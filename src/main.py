# import the necessary packages
import numpy as np
import os
import cv2
import argparse
import recognise
import util
import projection
import camera
import vscodeargs
import lsfparser
import statemachine


def main(FilePath):
    loadedSequence = lsfparser.openFile(filePath)
    try:
        camera.init()
        while True:
            image = camera.capture()

            dispImage = image.copy()
            playfieldCorners = recognise.get_playfield_corners_by_aruco(
                cv2.cvtColor(image, cv2.COLOR_BGR2GRAY))

            for playfieldCorner in playfieldCorners:
                cv2.circle(dispImage, playfieldCorner,
                           25, (0, 0, 255), cv2.FILLED)

            # show the frame
            cv2.imshow("Playfield", util.fit_display(
                util.cut_out_image(dispImage, playfieldCorners, (1000, 1000))))
            key = cv2.waitKey(1) & 0xFF

            # clear the stream in preparation for the next frame
            rawCapture.truncate(0)

            # if the `q` key was pressed, break from the loop
            if key == ord("q"):
                break
    except:
        print("Camera is gone :/")


def test_main(imagePath, filePath, savePath):
    # Load files
    loadedSequence = lsfparser.openFile(filePath)
    image = util.white_balance(cv2.imread(imagePath))
    # This is just for testing, don't look too much into it
    statemachine.processManager(loadedSequence, savePath)
    # Start processing image
    displayImage = recognise.find_bricks_by_color(image)[1]
    # Try and find aruco codes
    try:
        arucoCorners, arucoIds, rejectedCorners = recognise.find_aruco_markers(
            cv2.cvtColor(image, cv2.COLOR_BGR2GRAY))
        playfieldCorners = recognise.aruco_to_playfield_corners(
            arucoCorners, arucoIds)
        # Draw final image with overlays
        cv2.drawContours(displayImage, np.array(
            [playfieldCorners], dtype=np.int32), -1, (0, 0, 255), 5)
        for idx, corner in enumerate(playfieldCorners):
            cv2.putText(displayImage, str(idx), corner,
                        cv2.FONT_HERSHEY_SIMPLEX, 10, (0, 255, 0), 4)
            cv2.putText(displayImage, str(
                arucoIds[idx]), corner, cv2.FONT_HERSHEY_SIMPLEX, 10, (255, 0, 0), 4)

        # Cut image and draw dot matrix
        cutOutImage = util.cut_out_image(image, playfieldCorners, (1000, 1000))
        util.draw_dot_matrix(cutOutImage, (48, 48), (4, 0), (992, 994))
    except:
        # if aruco search-match-cut failed, just display main image
        cutOutImage = displayImage

    # Display final images
    cv2.imshow("Output image", util.fit_display(displayImage))
    projection.show_image_fullscreen(util.fit_display(cutOutImage))
    # Wait for user to exit
    while cv2.waitKey(100) != ord("q"):
        pass


# Parse user arguments
parser = argparse.ArgumentParser(
    description='Guidance assistant for building LEGO buildings')
parser.add_argument('--testImage', required=False,
                    help='Run the detection algorithm on a still image')
parser.add_argument('--readFile', required=True,
                    help='Lego model description file')
parser.add_argument('--saveFile', required=False, default="Saved.gg",
                    help='State save file path')

args = parser.parse_args()

# If using VS Code debugging, pass the arguments.
if vscodeargs.UsingVSCode:
    args.testImage = vscodeargs.VisualStudioArgImage
    args.readFile = vscodeargs.VisualStudioArgFile
    args.saveFile = vscodeargs.VisualStudioSaveFile

if args.testImage:
    test_main(args.testImage, args.readFile, args.saveFile)
else:
    main(args.readFile)
