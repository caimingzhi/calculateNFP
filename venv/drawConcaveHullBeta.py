from shapely.wkt import loads
from shapely import Polygon
import numpy as np
# import subprocess


"""
This is a Ramer-Douglas-Peucker implementation that only expands the shape.
In other words, it guarantees that the original polygon is strictly contained within the new (simplified) polygon.
It does this by a slight modification of RDP: whenever we remove a point, if that point is outside the polygon,
shift the line parallel to itself to intersect that point.

There are no guarantees on whether the points of the simplified polygon are a subset of the original set of points.
Indeed, in many cases they won't be.

Usage:
  rdp(points, epsilon)
    - points should be a 2d numpy array with dimensions (n, 2). Moreover, points[-1] should equal points[0] -- i.e. points should form a closed polygon.
    - epsilon is the epsilon parameter in RDP
    - The return value is a 2d numpy array that approximates the original polygon while containing fewer segments. It may not be closed.

  rdp_closed(points, epsilon)
    - Just like rdp but guarantees that the return value will also be a closed polygon.
      This is most likely what you want most of the time.
"""


def line_dists(points, start, end):
  """
  Returns the signed distances of each point to start and end
  """
  if np.all(start == end):
    return np.linalg.norm(points - start, axis=1)

  vec = end - start
  cross = np.cross(vec, start - points)
  dvalue = np.divide( cross, np.linalg.norm(vec))
  # print("======")
  # print(dvalue)
  # print("------")
  return np.divide(cross, np.linalg.norm(vec))


def glue(seg1, seg2):
  """
  Glues two segments together
  In other words, given segments A and B which have endpoints
  that are close together, computes a "glue point" that both segments
  can be extended to in order to intersect.
  Assumes seg1 and seg2 are arrays containing two points each,
  and that if seg1 = [a, b], it can be extended in the direction of b,
  and if seg2 = [c, d], it can be extended in the direction of c.
  """

  x1 = seg1[0]
  dir1 = seg1[1] - x1
  x2 = seg2[0]
  dir2 = seg2[1] - x2

  # The set of points that are on segment 1 treated as a ray is x1 + dir1 * t for all t >= 0
  # Similarly for segment 2, but for s <= 1
  # We set up the system:
  #     x1 + dir1 * t = x2 + dir2 * s
  # --> dir1 * t + dir2 * (-s) = x2 - x1
  # --> [dir1, dir2] * [t, -s] = x2 - x1
  mat = np.matrix([dir1, dir2]).T
  # Solve for the vector [t, -s]
  try:
    t_s = np.array((np.linalg.inv(mat) @ (x2 - x1))).flatten()
    # Recall that we can't make a segment go in a backwards direction
    # So we must have t >= 0 and s <= 1. However, since we solved for [t, -s]
    # we want that t_s[0] >= 0 and t_s[1] >= -1. If this fails, set t_s to None
    # Also, don't allow segments to more than double
    if not ((0 <= t_s[0] <= 2) and (-1 <= t_s[1] <= 1)):
      t_s = None
  except np.linalg.LinAlgError:
    # Singular matrix i.e. parallel
    t_s = None
  if t_s is None:
    # Just connect them with a line
    return np.array([seg1[1], seg2[0]])
  else:
    # x1 + dir1 * t_s[0] and x2 - dir2 * t_s[1] Should be the same
    return np.array([x1 + dir1 * t_s[0]])


def __rdp(points, epsilon):
  """Computes expansion only rdp assuming a clockwise orientation"""
  start, end = points[0], points[-1]
  dists = line_dists(points, start, end)

  # First compute the largest point away from the line just like the ordinary RDP
  index = np.argmax(np.abs(dists))
  dmax = abs(dists[index])

  if dmax > epsilon:
    result1 = __rdp(points[:index + 1], epsilon)
    result2 = __rdp(points[index:], epsilon)
    result = np.vstack((result1[:-1], glue(result1[-2:], result2[:2]), result2[1:]))
  else:
    # All points are within epsilon of the line
    # We take the point furthest *outside* the boundary (i.e. with negative distance)
    # and shift the line segment parallel to itself to intersect that point
    new_start, new_end = np.copy(start), np.copy(end)
    vec_x, vec_y = (end - start)
    norm = np.sqrt(vec_x * vec_x + vec_y * vec_y)
    if norm != 0:
      vec_rot90 = np.array([-vec_y, vec_x]) / norm
      # TODO -- verify that this works: can optimize so that if dists[index] < 0, no need to search again, we have index_min = index and dmin = -dmax
      index_min = np.argmin(dists)
      dmin = -dists[index_min]
      if dmin > 0:
        vec_rot90 *= dmin
        new_start += vec_rot90
        new_end += vec_rot90
    result = np.array([new_start, new_end])

  return result


def rdp(points, epsilon=0):
  """Computes expansion only rdp with no assumptions on orientation"""
  if orientation(points):
    return __rdp(points, epsilon)
  else:
    return __rdp(points[::-1], epsilon)[::-1]


def rdp_closed(points, epsilon=0):
  """Ensure that expansion only rdp returns a closed loop at the end"""
  new_points = rdp(points, epsilon)
  glue_pts = glue(new_points[-2:], new_points[:2])
  if len(glue_pts) == 1:
    return np.vstack((glue_pts, new_points[1:-1], glue_pts))
  else:
    return np.vstack((new_points, [new_points[0]]))


