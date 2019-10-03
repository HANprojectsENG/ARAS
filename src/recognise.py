import numpy as np
from enum import Enum
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
