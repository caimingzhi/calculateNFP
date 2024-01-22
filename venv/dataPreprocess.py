import os
import subprocess
folder_path = "D:\\试用期考核\\拼板方案\\1001PO文件\\PO文件"  # 将路径替换为你的文件夹路径

# 列出文件夹中的所有文件
files = os.listdir(folder_path)
command = 'java -jar pdf2jtsBeta.jar '
directory_path = 'cd E:\\tmp\\practiceTest && '
# subprocess.run('cd E:\\tmp\\practiceTest', shell=True, check=True)

# 打印每个文件的文件名
for file in files:
    file = folder_path + "\\" + file
    command1 = directory_path + command + file + " 0.3"
    subprocess.run(command1, shell=True, check=True)
    # print(file)


