import argparse
import os
from dataclasses import dataclass
from typing import Tuple

import numpy as np
from PIL import Image, ImageOps, ImageFilter


@dataclass
class AHashDebug:
    img_path: str
    img_size: int
    hash_size: int
    gray_resized: np.ndarray         # (img_size, img_size)
    gray_hash_block: np.ndarray      # (hash_size, hash_size)
    mean_value: float
    bits: np.ndarray                 # (hash_size, hash_size) uint8
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


def ahash_debug(image_path: str,
                img_size: int = 32,
                hash_size: int = 8,
                border_trim: float = 0.0,
                gaussian_blur: float = 0.0) -> AHashDebug:
    # 1) 读图 + EXIF 方向矫正 + 灰度
    img = Image.open(image_path)
    img = ImageOps.exif_transpose(img).convert("L")

    # 2) 方形中心裁剪 → 可选裁边 → 可选高斯模糊 → 缩放到统一尺寸
    img = _center_crop_to_square(img)

    if border_trim and border_trim > 0.0:
        w, h = img.size
        trim = int(min(w, h) * float(border_trim))
        if trim > 0 and (w - 2 * trim) > 0 and (h - 2 * trim) > 0:
            img = img.crop((trim, trim, w - trim, h - trim))

    if gaussian_blur and gaussian_blur > 0.0:
        img = img.filter(ImageFilter.GaussianBlur(radius=float(gaussian_blur)))

    img = img.resize((img_size, img_size), Image.BICUBIC)
    gray_resized = np.asarray(img, dtype=np.float32)

    # 3) 再缩放到 hash_size x hash_size 作为哈希输入块
    hash_img = img.resize((hash_size, hash_size), Image.BICUBIC)
    gray_hash = np.asarray(hash_img, dtype=np.float32)

    # 4) 计算均值阈值（aHash 用均值）
    mean_value = float(np.mean(gray_hash))

    # 5) 二值化：像素 > 均值 记 1，否则 0
    bits = (gray_hash > mean_value).astype(np.uint8)

    # 6) 行优先打包
    h_int = _pack_bits_row_major(bits)
    width_bits = hash_size * hash_size
    h_hex = "0x{:0{}x}".format(h_int, (width_bits + 3) // 4)

    return AHashDebug(
        img_path=image_path,
        img_size=img_size,
        hash_size=hash_size,
        gray_resized=gray_resized,
        gray_hash_block=gray_hash,
        mean_value=mean_value,
        bits=bits,
        hash_int=h_int,
        hash_hex=h_hex,
    )


def hamming_distance(a: int, b: int) -> int:
    x = a ^ b
    try:
        return x.bit_count()  # Python 3.8+
    except Exception:
        return bin(x).count("1")


def _print_debug(res: AHashDebug, stream, max_show: int = 8) -> None:
    print(f"图像: {res.img_path}", file=stream)
    print(f"工作尺寸: {res.img_size}x{res.img_size}, 哈希块: {res.hash_size}x{res.hash_size}", file=stream)
    np.set_printoptions(precision=2, suppress=True, linewidth=140)

    print("\n[灰度矩阵（缩放到工作尺寸，左上 8x8 展示）]", file=stream)
    print("说明: 单通道亮度值，范围约 0-255。", file=stream)
    print(res.gray_resized[:max_show, :max_show], file=stream)

    print("\n[哈希输入块（缩放到 hash_size x hash_size）]", file=stream)
    print("说明: aHash 在此块上取均值并进行阈值二值化。", file=stream)
    print(res.gray_hash_block, file=stream)

    print(f"\n[均值阈值]: {res.mean_value:.6f}", file=stream)
    print("说明: 像素值大于均值记为 1，否则为 0。", file=stream)

    print("\n[二值矩阵（>均值 记 1）]", file=stream)
    print(res.bits, file=stream)

    print(f"\n哈希（十六进制）: {res.hash_hex}", file=stream)
    print("-" * 60, file=stream)


def main():
    parser = argparse.ArgumentParser(description="aHash debug with step-by-step printing and comparison")
    parser.add_argument("image1", type=str, help="path to first image")
    parser.add_argument("image2", type=str, help="path to second image")
    parser.add_argument("--img-size", type=int, default=32, help="resize dimension for working view (default 32)")
    parser.add_argument("--hash-size", type=int, default=8, help="hash block size (default 8 → 64-bit)")
    parser.add_argument("--border-trim", type=float, default=0.0,
                        help="按比例裁掉四边（如 0.05 表示裁 5%），在缩放前进行")
    parser.add_argument("--gaussian-blur", type=float, default=0.0,
                        help="缩放前应用高斯模糊半径（如 0.8），0 表示不应用")
    parser.add_argument("--out", type=str, default=None, help="输出文件路径（默认: 'ahash hash_relust.txt'）")
    args = parser.parse_args()

    res1 = ahash_debug(args.image1, img_size=args.img_size, hash_size=args.hash_size,
                       border_trim=args.border_trim, gaussian_blur=args.gaussian_blur)
    res2 = ahash_debug(args.image2, img_size=args.img_size, hash_size=args.hash_size,
                       border_trim=args.border_trim, gaussian_blur=args.gaussian_blur)

    out_path = args.out if args.out else "ahash hash_relust.txt"

    with open(out_path, "w", encoding="utf-8") as f:
        print("aHash 逐步计算与比较（含中文说明）", file=f)
        print("=" * 60, file=f)
        _print_debug(res1, stream=f)
        _print_debug(res2, stream=f)

        dist = hamming_distance(res1.hash_int, res2.hash_int)
        bits = args.hash_size * args.hash_size
        norm = dist / float(bits)
        t1 = round(5 * bits / 64)
        t2 = round(10 * bits / 64)
        t3 = round(15 * bits / 64)
        print("\n[两图比较]", file=f)
        print(f"汉明距离: {dist} / {bits}（归一化 {norm:.4f}）", file=f)
        print(
            f"说明: 阈值随位数线性缩放，当前位数建议: ≤{t1} 极似, {t1+1}–{t2} 相似, {t2+1}–{t3} 边缘, >{t3} 不同。",
            file=f,
        )
        print("备注: aHash 简单快速，但对光照/对比度变化相对敏感；建议基于数据标定。", file=f)

    print(f"已写入: {out_path}")


if __name__ == "__main__":
    main()


