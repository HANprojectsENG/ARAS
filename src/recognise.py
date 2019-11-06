import numpy as np
from enum import Enum
import analyze
import util
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
    BrickColor.ORANGE: (np.array([5, 128, 60]), np.array([15, 255, 255]), np.array([0, 128, 255])),
    BrickColor.GREEN: (np.array([64, 192, 20]), np.array([90, 255, 128]), np.array([0, 155, 0])), #Changed lower h value
    BrickColor.YELLOW: (np.array([15, 108, 148]), np.array([35, 200, 255]), np.array([51, 255, 255])), #changed higher s value
    BrickColor.BLUE: (np.array([100, 192, 128]), np.array([120, 255, 255]), np.array([255, 51, 51])),
    BrickColor.RED: (np.array([140, 162, 96]), np.array([180, 255, 255]), np.array([00, 0, 200])) #Changed lower h value
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


def find_aruco_markers(grayImage, expectedCorners):
    aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_100)
    parameters = aruco.DetectorParameters_create()
    allIds = []
    allCorners = []
    for i in range(1, 255, 10):
        corners, ids, rejectedImgPoints = aruco.detectMarkers(
            cv2.inRange(grayImage, i, 255), aruco_dict, parameters=parameters)
        if ids is not None:
            for idx, mid in np.ndenumerate(ids):
                if int(mid) not in allIds:
                    allIds.append(np.array([mid]))
                    allCorners.append(corners[int(idx[0])])

            if len(allIds) == expectedCorners:
                return (allCorners, np.array(allIds, dtype=np.uint32))
    return (allCorners, np.array(allIds, dtype=np.uint32))


def aruco_to_playfield_corners(corners, ids):
    playfieldCorners = [0] * len(ids)

    for idx, markerCorners in enumerate(corners):
        playfieldCorners[MARKER_IDS.index(int(ids[idx]))] = tuple(
            map(int, markerCorners[0][MARKER_CORNER_IDX[int(ids[idx])]]))

    return playfieldCorners


def check_color(bgrImage):
    # Check if color of brick is correct
    hsv = cv2.cvtColor(bgrImage, cv2.COLOR_BGR2HSV)
    avg_color_per_row = np.average(hsv, axis=0)
    avg_color = np.average(avg_color_per_row, axis=0)
    int_avg_color = np.array(avg_color, dtype=np.uint8)
    print("avg_color:" + str(int_avg_color))
    for member in list(BrickColor):
        if compare_color(int_avg_color, COLOR_RANGES[member][0], COLOR_RANGES[member][1]):
            return(member.value)
        if member.value == 21: #Special case for red brick. Wrapping around HSV value
            if compare_color(int_avg_color, [0, 162, 96], [5, 255, 255]): 
                return(member.value)
    return(0)


def compare_color(avg_color, COLOR_MIN, COLOR_MAX):
    # Compare avg color of an area to expected color values
    for i in range(0, 3):
        if avg_color[i] < COLOR_MIN[i] or avg_color[i] > COLOR_MAX[i]:
            return False
    return True

def recognition(data,cropped_image, matrix):
    #layer. step. legosize(in nobs). color. posx1. posy1. posxn. posyn
    #print("Layer: " + str(data[0]) + " Step: " + str(data[1]) + " size: " + str(data[2]) + " color: " + str(data[3]) + " x1: " + str(data[4]) + " y1: " + str(data[5]) + "...")
    
    layer = data[0]
    print(int(matrix[layer,0,1,0]) - int(matrix[layer,0,0,0]))
    distance_between_nubs = int(matrix[layer,0,1,0]) - int(matrix[layer,0,0,0])
    for i in range(0,data[2]):
        pos_x = data[2 * i + 4]
        pos_y = data[2 * i + 5]
        #Get Top left pixel coordinates of lego stud
        coord_x1 = int(matrix[layer, pos_x, pos_y, 0] - distance_between_nubs / 4)
        coord_y1 = int(matrix[layer, pos_x, pos_y, 1] - distance_between_nubs / 4)

        #Get bottom right pixel coordinates of lego stud
        coord_x2 = int(matrix[layer, pos_x, pos_y, 0] + distance_between_nubs / 4)
        coord_y2 = int(matrix[layer, pos_x, pos_y, 1] + distance_between_nubs / 4)

        #Crop image to the pixel boundries
        cropped_stud = cropped_image[coord_y1:coord_y2, coord_x1:coord_x2]

        #Get resulting color of cropped stud
        result = check_color(cropped_stud)

        #Compare result with expected color
        if (result != data[3]):
            color = (0,0,0)
            thickness = 2
            start_point = (coord_x1,coord_y1)
            end_point = (coord_x2,coord_y2)
            cv2.imshow("failed", util.fit_display(cv2.rectangle(cropped_image, start_point, end_point, color, thickness)))
            print("pos:" + str(data[2 * i + 4]) + "," + str(data[2 * i + 5]) + " failed")
            if (result == 0):
                print("expected:" + str([BrickColor(data[3])]) + "\ndetected:" + str("unknown"))
            else: 
                print("expected:" + str([BrickColor(data[3])]) + "\ndetected:" + str([BrickColor(result)]))

            color2 = (int(COLOR_RANGES[BrickColor(data[3])][2][0]),int(COLOR_RANGES[BrickColor(data[3])][2][1]),int(COLOR_RANGES[BrickColor(data[3])][2][2]))

            #Get Top left pixel coordinates of lego stud
            coord2_x1 = int(matrix[layer, data[4], data[5], 0] - distance_between_nubs / 2)
            coord2_y1 = int(matrix[layer, data[4], data[5], 1] - distance_between_nubs / 2) + 10

            #Get bottom right pixel coordinates of lego stud
            coord2_x2 = int(matrix[layer, data[2 * data[2] + 2], data[2 * data[2] + 3], 0] + distance_between_nubs / 2)
            coord2_y2 = int(matrix[layer, data[2 * data[2] + 2], data[2 * data[2] + 3], 1] + distance_between_nubs / 2) + 10

            start2 = (coord2_x1,coord2_y1)
            end2 = (coord2_x2,coord2_y2)

            cv2.imshow("next", util.fit_display(cv2.rectangle(cropped_image, start2, end2, color2, 2)))
            return False
    print("Layer:" + str(data[0]) + " Step:" + str(data[1]) + " Passed")
    return True
