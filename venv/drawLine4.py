import matplotlib.pyplot as plt

# 从文件中读取数据
x = []  # 存储x轴数据
y = []  # 存储y轴数据
# plt.style.use('_mpl-gallery') 
index = 1
dataMin = 99999
with open("D:\\workFile\\testFile.txt", "r") as file:
    for line in file:
        parts = line.split()
        if len(parts) == 2:
            x.append(index)
            index = index + 1
            y.append(float(parts[1]))
            if float( float(parts[1]) < dataMin ) :
                dataMin = float(parts[1])



# 创建折线图
plt.plot(x, y, marker='o', linestyle='-', color='b', markersize = 4, label='折线图示例')
plt.axhline(y=0, color='r', linestyle='--', label='y=0')
plt.axhline(y=0.01, color='g', linestyle='--', label='y=0')
plt.axhline(y=dataMin, color='r', linestyle='--', label='y=0')
# 添加标签和标题
plt.xlabel('X轴标签')
plt.ylabel('Y轴标签')
plt.title('折线图示例')

# 添加图例
plt.legend()

# 显示图形
plt.show()
