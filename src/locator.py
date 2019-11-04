import numpy as np
import util
import time
import recognise
import camera
import statemachine
from enum import Enum
from constants import BOARD_LOCATION_MARGIN
import cv2
import cv2.aruco as aruco
thread_running = True


def checkLocation(imagePath):
    global thread_running
    oldCorners = []
    while True:
        if statemachine.stop_threads: 
            break
      
        if imagePath == True:
            image = cv2.resize(camera.capture(),None,fx=0.25,fy=0.25)
        else:
            image = cv2.resize(cv2.imread(imagePath),None,fx=0.25,fy=0.25)

        arucoCorners, arucoIds = recognise.find_aruco_markers(cv2.cvtColor(image, cv2.COLOR_BGR2GRAY), 4)
        corners = recognise.aruco_to_playfield_corners(arucoCorners, arucoIds)

        if len(corners) < 4 or len(corners) > 4:
            # ignore check if wrong amount of corners found
            thread_running = True
            time.sleep(0.6)
        else:
            thread_running, oldCorners = checkCornerLocation(corners, oldCorners)
            time.sleep(0.6)
      
  
def checkCornerLocation(corners, oldCorners):

    if len(oldCorners) != 4:
        return True, corners
    else:
        #compare corner locations here
        for i in range (0,4):
          for j in range(0,2):
            if (corners[i][j] - oldCorners[i][j]) > BOARD_LOCATION_MARGIN or (corners[i][j] - oldCorners[i][j]) < -BOARD_LOCATION_MARGIN:
                return False, corners

        return True, corners
