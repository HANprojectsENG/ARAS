import numpy as np
from enum import Enum
import analyze
import coordinates
import cv2
import cv2.aruco as aruco


class BrickColor(Enum):
    ORANGE = 106
    GREEN = 37
    YELLOW = 24
    BLUE = 23
    RED = 21


COLOR_RANGES = {
    BrickColor.ORANGE: (np.array([0, 128, 60]), np.array([10, 255, 255])),
    BrickColor.GREEN: (np.array([70, 192, 20]), np.array([90, 255, 128])),
    BrickColor.YELLOW: (np.array([15, 108, 148]), np.array([35, 192, 255])),
    BrickColor.BLUE: (np.array([100, 192, 128]), np.array([120, 255, 255])),
    BrickColor.RED: (np.array([160, 162, 96]), np.array([180, 255, 255]))
}

MARKER_CORNER_IDX = {
    41: 1,
    42: 1,
    43: 3,
    44: 3
}

# Marker IDs in clockwise order starting at left-top
MARKER_IDS = [42, 43, 41, 44]


def filter_brick_color(hsvImage, color):
    brickMask = cv2.inRange(
        hsvImage, COLOR_RANGES[color][0], COLOR_RANGES[color][1])
    return brickMask


def filter_bricks(bgrImage):
    hsvImage = cv2.cvtColor(bgrImage, cv2.COLOR_BGR2HSV)
    colorBrickImage = np.zeros(hsvImage.shape, dtype=np.uint8)

    for member in list(BrickColor):
        divBy = np.array([255], dtype=np.uint8)
        colorBrickImage += cv2.bitwise_and(
            bgrImage,
            cv2.cvtColor(filter_brick_color(hsvImage, member), cv2.COLOR_GRAY2BGR))

    return colorBrickImage


def find_bricks_by_color(bgrImage):
    hsvImage = cv2.cvtColor(bgrImage, cv2.COLOR_BGR2HSV)
    displayImage = cv2.cvtColor(
        (bgrImage * 0.5).astype(np.uint8), cv2.COLOR_BGR2HSV)
    bricks = []

    for member in list(BrickColor):
        filteredBrickImage = filter_brick_color(hsvImage, member)
        contours = cv2.findContours(
            filteredBrickImage, cv2.RETR_LIST, cv2.CHAIN_APPROX_TC89_L1)
        color = (COLOR_RANGES[member][0] + COLOR_RANGES[member][1]) / 2
        cv2.drawContours(
            displayImage, contours[0], -1, tuple(map(int, color)), 10)
        bricks.append((member, contours))

    return (bricks, cv2.cvtColor(displayImage, cv2.COLOR_HSV2BGR))


def find_aruco_markers(grayImage):
    aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_100)
    parameters = aruco.DetectorParameters_create()
    corners, ids, rejectedImgPoints = aruco.detectMarkers(
        grayImage, aruco_dict, parameters=parameters)
    return (corners, ids, rejectedImgPoints)


def aruco_to_playfield_corners(corners, ids):
    playfieldCorners = [0] * len(ids)

    for idx, markerCorners in enumerate(corners):
        playfieldCorners[MARKER_IDS.index(int(ids[idx]))] = tuple(
            map(int, markerCorners[0][MARKER_CORNER_IDX[int(ids[idx])]]))

    return playfieldCorners


def get_playfield_corners_by_aruco(grayImage):
    corners, ids, rejectedImgPoints = find_aruco_markers(grayImage)
    playfieldCorners = aruco_to_playfield_corners(corners, ids)
    return playfieldCorners


def check_color(bgrImage):
    # Check if color of brick is correct
    hsv = cv2.cvtColor(bgrImage, cv2.COLOR_BGR2HSV)
    avg_color_per_row = np.average(hsv, axis=0)
    avg_color = np.average(avg_color_per_row, axis=0)
    int_avg_color = np.array(avg_color, dtype=np.uint8)
    for member in list(BrickColor):
        if compare_color(int_avg_color, COLOR_RANGES[member][0], COLOR_RANGES[member][1]):
            return(member)
    return("BrickColor.UNKNOWN")


def compare_color(avg_color, COLOR_MIN, COLOR_MAX):
    # Compare avg color of an area to expected color values
    for i in range(0, 3):
        if avg_color[i] < COLOR_MIN[i] or avg_color[i] > COLOR_MAX[i]:
            return False
    return True

   
def crop_image(image, pos_x1,pos_y1,pos_x2,pos_y2, destination_pos, destination_size):
    if pos_x2 < pos_x1 or pos_y2 < pos_y1:
        print("recognition error: bad data in sequence file cannot crop")
    #Create matrix 
    matrix = coordinates.calculate_nub_coordinate_matrix(
        destination_pos, destination_size)
    layer = 0

    #Get Top left pixel coordinates of lego brick
    coord_x1 = int(matrix[layer, pos_x1, pos_y1, 0] - 8)
    coord_y1 = int(matrix[layer, pos_x1, pos_y1, 1] - 8)

    #Get bottom right pixel coordinates of lego brick
    coord_x2 = int(matrix[layer, pos_x2, pos_y2, 0] + 10)
    coord_y2 = int(matrix[layer, pos_x2, pos_y2, 1] + 10)

    #Crop image to the pixel boundries
    crop_img = image[coord_y1:coord_y2, coord_x1:coord_x2]
    return crop_img


def test_cropping(cutOutImage):
    #Test crop for specific brick
    testimage = crop_image(cutOutImage,362,408,408,450)
    print(check_color(testimage))
    cv2.imshow("test image", testimage)



def test_recognition_system(data,imagePath):
    image = analyze.get_image(imagePath)
    #layer. step. legosize(in nobs). color. posx1. posy1. posxn. posyn
    print("Layer: " +
                      str(data[0]) + " Step: " + str(data[1]) + " size: " + str(data[2]) + " color: " + str(data[3]) + " x1: " + str(data[4]) + " y1: " + str(data[5]) + "...")
    
    #crop image to the size of one lego brick from top left to bottom right stud                  
    testimage = crop_image(image, data[4], data[5], data[((data[2] * 2) + 2)], data[((data[2] * 2) + 3)],(4, 0), (992, 994))

    #Print color of brick
    print(check_color(testimage))
    cv2.imshow("test image", testimage)
    return True

