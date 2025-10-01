import argparse
import os
from dataclasses import dataclass
from typing import Optional, Tuple

import numpy as np
from PIL import Image, ImageOps, ImageFilter

# 优先使用 scipy 的 DCT；没有则退到 OpenCV；都没有则报错
_dct_backend = None
try:
    from scipy.fftpack import dct as _scipy_dct
    def dct2(a: np.ndarray) -> np.ndarray:
        return _scipy_dct(_scipy_dct(a, axis=0, norm="ortho"), axis=1, norm="ortho")
    _dct_backend = "scipy"
except Exception:
    try:
        import cv2  # type: ignore
        def dct2(a: np.ndarray) -> np.ndarray:
            return cv2.dct(a.astype(np.float32))
        _dct_backend = "opencv"
    except Exception:
        raise RuntimeError("需要 scipy 或 opencv 任一库来计算 DCT。请安装 scipy 或 opencv-python")

@dataclass
class PHashDebug:
    img_path: str
    backend: str
    img_size: int
    hash_size: int
    gray_32: np.ndarray             # (img_size, img_size)
    dct_full: np.ndarray            # (img_size, img_size)
    lowfreq: np.ndarray             # (hash_size, hash_size)
    median: float
    bits: np.ndarray                # (hash_size, hash_size) uint8
    hash_int: int
    hash_hex: str

def _center_crop_to_square(pil_img: Image.Image) -> Image.Image:
    w, h = pil_img.size
    if w == h:
        return pil_img
    side = min(w, h)
    left = (w - side) // 2
    top = (h - side) // 2
    return pil_img.crop((left, top, left + side, top + side))

def _pack_bits_row_major(bits: np.ndarray) -> int:
    h = 0
    for r in range(bits.shape[0]):
        row = bits[r]
        for c in range(bits.shape[1]):
            h = (h << 1) | int(row[c])
    return h

