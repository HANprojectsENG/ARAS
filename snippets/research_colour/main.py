from recognise import FilterMethod, find_bricks_by_color
import cv2
import sys

if len(sys.argv) < 3:
    print(sys.argv[0] + " <image file name> <bgr|bgr_euclid|hsv|hsv_euclid>")
    exit(1)

filterMethod = None
if sys.argv[2] == "bgr":
    filterMethod = FilterMethod.BGR
elif sys.argv[2] == "bgr_euclid":
    filterMethod = FilterMethod.BGR_EUCLIDEAN
elif sys.argv[2] == "hsv":
    filterMethod = FilterMethod.HSV
elif sys.argv[2] == "hsv_euclid":
    filterMethod = FilterMethod.HSV_EUCLIDEAN
else:
    print("Invalid filter method " + sys.argv[2])
    exit(2)


img = cv2.imread(sys.argv[1])
filteredImg = find_bricks_by_color(img, filterMethod)[1]
cv2.namedWindow("test", cv2.WINDOW_NORMAL)
cv2.resizeWindow("test", 600, 600)
cv2.imshow("test", filteredImg)
while cv2.waitKey(100) != ord("q"):
    pass
