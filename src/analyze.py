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
    try:
        arucoCorners, arucoIds, rejectedCorners = recognise.find_aruco_markers(
            cv2.cvtColor(image, cv2.COLOR_BGR2GRAY))
        playfieldCorners = recognise.aruco_to_playfield_corners(
            arucoCorners, arucoIds)
        # Draw final image with overlays
        #cv2.drawContours(displayImage, np.array(
            #[playfieldCorners], dtype=np.int32), -1, (0, 0, 255), 5)
        #for idx, corner in enumerate(playfieldCorners):
            #cv2.putText(displayImage, str(idx), corner,
                        #cv2.FONT_HERSHEY_SIMPLEX, 10, (0, 255, 0), 4)
            #cv2.putText(displayImage, str(
                #arucoIds[idx]), corner, cv2.FONT_HERSHEY_SIMPLEX, 10, (255, 0, 0), 4)

    # Cut image and draw dot matrix
    cutOutImage = util.cut_out_image(image, playfieldCorners, (1000, 1000))
    #util.draw_dot_matrix(cutOutImage, (48, 48), (4, 0), (992, 994))

    # Display final images
    cv2.imshow("Output image", util.fit_display(cutOutImage))
    cv2.waitKey(1)
    #projection.show_image_fullscreen(util.fit_display(cutOutImage))
    return cutOutImage


