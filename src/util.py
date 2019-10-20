import cv2
import os
import time
import numpy as np
from enum import Enum
import coordinates

MAX_DISPLAY_WIDTH = 960
MAX_DISPLAY_HEIGHT = 960
MAX_LAYERS = 10
MAX_LEGO_PER_LAYER = 50
MAX_DATA_PER_LEGO = 28
BAD_FILE_FORMAT_ERROR = 69




def fit_display(image):
    while image.shape[0] > MAX_DISPLAY_HEIGHT or image.shape[1] > MAX_DISPLAY_WIDTH:
        image = cv2.pyrDown(image)
    return image

# See https://stackoverflow.com/questions/46390779/automatic-white-balancing-with-grayworld-assumption


def white_balance(img):
    result = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)
    avg_a = np.average(result[:, :, 1])
    avg_b = np.average(result[:, :, 2])
    result[:, :, 1] = result[:, :, 1] - \
        ((avg_a - 128) * (result[:, :, 0] / 255.0) * 1.1)
    result[:, :, 2] = result[:, :, 2] - \
        ((avg_b - 128) * (result[:, :, 0] / 255.0) * 1.1)
    result = cv2.cvtColor(result, cv2.COLOR_LAB2BGR)
    return result


def size_to_corners(size):
    return np.array([
        [0, 0],
        [size[0], 0],
        [size[0], size[1]],
        [0, size[1]]
    ],
        dtype=np.float32)


def cut_out_image(image, playfieldCorners, destSize):
    M = cv2.getPerspectiveTransform(
        np.array(playfieldCorners, dtype=np.float32), size_to_corners(destSize))
    warpedImage = cv2.warpPerspective(image, M, destSize)
    return warpedImage


def draw_dot_matrix(image, dots_size, destination_pos, destination_size):
    matrix = coordinates.calculate_nub_coordinate_matrix(
        destination_pos, destination_size)
    layer = 0

    for j in range(dots_size[1]):
        for i in range(dots_size[0]):
            cv2.circle(
                image,
                (matrix[layer, j, i, 0], matrix[layer, j, i, 1]),
                2,
                (255, 0, 0),
                -1)

def openFile (filePath):
    # Doing my best to get rid of magic numbers, more code but far more readable
    with open(filePath) as file:
        matrix = np.zeros((MAX_LAYERS,MAX_LEGO_PER_LAYER,MAX_DATA_PER_LEGO), dtype=np.uint32)
        index = np.zeros((MAX_LAYERS), dtype=np.uint8)
        errorFlag = False
        # Go over every line in the file
        for cnt, line in enumerate(file):
            LineData = parseLegoData(line, cnt)
            #try block because normal return of parseLegoData is a list, otherwise it;s an int or None, easy to capture in a try block
            try:
                # Check if parser parsed data or not
                if LineData == BAD_FILE_FORMAT_ERROR:
                    print("Error reading file!")
                    errorFlag = True
                    break
                elif LineData is None:
                    print("Skipping line " + str(cnt+1))
            except:
                # Parser worked, now putting data into final array
                currentLayer = LineData[0]
                for i  in range(0,MAX_DATA_PER_LEGO):
                    matrix[currentLayer,index[currentLayer], i] = LineData[i]
                print("Line " + str(cnt+1) + " parsed!")
                index[currentLayer] = index[currentLayer] + 1
        if errorFlag:
            return -1
        else:
            return matrix

def parseLegoData(line, lineNumber):
    data = line.split(', ')
    totalArgs = len(data)
    # 8 arguments means at minimum a 1x2 piece
    if totalArgs >= 8:
        try:
            layer = int(data[0])
            step = int(data[1])
            legosize = int(data[2])
            color = int(data[3])
            coordinates = list(map(int, data[4:(totalArgs)]))
            # we don't want more or less coordinates than we need do we.
            if len(coordinates) != legosize*2:
                print("Lego coordinates don't match selected lego size in line " + str(lineNumber+1))
                return BAD_FILE_FORMAT_ERROR
            else: 
                # Add all parsed data into a single list
                stepArray = np.append( np.array([layer, step, legosize, color]) , np.asarray(coordinates) )

                # add zeros at the end of list if list is not full, max arguments = 28 = single 2x6 lego brick
                while totalArgs != MAX_DATA_PER_LEGO:
                    stepArray = np.append(stepArray, 0)
                    totalArgs = totalArgs + 1

                return stepArray
        except ValueError:
            # Value error kicks when the int conversions above fail, meaning invalid characters
            print("File has invalid data or format in line " + str(lineNumber+1) + " , pls fix!")
            return BAD_FILE_FORMAT_ERROR
    else:
        return None

