#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>  // for sleep function on Unix-like systems
#include "stb_vorbis.c"  // stb_vorbis库实现，用于读取音频文件，需自行下载包含进来

#define PI 3.14159265358979323846

// FIR滤波器结构体定义
typedef struct {
    int order;
    float *coeffs;
    float *buffer;
    int buffer_index;
} FIRFilter;

// 初始化FIR滤波器
FIRFilter* fir_filter_init(int order, float fc, int fs) {
    FIRFilter *filter = (FIRFilter *)malloc(sizeof(FIRFilter));
    filter->order = order;
    filter->coeffs = (float *)malloc((order + 1) * sizeof(float));
    filter->buffer = (float *)malloc((order + 1) * sizeof(float));
    for (int i = 0; i < order + 1; i++) {
        filter->buffer[i] = 0.0;
    }
    filter->buffer_index = 0;

    // 计算滤波器系数（简单的fir1实现，这里只支持低通）
    for (int n = 0; n <= order; n++) {
        if (n == order / 2) {
            filter->coeffs[n] = fc / (fs / 2);
        } else {
            filter->coeffs[n] = sin(PI * fc * (n - order / 2) / (fs / 2)) / (PI * (n - order / 2));
            filter->coeffs[n] *= (0.42 - 0.5 * cos(2 * PI * n / order) + 0.08 * cos(4 * PI * n / order));
        }
    }
    return filter;
}

// FIR滤波操作
float fir_filter(FIRFilter *filter, float input) {
    float output = 0.0;
    filter->buffer[filter->buffer_index] = input;
    for (int i = 0; i <= filter->order; i++) {
        int index = (filter->buffer_index - i + filter->order + 1) % (filter->order + 1);
        output += filter->coeffs[i] * filter->buffer[index];
    }
    filter->buffer_index = (filter->buffer_index + 1) % (filter->order + 1);
    return output;
}

// 释放FIR滤波器资源
void fir_filter_free(FIRFilter *filter) {
    free(filter->coeffs);
    free(filter->buffer);
    free(filter);
}

// 计算FFT（简单实现，这里只做示例，实际可能需用更完善的FFT库）
void fft(float *data, int n, float *real, float *imag) {
    if (n <= 1) return;
    float even_real[n / 2], even_imag[n / 2];
    float odd_real[n / 2], odd_imag[n / 2];
    for (int i = 0; i < n / 2; i++) {
        even_real[i] = data[2 * i];
        even_imag[i] = data[2 * i + 1];
        odd_real[i] = data[2 * i + 2];
        odd_imag[i] = data[2 * i + 3];
    }
    fft(even_real, n / 2, real, imag);
    fft(odd_real, n / 2, real + n / 2, imag + n / 2);
    for (int k = 0; k < n / 2; k++) {
        float angle = -2 * PI * k / n;
        float cos_angle = cos(angle);
        float sin_angle = sin(angle);
        float temp_real = cos_angle * odd_real[k] - sin_angle * odd_imag[k];
        float temp_imag = cos_angle * odd_imag[k] + sin_angle * odd_real[k];
        real[k] += temp_real;
        imag[k] += temp_imag;
        real[k + n / 2] = real[k] - temp_real;
        imag[k + n / 2] = imag[k] - temp_imag;
    }
}

// 生成正弦波噪声
void generate_noise(float *noise, int length, float noise_frequency, float noise_amplitude, int fs) {
    for (int i = 0; i < length; i++) {
        noise[i] = noise_amplitude * sin(2 * PI * noise_frequency * i / fs);
    }
}

