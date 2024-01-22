from shapely.wkt import loads

# Define the WKT representation of the polygon
import matplotlib.pyplot as plt

 
with open('D:\试用期考核\拼板方案\polygons\poly01.txt', "r") as file:
    for line in file:
        polygon = line

wkt_polygon = line
# Parse the WKT into a Shapely geometry object
polygon = loads(wkt_polygon)

# Check if the polygon is valid
if polygon.is_valid:
    print("The polygon is valid.")
else:
    print("The polygon is not valid.")

# You can perform various operations on the polygon, such as calculating its area or perimeter.
area = polygon.area
perimeter = polygon.length

print("Area:", area)
print("Perimeter:", perimeter)
