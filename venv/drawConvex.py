
import matplotlib.pyplot as plt
import datetime
import sys
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class LineSegment:
    def __init__(self, start, end):
        self.start = start
        self.end = end



line_segments = []
current_time = datetime.datetime.now()
timestamp = current_time.strftime("%Y%m%d_%H%M%S_%f")[:-3]  # Remove the last three characters to keep only milliseconds

path = "E:\\tmp\\convex.txt"

with open(path, "r") as file:
    lines = file.readlines()
    for line in lines:
        coordinates = list(map(float, line.split()))
        start_point = Point(coordinates[0], coordinates[1])
        end_point = Point(coordinates[2], coordinates[3])
        line_segment = LineSegment(start_point, end_point)
        line_segments.append(line_segment)



# 读取额外的点坐标
additional_points = []
additional_path = "E:\\tmp\\dominantPoint.txt"
with open(additional_path, "r") as file:
    lines = file.readlines()
    for line in lines:
        x, y = map(float, line.split())
        additional_points.append(Point(x, y))

# 绘制所有线段r
for segment in line_segments:
    plt.plot([segment.start.x, segment.end.x], [segment.start.y, segment.end.y], marker='o', markersize = 3 )


for point in additional_points:
    plt.scatter(point.x, point.y, color='red', marker='x', label='Dominant Point')

# 添加网格线
plt.grid(True)
# 设置图形属性
plt.title('Line Segments')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
# 显示绘图
filename = f"output_{timestamp}"  # Replace "output" with your desired prefix and ".png" with the desired file extension
if len(sys.argv) > 1:
    # 将参数拼接为字符串，使用下划线连接
    filename = '_'.join(sys.argv[1:])
    print("filename:", filename)
else:
    filename = f"output_{timestamp}" 



plt.savefig(f"E:\\tmp\\plotConvex\\output_plot_{filename}.png", dpi=300 )
#
# plt.show()