def orientation(points):
  """Returns true if the points area in a clockwise order"""
  x, y = points.T
  # Compute signed area and compare with 0
  return np.dot(x,np.roll(y,1))-np.dot(y,np.roll(x,1)) >= 0

def test( file_path ):
  import matplotlib.pyplot as plt
  def make_points():
    # file_path = 'D:\\试用期考核\\拼板方案\\test04.txt' 
    with open(file_path, 'r') as file:
        all_data = file.read()
    wkt_data = all_data
    multipolygonSource = loads(wkt_data)
    multipolygon = Polygon(multipolygonSource.buffer(3*(72/25.4)))
    # multipolygon = Polygon(multipolygonSource.buffer(0))
    # print( multipolygon )
    polygons = []

    coordinates = np.array(multipolygon.exterior.coords)
    polygons.append(coordinates)

    # for polygon in multipolygon.geoms:
    #     # Extract exterior coordinates of the polygon
    #     coordinates = np.array(polygon.exterior.coords)
    #     polygons.append(coordinates)
    
    # polygons_array = np.array(polygons[3])
    # return polygons_array 
    return polygons 

  def pprint_numpy(points):
    for x, y in points:
      print(f'({x:.2f}, {y:.2f})', end=', ')
    print("\n")

  def plot_points(pts):
    # plt.plot(pts.T[0], pts.T[1])
    plt.plot(np.array(pts)[:, 0], np.array(pts)[:, 1])


  pts = make_points()
  # with open('pts_rdp_data.txt', "ab") as f:
  file_path = 'your_file.txt'



  with open('file4.txt', "ab") as f:
    for thisPolygon in pts:
      theP = np.array(thisPolygon)
      theP /=  (72 / 25.4)
      print(f"Size of the theP: {theP.shape}")
      # plot_points( theP )
      pts_rdp = rdp_closed( theP, 3/(72/25.4) )
      print(pts_rdp)
      # plot_points( pts_rdp )
      print(f"Size of pts_rdp : {pts_rdp.shape}")
      # np.savetxt('pts_rdp_data.txt', pts_rdp.T[0, : ], fmt='%.2f', delimiter=' ')
      # np.savetxt( f, pts_rdp[ -2::-1, 0 ], fmt='%.2f', delimiter='', newline= " ")
      # f.write(b"\n")
      # np.savetxt( f, pts_rdp[ -2::-1, 1 ], fmt='%.2f', delimiter='', newline= " ")
      # f.write(b"\n")
      line_to_write_x = ' '.join(map(lambda x: f"{x:.2f}", pts_rdp[-2::-1, 0]))
      line_to_write_x = line_to_write_x.rstrip()
      f.write(line_to_write_x.encode() + b"\n")
      # Save the y-coordinates without trailing space
      line_to_write_y = ' '.join(map(lambda y: f"{y:.2f}", pts_rdp[-2::-1, 1]))
      line_to_write_y = line_to_write_y.rstrip()
      f.write(line_to_write_y.encode() + b"\n")

  # plot_points(pts_rdp)
  # plot_points(pts)
  # pts_rdp = rdp_closed(pts, 4)
  # plot_points(pts_rdp)
  # print("Original:")
  # pprint_numpy(pts)
  # print("\nReduced:")
  # pprint_numpy(pts_rdp)

  plt.show()

if __name__ == "__main__":
  with open("file4.txt", 'w'):
    pass
#   string_array = [
#     "PO2022051295281148",
#     "PO2022050615264021",
#     "PO2022050121748498",
#     "PO2022050446111968",
#     "PO2022051281459188",
#     "PO2022050736523708",
#     "PO2022051047257115",
#     "PO2022050746314260",
#     "PO2022050642243033-2-1"

# ]
    string_array = [
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8"

]
  
  mode_number = [ 3, 1, 1, 1, 1, 1, 1, 1 ]
  # mode_number = [ 1, 1, 4 ]
  for thisIndex in range(0, len(mode_number) ):
    # print("##################")
    print( thisIndex )
    thisNum = mode_number[thisIndex]
    while thisNum > 0:
      # headPath = "D:\\试用期考核\\拼板方案\\1001PO文件\\PO文件"
      headPath = "E:\\tmp\\test\\beta"
      targetPo = string_array[thisIndex] + ".txt"
      finalPath = headPath + "\\" + targetPo
      # print(finalPath)
      test( finalPath )
      thisNum -= 1
      


# Specify the file path
file_path = 'D:\\试用期考核\\拼板方案\\test03.txt'  # Replace with the actual file path

# Open the file and read all the data
with open(file_path, 'r') as file:
    all_data = file.read()

# Print or manipulate the data as needed
# print(all_data)


# WKT data
wkt_data = all_data

# Parse WKT and convert to NumPy arrays
multipolygon = loads(wkt_data)

# Initialize an empty list to store individual polygons
polygons = []

# Iterate over each polygon in the MultiPolygon
for polygon in multipolygon.geoms:
    # Extract exterior coordinates of the polygon
    coordinates = np.array(polygon.exterior.coords)
    polygons.append(coordinates)

# Convert the list of polygons to a NumPy array
polygons_array = np.array(polygons[0])

# Print the result
# print(polygons_array)


