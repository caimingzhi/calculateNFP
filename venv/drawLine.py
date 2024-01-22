import matplotlib.pyplot as plt

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class LineSegment:
    def __init__(self, start, end):
        self.start = start
        self.end = end

# 定义地址文件路径
save_seq = []
for j in range( 12*160 ):
    if j % 120 == 0 :
        save_seq.append(j)


paths = [
f"E:\\myNewReposity\\testLib\\caculateNFPbeta\\cache\\cuckoosSearch{i}.txt" for i in save_seq
]



# 创建一个图形对象，包含多个子图
fig, axes = plt.subplots(4, 4, figsize=(10, 10))

# 读取每个地址的数据并在不同的子图上绘制
for i, path in enumerate(paths):
    line_segments = []
    with open(path, "r") as file:
        lines = file.readlines()
        for line in lines:
            coordinates = list(map(float, line.split()))
            start_point = Point(coordinates[0], coordinates[1])
            end_point = Point(coordinates[2], coordinates[3])
            line_segment = LineSegment(start_point, end_point)
            line_segments.append(line_segment)
    
    # 绘制每个地址的数据在不同的子图上
    row = i // 4
    col = i % 4
    print( row, col )
    for segment in line_segments:
        axes[row, col].plot([segment.start.x, segment.end.x], [segment.start.y, segment.end.y], marker='o')
    axes[row, col].set_title(f'Address {i+1}')




# 调整子图之间的间距
plt.tight_layout()

# 添加网格线
for ax in axes.flatten():
    ax.grid(True)

# 设置图形属性
fig.suptitle('Line Segments from Multiple Addresses')
fig.text(0.5, 0.04, 'X', ha='center')
fig.text(0.04, 0.5, 'Y', va='center', rotation='vertical')

# 显示绘图
plt.show()
