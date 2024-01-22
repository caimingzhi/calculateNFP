import re

# text = """MULTIPOLYGON (((430 450, 630 450, 630 370, 430 370, 430 450)), ((830 430, 865 430, 865 299, 830 299, 830 430)), ((690 420, 690 250, 670 250, 670 420, 690 420)))"""

# pattern = r'\(\((.*?)\)\)'
# matches = re.findall(pattern, text)

# for match in matches:
#     coordinates = match.split(',')
#     for coord in coordinates:
#         x, y = coord.strip('\(').split()
#         print(f"x: {x}, y: {y}")

# file_names = ["file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt", "file6.txt", "file7.txt", "file8.txt", "file9.txt", "file10.txt", "file11.txt", "file12.txt"]
file_names = ["fileAll.txt"]
index = 0
path = "E:\\tmp\\test.txt"
with open( path, "r" ) as file:
    line = file.read()
    pattern = r'\(\(.*?\)\)'
    matches = re.findall(pattern, line )

    print("===========")
    for match in matches:
        coordinates = match.split(',')
        x_value = []
        y_value = []
        for coord in coordinates:
            x, y = coord.strip('()').split()
            x_value.insert(0, float(x))
            y_value.insert(0, float(y))
            print(f"x: {x}, y: {y}")
        x_value.pop()
        y_value.pop()
        with open( file_names[index], "a" ) as file:
            file.write(" ".join(map(str, x_value)) + "\n")
            file.write(" ".join(map(str, y_value)) + "\n")
        # index = index + 1

    
            


# import re

# path = "D:\\试用期考核\\拼板方案\\test.txt"
# with open(path, "r") as file:
#     text = file.read()  # 一次性读取文件内容

#     pattern = r'\(\(.*?\)\)'
#     matches = re.findall(pattern, text)

#     for match in matches:
#         coordinates = match.split(',')
#         for coord in coordinates:
#             x, y = coord.strip('()').split()
#             print(f"x: {x}, y: {y}")