def phash_debug(image_path: str,
                img_size: int = 32,
                hash_size: int = 8,
                exclude_dc_for_threshold: bool = True,
                border_trim: float = 0.0,
                gaussian_blur: float = 0.0) -> PHashDebug:
    # 1) 读图 + EXIF 方向矫正 + 灰度 + 方形中心裁剪 + 缩放
    img = Image.open(image_path)
    img = ImageOps.exif_transpose(img).convert("L")
    img = _center_crop_to_square(img)

    # 可选：按比例裁边（各方向裁掉相同百分比），在缩放之前进行
    if border_trim and border_trim > 0.0:
        w, h = img.size
        trim = int(min(w, h) * float(border_trim))
        if trim > 0 and (w - 2 * trim) > 0 and (h - 2 * trim) > 0:
            img = img.crop((trim, trim, w - trim, h - trim))

    # 可选：轻度高斯模糊，减弱噪声/伪影
    if gaussian_blur and gaussian_blur > 0.0:
        img = img.filter(ImageFilter.GaussianBlur(radius=float(gaussian_blur)))

    img = img.resize((img_size, img_size), Image.BICUBIC)

    gray = np.asarray(img, dtype=np.float32)  # 0..255

    # 2) 2D DCT (正交)
    C = dct2(gray)

    # 3) 取左上角低频块 (hash_size x hash_size)
    low = C[:hash_size, :hash_size].copy()

    # 4) 计算中位数阈值（通常排除 DC）
    if exclude_dc_for_threshold and hash_size >= 2:
        mask = np.ones_like(low, dtype=bool)
        mask[0, 0] = False
        med = float(np.median(low[mask]))
    else:
        med = float(np.median(low))

    # 5) 二值化（严格 > 中位数 记 1）
    bits = (low > med).astype(np.uint8)

    # 6) 行优先打包为 64 位整数（或更长）
    h_int = _pack_bits_row_major(bits)
    width_bits = hash_size * hash_size
    h_hex = "0x{:0{}x}".format(h_int, (width_bits + 3) // 4)

    return PHashDebug(
        img_path=image_path,
        backend=_dct_backend,
        img_size=img_size,
        hash_size=hash_size,
        gray_32=gray,
        dct_full=C,
        lowfreq=low,
        median=med,
        bits=bits,
        hash_int=h_int,
        hash_hex=h_hex,
    )

def hamming_distance(a: int, b: int) -> int:
    x = a ^ b
    # 兼容老版本 Python（无 int.bit_count）
    try:
        return x.bit_count()  # type: ignore[attr-defined]
    except Exception:
        return bin(x).count("1")

def _print_debug(res: PHashDebug, stream, max_show: int = 8) -> None:
    print(f"图像: {res.img_path}", file=stream)
    print(f"DCT 后端: {res.backend}", file=stream)
    print(f"工作尺寸: {res.img_size}x{res.img_size}, 哈希低频块: {res.hash_size}x{res.hash_size}", file=stream)
    np.set_printoptions(precision=2, suppress=True, linewidth=140)

    print("\n[灰度矩阵（左上 8x8 展示）]", file=stream)
    print("说明: 单通道亮度值，范围约 0-255。", file=stream)
    print(res.gray_32[:max_show, :max_show], file=stream)

    print("\n[DCT 全系数（左上 8x8 展示）]", file=stream)
    print("说明: 将空间域转换到频率域，左上为低频（整体结构），右下为高频（细节/噪声）。", file=stream)
    print(res.dct_full[:max_show, :max_show], file=stream)

    print("\n[低频块（用于生成哈希）]", file=stream)
    print("说明: 仅取左上低频子块，pHash 利用其稳定性。", file=stream)
    print(res.lowfreq, file=stream)

    print(f"\n[中位数阈值（计算时排除 DC）]: {res.median:.6f}", file=stream)
    print("说明: 用中位数做阈值，较抗极端值和亮度偏置。", file=stream)

    print("\n[二值矩阵（系数 > 中位数 记 1，否则 0）]", file=stream)
    print(res.bits, file=stream)

    print(f"\n哈希（十六进制）: {res.hash_hex}", file=stream)
    print("-" * 60, file=stream)

def main():
    parser = argparse.ArgumentParser(description="pHash debug with step-by-step printing and comparison")
    parser.add_argument("image1", type=str, help="path to first image")
    parser.add_argument("image2", type=str, help="path to second image")
    parser.add_argument("--img-size", type=int, default=32, help="resize dimension (default 32)")
    parser.add_argument("--hash-size", type=int, default=8, help="low-frequency block size (default 8)")
    parser.add_argument("--include-dc-in-threshold", action="store_true",
                        help="include DC coefficient when computing median threshold (default: exclude)")
    parser.add_argument("--border-trim", type=float, default=0.0,
                        help="按比例裁掉四边（如 0.05 表示裁 5%），在缩放前进行")
    parser.add_argument("--gaussian-blur", type=float, default=0.0,
                        help="缩放前应用高斯模糊半径（如 0.8），0 表示不应用")
    parser.add_argument("--out", type=str, default=None,
                        help="输出文件路径（不指定则用 'phash_debug_<img1>_vs_<img2>.txt'）")
    args = parser.parse_args()

    res1 = phash_debug(
        args.image1,
        img_size=args.img_size,
        hash_size=args.hash_size,
        exclude_dc_for_threshold=not args.include_dc_in_threshold,
        border_trim=args.border_trim,
        gaussian_blur=args.gaussian_blur,
    )
    res2 = phash_debug(
        args.image2,
        img_size=args.img_size,
        hash_size=args.hash_size,
        exclude_dc_for_threshold=not args.include_dc_in_threshold,
        border_trim=args.border_trim,
        gaussian_blur=args.gaussian_blur,
    )

    # 输出文件路径
    if args.out is not None:
        out_path = args.out
    else:
        b1 = os.path.splitext(os.path.basename(args.image1))[0]
        b2 = os.path.splitext(os.path.basename(args.image2))[0]
        out_path = f"phash_debug_{b1}_vs_{b2}.txt"

    with open(out_path, "w", encoding="utf-8") as f:
        print("pHash 逐步计算与比较（含中文说明）", file=f)
        print("=" * 60, file=f)
        _print_debug(res1, stream=f)
        _print_debug(res2, stream=f)

        dist = hamming_distance(res1.hash_int, res2.hash_int)
        bits = args.hash_size * args.hash_size
        norm = dist / float(bits)
        # 按位数线性缩放 64 位经验阈值
        t1 = round(5 * bits / 64)
        t2 = round(10 * bits / 64)
        t3 = round(15 * bits / 64)
        print("\n[两图比较]", file=f)
        print(f"汉明距离: {dist} / {bits}（归一化 {norm:.4f}）", file=f)
        print(
            f"说明: 阈值随位数线性缩放，当前位数建议: ≤{t1} 极似, {t1+1}–{t2} 相似, {t2+1}–{t3} 边缘, >{t3} 不同。",
            file=f,
        )
        print("备注: 请基于你的数据集做 ROC/PR 标定更可靠。", file=f)

    print(f"已写入: {out_path}")

if __name__ == "__main__":
    main()