import math


headPath = "E:\\tmp\\groupMessage\\Group69\\"
file = headPath + "rateCache.txt"
fileSource = headPath + "groupIDAndArea2.txt"
path_number = headPath + "groupIDAndMode2.txt"
path_group = headPath + "groupNum2.txt"


data_list = []

with open( file, 'r' ) as file:
    for line in file:
        pairs = line.strip().split(' ')
        data_dict = {}
        for pair in pairs:
            key, value = pair.split(':')
            data_dict[key.strip()] = value.strip()
        data_list.append(data_dict)


dataSource = []
with open( fileSource, 'r' ) as file:
    lines = file.readlines()
    # print( lines )
    for line in lines:
        thisData = line.strip().split(',')
        # print(thisData)
        data_tuple = ( int(thisData[0]), int( thisData[1]), int( thisData[2]) )
        dataSource.append(data_tuple)



poNumber = []
with open( path_number, 'r') as file:
    for line in file:
        value = line.strip().split(',')
        data_tuple = (int(value[0]), value[1],int(value[2]))
        poNumber.append(data_tuple)


group_number = []
with open( path_group, 'r' ) as file:
    for line in file:
        value = line.strip().split(',')
        data_tuple = ( int(value[0]), int(value[1]) )
        group_number.append(data_tuple)


print(len(data_list))

the_four_machin_size = [
    [759, 310],
    [740, 297], 
    [745, 297], 
    [750, 300] 
]

def choose_four(max_val, min_val, four_machine_size):
    for size in four_machine_size:
        if max_val <= size[0] and min_val >= size[1]:
            return True
    return False

allTotallPrize = 0

for index in range(0, len(data_list) ):
    print(index)
    filtered_data = [ data for data in data_list if data.get('groupID') == str(index)]
    height = float(filtered_data[0].get("height")) + 15
    width = float(filtered_data[0].get("width")) + 12
    # filtered_data = [ data for data in dataSource if data[0] == index ]
    # height = float(filtered_data[0][1])
    # width = float(filtered_data[0][2])
# 639256.0037463378
# 703740.8398799999
    poNumberFiltered = [ data for data in poNumber if data[0] == index ]
    modeNumber = []
    for data in poNumberFiltered :
        modeNumber.append(data[2])
    group_filtered = [ data for data in group_number if data[0] == index ]
    groupNumber = group_filtered[0][1]
    
    thisPrintNum = groupNumber
    losePaper = 150 + 50 * (math.ceil( thisPrintNum / 1000 ) - 1 )
    thisPrintNum += losePaper
    max = width
    min = height
    if( width < height ) : 
        max = height
        min = width
    basePrize = 330.0
    abovePrize = 0.07
    if(choose_four( max, min, the_four_machin_size )):
        basePrize = 230
        abovePrize = 0.05
    totalPaperSize = max * min * 1e-6 * thisPrintNum
    printPrice = basePrize + abovePrize * 1000 * (math.ceil( thisPrintNum / 1000 ) - 1 )
    paperPrice = 7000 * totalPaperSize * 350 * 1e-6
    surfPrice = (0.35 * totalPaperSize) if  ( (0.35 * totalPaperSize) > 250 ) else 250
    biePrice =  ( 0.1 * thisPrintNum )  if (( 0.1 * thisPrintNum ) > 150) else 150 
    dieCutPrice = 200
    nianPriceTotall = 0
    for num in modeNumber:
        nianPrice = 0.07 * num * thisPrintNum
        nianPriceTotall += nianPrice if nianPrice > 80 else 80
    totallPrice = printPrice + paperPrice + surfPrice + biePrice + dieCutPrice + nianPriceTotall
    allTotallPrize += totallPrice

print(allTotallPrize)
    








