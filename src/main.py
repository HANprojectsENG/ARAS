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


def main(filePath):
    loadedSequence = lsfparser.openFile(filePath)
    camera.init()
    statemachine.processManager(loadedSequence, savePath, True)
    while cv2.waitKey(100) != ord("q"):
        pass


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
