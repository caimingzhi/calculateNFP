from itertools import groupby
from drawConcaveHullAlpha import saveMiddle
# 文件路径

pathMode = 'E:\\tmp\\groupMessage\\groupIDAndMode.txt'

# 创建一个空列表用于存储数据
groupeIdAndMode = []

# 读取文件内容
with open(pathMode, 'r') as file:
    # 逐行读取文件
    for line in file:
        # 去除换行符并分割字段
        fields = line.strip().split(',')
        
        # 将每行的字段转换为适当的数据类型
        fields = [int(fields[0]), fields[1], int(fields[2])]
        
        # 将字段添加到列表中
        groupeIdAndMode.append(fields)


folder_path = "D:\\试用期考核\\拼板方案\\1001PO文件\\PO文件"  # 将路径替换为你的文件夹路径
middle_path = "E:\\tmp\\poMiddlePoint"
for item in groupeIdAndMode:
    groupeId = item[1]
    file = folder_path + "\\" + groupeId + ".txt"
    save_path = middle_path + "\\" + groupeId + "_middlePoint.txt"
    with open(save_path, "w"):
        pass  # 使用 pass 语句，什么也不做
    saveMiddle( file, save_path )
# 使用 groupby 分组
grouped_data = {key: list(group) for key, group in groupby(groupeIdAndMode, key=lambda x: x[0])}