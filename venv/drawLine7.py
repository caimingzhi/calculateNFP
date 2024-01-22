
import matplotlib.pyplot as plt

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class LineSegment:
    def __init__(self, start, end):
        self.start = start
        self.end = end



line_segments = []




# path = "E:\\myNewReposity\\testLib\\caculateNFPbeta\cache\\cuckoosSearch1800.txt"
# path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates03-original.txt"
# path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates03-thisNew.txt"
path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates099-new.txt"
path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates0199-new.txt"  
# path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates0099-new.txt"  
path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates007-new.txt"  
# path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates0033-new.txt"  
path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates07-cache.txt"  

# path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates01.txt"
# path = "E:\\tmp\\nfp.txt"
# path = "E:\\tmp\\convex.txt"
# path = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates02.txt"
# 从文件中读取数据并解析

with open(path, "r") as file:
    lines = file.readlines()    
    for line in lines:
        coordinates = list(map(float, line.split()))
        start_point = Point(coordinates[0], coordinates[1])
        end_point = Point(coordinates[2], coordinates[3])
        line_segment = LineSegment(start_point, end_point)
        line_segments.append(line_segment)
# 绘制所有线段r
for segment in line_segments:
    plt.plot([segment.start.x, segment.end.x], [segment.start.y, segment.end.y], marker='o', markersize = 3 )









# 添加网格线
plt.grid(True)
# plt.xlim(-5, 15)
# plt.ylim(-5, 15)
    
# inferablity  raster tile pyramid inferablity inferablity  cone vertex terrain perservation

# 设置图形属性
plt.title('Line Segments')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
# 显示绘图
plt.show()
