# import the necessary packages
import numpy as np
import pathlib
import analyze
import cv2
import argparse
import recognise
import util
import projection
import camera
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
    statemachine.processManager(loadedSequence, savePath, imagePath)
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

if args.testImage:
    test_main(args.testImage, args.readFile, args.saveFile)
else:
    main(args.readFile)
