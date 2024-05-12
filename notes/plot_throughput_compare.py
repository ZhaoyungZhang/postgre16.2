import pandas as pd
import matplotlib.pyplot as plt

# 读取原始数据和状态分开的数据
data_origin = pd.read_csv('tpcc-origin.csv')
data_separate = pd.read_csv('tpcc-state-separate.csv')

# 设置图形大小
plt.figure(figsize=(12, 6))

# 绘制原始数据的图形
plt.plot(data_origin['Time (seconds)'], data_origin['Throughput (requests/second)'], marker='o', linestyle='-', color='b', label='Baseline')

# 绘制状态分开数据的图形
plt.plot(data_separate['Time (seconds)'], data_separate['Throughput (requests/second)'], marker='o', linestyle='-', color='r', label='Separated')

# 添加标题和坐标轴标签
plt.title('Real-time Throughput Over Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Throughput (requests/second)')

# 添加网格线和图例
plt.grid(True)
plt.legend()

# 显示图形
plt.show()

# 将图形保存为图片文件
plt.savefig('tpcc_comparison.png')
