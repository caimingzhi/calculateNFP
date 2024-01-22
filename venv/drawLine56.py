import numpy as np
import matplotlib.pyplot as plt

# 设置随机数种子，以便结果可重复
np.random.seed(0)

# 生成正态分布的随机数据
mean = 0  # 正态分布的均值
std_dev = 1  # 正态分布的标准差
sample_size = 5000000  # 样本大小



# 使用 numpy 生成正态分布的随机数据
data = np.random.normal(mean, std_dev, sample_size)

# 可选：绘制直方图来可视化数据分布
plt.hist(data, bins=100, density=True, alpha=0.6, color='g')
plt.title("Normal Distribution")
plt.xlabel("Value")
plt.ylabel("Frequency")
plt.show()
