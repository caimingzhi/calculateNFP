import pandas as pd

import re

from datetime import datetime, timedelta

import shutil

import time



# 记录开始时间

start_time = time.time()

# 读取Excel文件

excel_file_path = 'E:\\tmp\\test01.xlsx'

df = pd.read_excel(excel_file_path)
df['selected_device'] = None
df['printing_time'] = None

# 复制文件

# shutil.copy('E:\\Paichan_FJSP\\data_sql\\test.xlsx', 'E:\\Paichan_FJSP\\data_sql\\output_test.xlsx')

# 创建一个新的DataFrame，用于存储每个订单的结果

# results_df = pd.DataFrame(columns=['group_sn', 'texture_str', 'number', 'print_size', 'printSide', 'lastday', 'add_time', 'process_flow', 'selected_device', 'printing_time'])



class PrintingDevice:

    def __init__(self, id, device_name, device_size, device_num, max_long, max_width, min_long, min_width):

        self.id = id

        self.device_name = device_name

        self.device_size = device_size

        self.device_num = device_num

        self.max_long = max_long

        self.max_width = max_width

        self.min_long = min_long

        self.min_width = min_width



class UVPrintingDevice(PrintingDevice):

    def __init__(self, id, device_name, device_size, device_num, max_long, max_width, min_long, min_width):

        super().__init__(id, device_name, device_size, device_num, max_long, max_width, min_long, min_width)



# 创建印刷设备对象列表

printing_devices = [

    PrintingDevice(1, '1号机-对开5色', 5, 11, 1020, 723, 20, 20),

    PrintingDevice(2, '2号机-四开5色', 6, 11, 740, 530, 390, 260),

    PrintingDevice(3, '3号机-海德堡XL106', 5, 13, 1060, 740, 480, 340),

    PrintingDevice(4, '4号机-罗兰对开5色', 5, 11, 1040, 730, 520, 360),

    UVPrintingDevice(5, '5号机-对开UV机', 5, 11, 1111, 1111, 111, 111)

]



def calculate_printing_time(order_quantity, device):

    if isinstance(device, UVPrintingDevice):

        return calculate_uv_printing_time(order_quantity)

    else:

        return calculate_normal_printing_time(order_quantity)



