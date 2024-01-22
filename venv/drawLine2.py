import matplotlib.pyplot as plt
from matplotlib.patches import Polygon

# 定义不规则多边形的顶点坐标
polygon_vertices = [(1, 1), (2, 3), (4, 4), (3, 2), (2.5, 1.5)]

# 创建一个图形对象
fig, ax = plt.subplots()

# 创建一个多边形对象并添加到图形中
polygon = Polygon(polygon_vertices, closed=True, edgecolor='b', facecolor='none')
ax.add_patch(polygon)

# 设置坐标轴范围，使得多边形能够完全显示
ax.set_xlim(0, 5)
ax.set_ylim(0, 5)

# 显示图形
plt.show()