// 绘制频谱（这里通过调用gnuplot来绘制，需安装gnuplot并根据实际情况修改路径）
void plot_spectrum(float *data, int length, int fs, char *title, char *xlabel, char *ylabel) {
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe == NULL) {
        printf("无法打开gnuplot管道\n");
        return;
    }
    fprintf(gnuplotPipe, "set title '%s'\n", title);
    fprintf(gnuplotPipe, "set xlabel '%s'\n", xlabel);
    fprintf(gnuplotPipe, "set ylabel '%s'\n", ylabel);
    fprintf(gnuplotPipe, "plot '-' with lines\n");
    float real[length];
    float imag[length];
    fft(data, length, real, imag);
    for (int i = 0; i < length / 2 + 1; i++) {
        float magnitude = sqrt(real[i] * real[i] + imag[i] * imag[i]) / (length / 2);
        if (i > 0 && i < length / 2) {
            magnitude *= 2;
        }
        fprintf(gnuplotPipe, "%f %f\n", (float)i * fs / length, magnitude);
    }
    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
    pclose(gnuplotPipe);
}

int main() {
    int channels;
    int sample_rate;
    int error;
    stb_vorbis *vorbis = stb_vorbis_open_filename("D:\\githubprojects\\Learning-Record\\matlab\\my_music_file.ogg", &error, NULL);
    if (vorbis == NULL) {
        printf("无法读取音频文件\n");
        return -1;
    }
    stb_vorbis_info info = stb_vorbis_get_info(vorbis);
    channels = info.channels;
    sample_rate = info.sample_rate;
    int num_samples = stb_vorbis_stream_length_in_samples(vorbis);
    short *audio_data = (short *)malloc(num_samples * channels * sizeof(short));
    stb_vorbis_get_samples_short_interleaved(vorbis, channels, audio_data, num_samples * channels);

    // 生成噪声
    float noise[num_samples];
    generate_noise(noise, num_samples, 1000, 0.1, sample_rate);

    // 添加噪声到音频数据
    short noisy_audio_data[num_samples];
    for (int i = 0; i < num_samples; i++) {
        noisy_audio_data[i] = audio_data[i] + (short)(noise[i] * 32767);  // 转换为16位音频范围
    }

    // 初始化FIR滤波器
    FIRFilter *filter = fir_filter_init(100, 3000, sample_rate);

    // 滤波
    short filtered_audio_data[num_samples];
    for (int i = 0; i < num_samples; i++) {
        float input = (float)noisy_audio_data[i] / 32767;  // 归一化
        float output = fir_filter(filter, input);
        filtered_audio_data[i] = (short)(output * 32767);  // 转换回16位音频范围
    }

    // 绘制原始音频频谱
    plot_spectrum((float *)audio_data, num_samples, sample_rate, "读取音乐的频谱", "频率 (Hz)", "幅值");

    // 绘制加噪后音频频谱
    plot_spectrum((float *)noisy_audio_data, num_samples, sample_rate, "加入正弦波后的语音频谱", "频率 (Hz)", "幅值");

    // 绘制滤波后音频频谱
    plot_spectrum((float *)filtered_audio_data, num_samples, sample_rate, "用滤波器滤波后的频谱", "频率 (Hz)", "幅值");

    // 播放原始音频（通过调用系统命令，这里以aplay为例，不同系统需调整）
    sleep(10);
    _sleep(10);

    // 播放加噪后音频（将加噪后的音频数据先保存为临时文件再播放，需确保有写权限等）
    FILE *temp_noisy_file = fopen("temp_noisy.wav", "wb");
    // 这里需按照WAV文件格式写入头信息以及音频数据等，此处省略详细的WAV文件格式写入代码
    fwrite(noisy_audio_data, sizeof(short), num_samples, temp_noisy_file);
    fclose(temp_noisy_file);
    system("aplay -r <采样率> -f S16_LE temp_noisy.wav &");
    sleep(10);
    _sleep(10);

    // 播放滤波后音频（同样保存为临时文件再播放）
    FILE *temp_filtered_file = fopen("temp_filtered.wav", "wb");
    fwrite(filtered_audio_data, sizeof(short), num_samples, temp_filtered_file);
    fclose(temp_filtered_file);
    system("aplay -r <采样率> -f S16_LE temp_filtered.wav &");

    // 释放资源
    stb_vorbis_close(vorbis);
    fir_filter_free(filter);
    remove("temp_noisy.wav");
    remove("temp_filtered.wav");

    return 0;
}