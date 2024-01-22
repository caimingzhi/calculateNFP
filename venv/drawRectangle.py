import matplotlib.pyplot as plt
import matplotlib.patches as patches

# # 创建一个新的绘图
# fig, ax = plt.subplots()

# # 创建一个矩形补丁
# rectangle = patches.Rectangle((0.2, 0.2), 0.6, 0.4, linewidth=2, edgecolor='r', facecolor='none')

# # 将矩形添加到绘图中
# ax.add_patch(rectangle)

# # 设置坐标轴范围
# ax.set_xlim(0, 1)
# ax.set_ylim(0, 1)

# # 显示绘图
# plt.show()

import turtle

# 创建Turtle对象
t = turtle.Turtle()

# 绘制矩形
for _ in range(2):
    t.forward(100)  # 前进100个单位
    t.left(90)      # 左转90度
    t.forward(50)   # 前进50个单位
    t.left(90)      # 左转90度

# 关闭Turtle图形窗口
turtle.done()

