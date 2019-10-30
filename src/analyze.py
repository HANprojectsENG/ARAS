import numpy as np
import util
import recognise
import projection
from enum import Enum
import cv2
import cv2.aruco as aruco



def get_image(imagePath):
    image = util.white_balance(cv2.imread(imagePath))
    #displayImage = recognise.find_bricks_by_color(image)[1]
    # Try and find aruco codes
    arucoCorners, arucoIds = recognise.find_aruco_markers(
        cv2.cvtColor(image, cv2.COLOR_BGR2GRAY), 4)
    playfieldCorners = recognise.aruco_to_playfield_corners(
        arucoCorners, arucoIds)

    # Cut image and draw dot matrix
    cutOutImage = util.cut_out_image(image, playfieldCorners, (1000, 1000))

    # Display final images
    cv2.imshow("Output image", util.fit_display(cutOutImage))
    cv2.waitKey(1)
    return cutOutImage


