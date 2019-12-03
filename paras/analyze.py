import numpy as np
import util
import recognise
import projection
import camera
from enum import Enum
import cv2
import cv2.aruco as aruco

arucoIdsOLD = []
arucoCornersOLD = []

def get_image(imagePath):
    global arucoIdsOLD
    global arucoCornersOLD
    if imagePath == True:
        image = util.white_balance(camera.capture())
    else:
        image = util.white_balance(cv2.imread(imagePath))
    #displayImage = recognise.find_bricks_by_color(image)[1]
    # Try and find aruco codes
    arucoCorners, arucoIds = recognise.find_aruco_markers(
        cv2.cvtColor(image, cv2.COLOR_BGR2GRAY), 4)
    if len(arucoCorners) != 4:
        arucoIds = arucoIdsOLD
        arucoCorners = arucoCornersOLD
    else:
        arucoIdsOLD = arucoIds
        arucoCornersOLD = arucoCorners

    if len(arucoCorners) != 4 or len(arucoCornersOLD) != 4:
        raise ValueError("Expected 4 markers, found " + str(len(arucoCorners)))

    playfieldCorners = recognise.aruco_to_playfield_corners(
        arucoCorners, arucoIds)

    # Cut image and draw dot matrix
    cutOutImage = util.cut_out_image(image, playfieldCorners, (1000, 1000))

    # Display final images
    cv2.imshow("Output image", util.fit_display(cutOutImage))
    cv2.waitKey(1)
    return cutOutImage