#########################################################################################################
#########################################################################################################
#########################################################################################################
#################################-------TEMPORARY CODE LOCATION-------###################################
#########################################################################################################
#########################################################################################################
#########################################################################################################

class ProcessState(Enum):
    INIT = 0
    STARTING = 1
    CHECK_CURRENT_STEP = 2
    PROJECT_STEP = 3
    WAIT = 4
    PROJECTOR_OFF = 5
    CHECK_NEXT_STEP = 6
    FINAL_STEP = 7

def processManager(loadedSequence):
    #oh boi
    State = None
    NextState = ProcessState.INIT
    Layer = 0
    Step = 0
    currentStep = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint32)
    checkStep = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint32)
    try:
        filePath = os.getcwd()
        filePath = filePath.replace("src", "Saved.gg")
        while True:
            State = NextState
            # Initial state, only here once, at the beginning
            if State == ProcessState.INIT:
                # Open save file
                with open(filePath) as file:
                    data = file.readline()
                    if data == '':
                        # No data on savefile, starting from 0
                        NextState = ProcessState.STARTING
                    else:
                        data = data.split(', ')
                        if len(data) == 2:
                            # Savedata found, importining it and starting the next step
                            Layer = int(data[0])
                            Step = int(data[1])
                            print("Loaded from last run. Last completed Step: " + str(Step) + " on Layer: " + str(Layer))
                            NextState = ProcessState.CHECK_NEXT_STEP
                        else:
                            print("Error reading save file :/ ")
                            break

            elif State == ProcessState.STARTING:
                Layer = 0
                Step = 0
                NextState = ProcessState.CHECK_CURRENT_STEP
        
            elif State == ProcessState.CHECK_CURRENT_STEP:
                print("We are in currently in Layer: " + str(Layer) + " Step: " + str(Step))
                # basic idea of last check, change bool to move steps or not
                completed = True
                time.sleep(2)
                if completed:
                    NextState = ProcessState.CHECK_NEXT_STEP
                else:
                    NextState = ProcessState.PROJECT_STEP

            elif State == ProcessState.PROJECT_STEP:
                # project current step
                NextState = ProcessState.WAIT
        
            elif State == ProcessState.WAIT:
                # wait for hand movement
                NextState = ProcessState.PROJECTOR_OFF

            elif State == ProcessState.PROJECTOR_OFF:
                # Turn off projector / display black image
                NextState = ProcessState.CHECK_CURRENT_STEP

            elif State == ProcessState.CHECK_NEXT_STEP:
                # Before checking next step, save last step
                if Step != -1:
                    with open(filePath, 'w') as file:
                        file.write(str(Layer) + ", " + str(Step))
                # Check next step
                nextStep = Step + 1
                # Load next step 
                for i  in range(0,MAX_DATA_PER_LEGO):
                    checkStep[i] = loadedSequence[Layer, nextStep, i]
                # Check if next step  exists
                if (checkStep[1] == nextStep):
                    # Check if next step layer exists
                    if (checkStep[0] == Layer):
                        # Check next step data structure
                        for i in range(0,(checkStep[2]*2)):
                            if checkStep[4+i] == 0:
                                print("Error checking step Coordinates in CHECK_NEXT_STEP")
                                break
                        # Everything ok, moving step index +1 for the main loop
                        Step = Step + 1
                        # Load current step to use later
                        for i  in range(0,MAX_DATA_PER_LEGO):
                            currentStep[i] = loadedSequence[Layer, Step, i]
                        NextState = ProcessState.CHECK_CURRENT_STEP
                    # Layer not found in this step, will increment Layer and check again
                    else:
                        Layer = Layer + 1
                        if Layer == MAX_LAYERS:
                            NextState = ProcessState.FINAL_STEP
                        else:
                            NextState = ProcessState.CHECK_NEXT_STEP
                # Step not found, means we reached the end probably, will have to go to next layer
                # We set Step to -1 because its always incremented at the start of this state
                else:
                    Step = -1
                    Layer = Layer + 1
                    if Layer == MAX_LAYERS:
                        NextState = ProcessState.FINAL_STEP
                    else:
                        NextState = ProcessState.CHECK_NEXT_STEP

            elif State == ProcessState.FINAL_STEP:
                # We are done, erase savefile!
                with open(filePath, 'w') as file:
                    file.write('')
                print("You reached the end :)")
                break

    except Exception as e:
        print ("oh no..Error while in State: " + str(State) + " NextState: " + str(NextState) + " Step: " + str(Step) + " Layer: " + str(Layer))
        print(e)
