import matplotlib.pyplot as plt

# 读取文件数据
with open('D:\workFile\pointCache.txt', 'r') as file:
    lines = file.readlines()

# 提取 x 和 y 坐标
x_values = [float(line.split()[0]) for line in lines]
y_values = [float(line.split()[1]) for line in lines]

# 绘制散点图
plt.scatter(x_values, y_values, label='Data Points')

# 设置图表标题和轴标签
plt.title('Scatter Plot of Data Points')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')

# 显示图例
plt.legend()

# 显示图形
plt.show()