def calculate_normal_printing_time(order_quantity):

    if order_quantity < 3000:

        return 30

    elif 3001 <= order_quantity <= 5000:

        return 60

    elif 5001 <= order_quantity <= 10000:

        return 90

    elif 10001 <= order_quantity <= 15000:

        return 120

    elif 15001 <= order_quantity <= 20000:

        return 150

    else:

        additional_time = ((order_quantity - 20000) // 5000) * 30

        return 150 + additional_time



def calculate_uv_printing_time(order_quantity):

    if order_quantity < 3000:

        return 60

    elif 3001 <= order_quantity <= 5000:

        return 90

    elif 5001 <= order_quantity <= 10000:

        return 120

    elif 10001 <= order_quantity <= 15000:

        return 150

    elif 15001 <= order_quantity <= 20000:

        return 180

    else:

        additional_time = ((order_quantity - 20000) // 5000) * 30

        return 180 + additional_time



def select_printer(order_long, order_width, order_quantity, is_uv_printing, is_double_sided, devices):

    # 根据印刷类型选择机器列表

    if is_uv_printing:

        valid_devices = [device for device in devices if isinstance(device, UVPrintingDevice)]

    else:

        valid_devices = [device for device in devices if not isinstance(device, UVPrintingDevice)]



    # 根据订单尺寸选择合适的机器

    valid_devices = [

        device for device in valid_devices

        if device.min_long <= order_long <= device.max_long

        and device.min_width <= order_width <= device.max_width

    ]



    if not valid_devices:

        return None, None



    # 选择比重最大的机器

    max_ratio_device = max(

        valid_devices,

        key=lambda device: max(order_long * order_width / (device.max_long * device.max_width),

                               device.min_width * device.min_long / (order_width * order_long))

    )

    printing_time = calculate_printing_time(order_quantity, max_ratio_device, is_double_sided)

    return max_ratio_device, printing_time



def calculate_printing_time(order_quantity, device, is_double_sided):

    if is_double_sided:

        # 如果是双面印刷，时间是单面印刷时间的两倍

        single_sided_time = calculate_single_sided_printing_time(order_quantity, device)

        return single_sided_time * 2

    else:

        # 如果是单面印刷，直接计算单面印刷时间

        return calculate_single_sided_printing_time(order_quantity, device)



# 新增计算单面印刷时间的函数

def calculate_single_sided_printing_time(order_quantity, device):

    if isinstance(device, UVPrintingDevice):

        return calculate_uv_printing_time(order_quantity)

    else:

        return calculate_normal_printing_time(order_quantity)



def update_dataframe(order_row, selected_device, printing_time):

    # 更新DataFrame中的数据

    index = df[df['group_sn'] == order_row['group_sn']].index

    if not index.empty:

        index = index[0]  # 获取订单的索引

        df.at[index, 'selected_device'] = selected_device.device_name

        df.at[index, 'printing_time'] = printing_time



def process_order( rowIndex, order_row):

    # global results_df  # 声明 results_df 为全局变量
    global df  # 声明 results_df 为全局变量

    

    # 从print_size字段中提取长宽信息并去除单位

    print_size = order_row['print_size'].replace('mm', '')



    # 使用正则表达式来提取数字部分
    # t1 = time.time()
    match = re.match(r'(\d+(\.\d+)?)\*(\d+(\.\d+)?)', print_size)
    # t2 = time.time()
    # elapsed_time1 = (t2 - t1)*1000000

    # print(f"信息提取用时: {elapsed_time1} 秒")


    if match:

        order_long1 = float(match.group(1))

        order_width1 = float(match.group(3))

    else:

        order_long1 = float(print_size)



    order_quantity = order_row['number']



    # 检查订单是否为双面印刷，是普通印刷还是UV印刷

    is_double_sided = order_row['printSide'] == '双面印刷'

    is_uv_printing = order_row['printSide'] == 'UV印刷'

    is_not_printing = order_row['printSide'] == '不印刷'



    # 将正则化后提取的时间用来计算印刷时间

    selected_device, printing_time = select_printer(order_long1, order_width1, order_quantity, is_uv_printing, is_double_sided, printing_devices)

    if is_not_printing:

        printing_time = 0  # 如果不印刷，印刷时间记为0


    t1 = time.time()

    if selected_device:

        
        df.loc[rowIndex, 'selected_device' ] = selected_device.device_name
        df.loc[rowIndex, 'printing_time' ] = printing_time
        # 创建一个包含当前订单结果的DataFrame

        # order_result = pd.DataFrame({

        #     'group_sn': [order_row['group_sn']],

        #     'texture_str': [order_row['texture_str']],

        #     'number': [order_row['number']],

        #     'print_size': [order_row['print_size']],

        #     'printSide': [order_row['printSide']],

        #     'lastday': [order_row['lastday']],

        #     'add_time': [order_row['add_time']],

        #     'process_flow': [order_row['process_flow']],

        #     'selected_device': [selected_device.device_name],

        #     'printing_time': [printing_time]

        # })



        # 将订单结果DataFrame附加到结果DataFrame中

       

        # results_df = pd.concat([results_df, order_result], ignore_index=True)


        t2 = time.time()
        elapsed_time1 = (t2 - t1)*1000000

        # print(f"信息提取用时: {elapsed_time1} 微秒")


        # 将订单结果DataFrame保存到新文件

        # results_df.to_excel('E:\\Paichan_FJSP\\data_sql\\output_result_2.xlsx', index=False)



    if selected_device:

        print(f"订单号：{order_row['group_sn']}")

        # print(f"单双面打印：{order_row['printSide']}")

        # print(f"选择的印刷设备是：{selected_device.device_name}")

        # print(f"印刷时间：{printing_time}分钟")



        # 更新DataFrame中的数据

        index = df[df['group_sn'] == order_row['group_sn']].index

        if not index.empty:

            index = index[0]  # 获取订单的索引

            df.at[index, 'selected_device'] = selected_device.device_name

            df.at[index, 'printing_time'] = printing_time



# 处理订单

for index, row in df.iterrows():
    
    process_order(index, row)

df.to_excel('E:\\tmp\\output_result_01.xlsx', index=False)


# print("已保存数据到Excel文件")

# print(results_df[['group_sn', 'selected_device', 'printing_time']]) #results_df 中有一些重复的订单号，因为在处理订单时，每次都会将结果附加到 results_df 中，即使订单号重复

# print(df[['group_sn', 'selected_device', 'printing_time']])  #df 中没有重复的订单号



# 记录结束时间

end_time = time.time()

elapsed_time = end_time - start_time

print(f"信息提取用时: {elapsed_time} 秒")

