from itertools import groupby
# 文件路径

pathMode = 'E:\\tmp\\groupMessage\\Group69\\groupIDAndMode2.txt'

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


# 使用 groupby 分组
grouped_data = {key: list(group) for key, group in groupby(groupeIdAndMode, key=lambda x: x[0])}

# 输出每个分组
for key, group in grouped_data.items():
    print(f"分组 {key}:")
    for row in group:
        print(row)
    print()
from drawConcaveHullGamma import test
for key, group in grouped_data.items():
    # save_path = "E:\\tmp\\groupMessage\\Group69\\groupData\\group" + str(key) + ".txt"
    # with open(save_path, 'w') as file:
    #     pass
    print(f"groundId {key}")
    poID = []
    mobeNum = []
    for row in group:
        # print(row[2], row[1])
        poID.append(row[1])
        mobeNum.append(row[2])
    for thisIndex in range(0, len( mobeNum )):
        thisNum = 1
        while thisNum > 0:
            headPath = "D:\\试用期考核\\拼板方案\\1001PO文件\\PO文件"
            targetPo = poID[thisIndex] + ".txt"
            finalPath = headPath + "\\" + targetPo
            save_path = "E:\\tmp\\groupMessage\\PoFile\\" + poID[thisIndex] + ".txt"
            with open(save_path, 'w') as file:
                pass
            # if poID[thisIndex] == "PO2022050121748498":
            #     continue
            print(finalPath)
            test(finalPath, save_path)
            thisNum  -= 1


# 创建一个空列表用于存储数据
groupeIdAndArea = []

# pathArea = "E:\\tmp\\groupMessage\\groupIDAndArea2.txt"
# # 读取文件内容
# with open( pathArea, 'r') as file:
#     # 逐行读取文件
#     for line in file:
#         # 去除换行符并分割字段
#         fields = line.strip().split(',')
        
#         # 将每行的字段转换为整数或浮点数（根据需要）
#         fields = [int(fields[0]), float(fields[1]), int(fields[2])]
        
#         # 将字段添加到列表中
#         groupeIdAndArea.append(fields)

# for row in groupeIdAndArea:
#     print(row)

