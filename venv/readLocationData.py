file_path = "E:\\tmp\groupMessage\\location.txt"  # 替换为实际的文件路径
new_file_path = "E:\\tmp\\groupMessage\\locationBeta.txt"  # 替换为新文件保存路径

try:
    with open(file_path, "r") as file, open(new_file_path, "w") as output_file:
        for line in file:
            # 拆分每一行数据
            data = line.split()
            data[1] = "D:\\试用期考核\\拼板方案\\1001PO文件\PO文件\\" + data[1]+ ".pdf"
            # 处理数据，例如输出到控制台
            print("ID: {}, PO: {}, X: {}, Y: {}, Angle: {}".format(data[0], data[1], data[2], data[3], data[4]))
            output_file.write(" ".join(data) + "\n")
except FileNotFoundError:
    print(f"文件 '{file_path}' 不存在。")
except Exception as e:
    print(f"发生错误: {e}")
