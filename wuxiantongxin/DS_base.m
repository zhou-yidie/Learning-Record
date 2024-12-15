% 清空工作区和图形窗口
clc;
clear;
close all;

% 1. 生成伪随机码（PN序列）
N = 7;  % LFSR的长度
initial_state = [1, 1, 0, 1, 1, 0, 1];  % 初始状态
feedback_taps = [7, 6];  % LFSR反馈位

pn_sequence = zeros(1, 100);  % 存储生成的伪随机序列
state = initial_state;

for i = 1:100
    feedback_bit = mod(sum(state(feedback_taps)), 2);  % 计算反馈位
    pn_sequence(i) = state(end);  % 输出当前位
    state = [feedback_bit, state(1:end-1)];  % 更新状态
end

% 2. 生成原始数据（信息信号）
data_bits = randi([0, 1], 1, 10);  % 随机生成原始数据比特



% 3. 扩频：信息信号与伪随机序列进行按位乘积（直接序列扩频）
spread_signal = [];
for i = 1:length(data_bits)
    spread_signal = [spread_signal, data_bits(i) * pn_sequence];
end

% 4. 解扩：接收端使用相同的伪随机码与接收到的信号进行按位乘积解扩
received_signal = spread_signal;  % 模拟接收信号（无噪声）
demodulated_data = [];
for i = 1:length(data_bits)
    demodulated_data(i) = mod(sum(received_signal((i-1)*100 + 1:i*100) .* pn_sequence), 2);
end

% 5. 绘图展示结果
figure;
subplot(4, 1, 1);
plot(pn_sequence(1:100), 'b');  % 绘制伪随机序列
title('伪随机码（PN序列）');
xlabel('时间');
ylabel('比特值');

subplot(4, 1, 2);
stem(data_bits, 'filled');  % 绘制解扩后的数据
title('随机生成的数据');
xlabel('数据索引');
ylabel('比特值');

subplot(4, 1, 3);
stem(spread_signal(1:1000), 'filled');  % 绘制扩频信号
title('扩频信号');
xlabel('时间');
ylabel('信号值');

subplot(4, 1, 4);
stem(demodulated_data, 'filled');  % 绘制解扩后的数据
title('解扩后的数据');
xlabel('数据索引');
ylabel('比特值');

% 输出解扩后的数据
disp('解扩后的数据:');
disp(demodulated_data);
