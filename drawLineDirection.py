import matplotlib.pyplot as plt
import numpy as np

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class LineSegment:
    def __init__(self, start, end):
        self.start = start
        self.end = end

line_segments = []
path = "E:\\myNewReposity\\testLib\\calculateNFP\\lineSegment.txt"

# 从文件中读取数据并解析
with open(path, "r") as file:
    lines = file.readlines()
    for line in lines:
        coordinates = list(map(float, line.split()))
        start_point = Point(coordinates[0], coordinates[1])
        end_point = Point(coordinates[2], coordinates[3])
        line_segment = LineSegment(start_point, end_point)
        line_segments.append(line_segment)

# 绘制所有线段
for segment in line_segments:
    plt.plot([segment.start.x, segment.end.x], [segment.start.y, segment.end.y], marker='o')

    # 计算线段中点和方向向量
    mid_point = Point((segment.start.x + segment.end.x) / 2, (segment.start.y + segment.end.y) / 2)
    direction_vector = np.array([segment.end.x - segment.start.x, segment.end.y - segment.start.y])

    # 绘制箭头表示方向
    plt.arrow(mid_point.x, mid_point.y, direction_vector[0], direction_vector[1], head_width=0.1, head_length=0.2, fc='blue', ec='blue')

# 读取点数据并绘制点
point_path = "E:\\myNewReposity\\testLib\\calculateNFP\\point.txt"
with open(point_path, "r") as point_file:
    point_lines = point_file.readlines()
    for point_line in point_lines:
        point_coordinates = list(map(float, point_line.split()))
        plt.plot(point_coordinates[0], point_coordinates[1], 'go')  # 'go' means green circles

# 添加网格线
plt.grid(True)

# 设置图形属性
plt.title('Line Segments and Points')
plt.xlabel('X')
plt.ylabel('Y')

# 显示绘图
plt.show()
import matplotlib.pyplot as plt
import numpy as np

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class LineSegment:
    def __init__(self, start, end):
        self.start = start
        self.end = end

line_segments = []
# path = "E:\\myNewReposity\\testLib\\calculateNFP\\lineSegment.txt"
# path = "E:\\myNewReposity\\testLib\\calculateNFP\\lineSegment01.txt"
path = "E:\\myNewReposity\\testLib\\calculateNFP\\nfp.txt"

# 从文件中读取数据并解析
with open(path, "r") as file:
    lines = file.readlines()
    for line in lines:
        coordinates = list(map(float, line.split()))
        start_point = Point(coordinates[0], coordinates[1])
        end_point = Point(coordinates[2], coordinates[3])
        line_segment = LineSegment(start_point, end_point)
        line_segments.append(line_segment)

# 绘制所有线段
for segment in line_segments:
    plt.plot([segment.start.x, segment.end.x], [segment.start.y, segment.end.y], marker='o')

    # 计算线段中点和方向向量
    mid_point = Point((segment.start.x + segment.end.x) / 2, (segment.start.y + segment.end.y) / 2)
    direction_vector = np.array([segment.end.x - segment.start.x, segment.end.y - segment.start.y])

    # 绘制箭头表示方向
    plt.arrow(mid_point.x, mid_point.y, direction_vector[0], direction_vector[1], head_width=0.1, head_length=0.2, fc='blue', ec='blue')

# 读取点数据并绘制点
point_path = "E:\\myNewReposity\\testLib\\calculateNFP\\point.txt"
with open(point_path, "r") as point_file:
    point_lines = point_file.readlines()
    for point_line in point_lines:
        point_coordinates = list(map(float, point_line.split()))
        plt.plot(point_coordinates[0], point_coordinates[1], 'go')  # 'go' means green circles

# 添加网格线
plt.grid(True)

# 设置图形属性
plt.title('Line Segments and Points')
plt.xlabel('X')
plt.ylabel('Y')

# 显示绘图
plt.show()
