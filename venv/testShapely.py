from shapely import Point
from shapely import Polygon
rectPolygon = Polygon([[0, 0], [1, 0], [1, 1], [0, 1], [0, 0]]).buffer(1)
print(rectPolygon)