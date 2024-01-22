import matplotlib.pyplot as plt
import os
import uuid  # 导入 uuid 模块

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class LineSegment:
    def __init__(self, start, end):
        self.start = start
        self.end = end

line_segments = []
# path = "E:\\myNewReposity\\testLib\calculateNFP\\lineSegment.txt"
# path = "E:\\myNewReposity\\testLib\calculateNFP\\lineSegment01.txt"
path = "E:\\myNewReposity\\testLib\calculateNFP\\PointSeq.txt"
# path = "E:\\myNewReposity\\testLib\\calculateNFP\\nfp.txt"

# 从文件中读取数据并解析
with open(path, "r") as file:
    lines = file.readlines()
    for line in lines:
        coordinates = list(map(float, line.split()))
        start_point = Point(coordinates[0], coordinates[1])
        end_point = Point(coordinates[2], coordinates[3])
        line_segment = LineSegment(start_point, end_point)
        line_segments.append(line_segment)

# 生成一个随机的文件名
output_folder = "E:\\myNewReposity\\testLib\\alculateNFP\\output";
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

file_name = os.path.join(output_folder, str(uuid.uuid4()) + ".png")

# 创建一个图形
plt.figure()

# 绘制所有线段
for segment in line_segments:
    plt.plot([segment.start.x, segment.end.x], [segment.start.y, segment.end.y], marker='o')

# 添加网格线
plt.grid(True)

# 设置图形属性
plt.title('Line Segments')
plt.xlabel('X')
plt.ylabel('Y')

# 保存图像到文件（以生成的文件名保存）
# plt.savefig(file_name)
plt.show()
# 不显示绘图
# plt.show()
