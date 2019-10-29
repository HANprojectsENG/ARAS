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

class FilterMethod(Enum):
    HSV = 1
    HSV_EUCLIDEAN = 2
    BGR = 3
    BGR_EUCLIDEAN = 4

COLOR_RANGES_HSV = {
    BrickColor.ORANGE: (np.array([0, 128, 60]), np.array([10, 255, 255])),
    BrickColor.GREEN: (np.array([70, 192, 20]), np.array([90, 255, 128])),
    BrickColor.YELLOW: (np.array([15, 108, 148]), np.array([35, 192, 255])),
    BrickColor.BLUE: (np.array([100, 192, 128]), np.array([120, 255, 255])),
    BrickColor.RED: (np.array([160, 162, 96]), np.array([180, 255, 255]))
}

HSV_MAX_DISTANCE = 50

COLOR_RANGES_BGR = {
    BrickColor.ORANGE: (np.array([0, 30, 60]), np.array([30, 85, 255])),
    BrickColor.GREEN: (np.array([10, 20, 0]), np.array([128, 128, 5])),
    BrickColor.YELLOW: (np.array([63, 117, 148]), np.array([85, 255, 223])),
    BrickColor.BLUE: (np.array([128, 0, 0]), np.array([255, 96, 32])),
    BrickColor.RED: (np.array([0, 0, 96]), np.array([76, 35, 255]))
}

BGR_MAX_DISTANCE = 30

def calculate_euclidean_distance(image1, image2):
    absdiffImage = cv2.absdiff(image1, image2)
    normImage = np.linalg.norm(absdiffImage, axis=2)
    return normImage


def filter_brick_color(bgrImage, color, filterMethod):
    brickMask = None
    if filterMethod == FilterMethod.HSV:
        hsvImage = cv2.cvtColor(bgrImage, cv2.COLOR_BGR2HSV)
        brickMask = cv2.inRange(
            hsvImage, COLOR_RANGES_HSV[color][0], COLOR_RANGES_HSV[color][1])
    elif filterMethod == FilterMethod.HSV_EUCLIDEAN:
        hsvImage = cv2.cvtColor(bgrImage, cv2.COLOR_BGR2HSV)
        expectedColor = (COLOR_RANGES_HSV[color][0] + COLOR_RANGES_HSV[color][1]) // 2
        distImage = calculate_euclidean_distance(hsvImage, np.full(hsvImage.shape, expectedColor, dtype=np.uint8))
        brickMask = cv2.inRange(
            distImage, np.array([0]), np.array([HSV_MAX_DISTANCE]))
    elif filterMethod == FilterMethod.BGR:
        brickMask = cv2.inRange(
            bgrImage, COLOR_RANGES_BGR[color][0], COLOR_RANGES_BGR[color][1])
    elif filterMethod == FilterMethod.BGR_EUCLIDEAN:
        expectedColor = (COLOR_RANGES_BGR[color][0] + COLOR_RANGES_BGR[color][1]) // 2
        distImage = calculate_euclidean_distance(bgrImage, np.full(bgrImage.shape, expectedColor, dtype=np.uint8))
        brickMask = cv2.inRange(
            distImage, np.array([0]), np.array([BGR_MAX_DISTANCE]))

    return brickMask


def find_bricks_by_color(bgrImage, filterMethod):
    displayImage = (bgrImage * 0.1).astype(np.uint8)
    atopBgrImage = (bgrImage * 0.3).astype(np.uint8)
    bricks = []

    for member in list(BrickColor):
        filteredBrickImage = filter_brick_color(bgrImage, member, filterMethod)
        contours = cv2.findContours(
            filteredBrickImage, cv2.RETR_LIST, cv2.CHAIN_APPROX_TC89_L1)
        color = (COLOR_RANGES_BGR[member][0] + COLOR_RANGES_BGR[member][1]) / 2
        displayImage += cv2.bitwise_and(
            atopBgrImage,
            cv2.cvtColor(filteredBrickImage, cv2.COLOR_GRAY2BGR))
        cv2.drawContours(
            displayImage, contours[0], -1, tuple(map(int, color)), 2)
        bricks.append((member, contours))

    return (bricks, displayImage)
