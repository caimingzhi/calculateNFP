import matplotlib.pyplot as plt

# 从文件中读取线段数据
segments = []
# with open("D:\\workFile\\theFileNewLine.txt", "r") as file:
# with open("D:\\workFile\\theFile5.txt", "r") as file:     
# with open("D:\\workFile\\theFileMoving.txt", "r") as file:
with open("D:\\workFile\\theFileFixed.txt", "r") as file:
# with open("D:\\workFile\\theFileMovAndFixed.txt", "r") as file:
    for line in file:
        points = list(map(float, line.split()))
        if len(points) == 4:
            segments.append(points)

# 创建一个绘图对象
fig, ax = plt.subplots()

# 绘制每一段线段
for segment in segments:
    x1, y1, x2, y2 = segment
    ax.plot([x1, x2], [y1, y2], marker='o', linestyle='-', color='b', markersize = 3 )
    # ax.plot([y1, y2], [x1, x2], marker='o', linestyle='-', color='b', markersize = 3 )

# 添加标签和标题
ax.set_xlabel('X轴标签')
ax.set_ylabel('Y轴标签')
ax.set_title('线段示例')

# 显示图形
plt.show()
