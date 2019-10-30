import util
import pathlib
import time
import recognise
import coordinates
import analyze
import cv2
import numpy as np
from enum import Enum
from constants import MAX_DATA_PER_LEGO, MAX_LAYERS, MAX_LEGO_PER_LAYER, SAVE_FILE_READ_ERROR, CHECK_NEXT_STEP_COORDINATES_ERROR


class ProcessState(Enum):
    INIT = 0
    STARTING = 1
    CHECK_CURRENT_STEP = 2
    PROJECT_STEP = 3
    WAIT = 4
    PROJECTOR_OFF = 5
    CAPTURE = 6
    CHECK_NEXT_STEP = 7
    FINAL_STEP = 8

def processManager(loadedSequence, savePath, imagePath):
    #oh boi
    State = None
    NextState = ProcessState.INIT
    Layer = 0
    Step = 0
    currentStep = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint16)
    checkStep = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint16)
    cropped_image = analyze.get_image(imagePath)
    matrix = coordinates.calculate_nub_coordinate_matrix((4,0),(992,994))
    try:
        while True:
            #check if loop should continue or not
            if LoopChecker() == False:
                break
            State = NextState
            # Initial state, only here once, at the beginning
            if State == ProcessState.INIT:
                # Open save file if exists, create it otherwise
                mode = 'r' if pathlib.Path(savePath).is_file() else 'w+'
                with open(savePath, mode) as file:
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
                            print("Error Code" + str(SAVE_FILE_READ_ERROR))
                            break

            elif State == ProcessState.STARTING:
                Layer = 0
                Step = 0
                NextState = ProcessState.CHECK_CURRENT_STEP
        
            elif State == ProcessState.CHECK_CURRENT_STEP:
                # check recogntion of current step
                completed = recognise.recognition(loadedSequence[Layer][Step], cropped_image, matrix)
                if completed:
                    NextState = ProcessState.CHECK_NEXT_STEP
                else:
                    NextState = ProcessState.PROJECT_STEP

            elif State == ProcessState.PROJECT_STEP:
                # project current step
                NextState = ProcessState.WAIT
        
            elif State == ProcessState.WAIT:
                # wait for hand movement
                # wait for key press until hand movement is working
                while cv2.waitKey(100) != ord("n"):
                    pass
                NextState = ProcessState.PROJECTOR_OFF

            elif State == ProcessState.PROJECTOR_OFF:
                # Turn off projector / display black image
                NextState = ProcessState.CAPTURE

            elif State == ProcessState.CAPTURE:
                # Take picture
                cropped_image = analyze.get_image(imagePath)
                NextState = ProcessState.CHECK_CURRENT_STEP

            elif State == ProcessState.CHECK_NEXT_STEP:
                # Before checking next step, save last step
                if Step != -1:
                    with open(savePath, 'w') as file:
                        file.write(str(Layer) + ", " + str(Step))
                # Check next step
                nextStep = Step + 1
                if nextStep != MAX_LEGO_PER_LAYER:
                    # Load next step 
                    for i  in range(0,MAX_DATA_PER_LEGO):
                        checkStep[i] = loadedSequence[Layer, nextStep, i]
                else:
                    # Reached max step on layer, setting step to -1 will force to move to next layer
                    checkStep[1] = -1
                # Check if next step and layer exists
                if (checkStep[1] == nextStep and checkStep[0] == Layer):
                    # Check next step data structure
                    for i in range(0,(checkStep[2]*2)):
                        if checkStep[4+i] == 0:
                            print("Error Code" + str(CHECK_NEXT_STEP_COORDINATES_ERROR))
                            break
                    # Everything ok, moving step index +1 for the main loop
                    Step = Step + 1
                    # Load current step to use later
                    for i  in range(0,MAX_DATA_PER_LEGO):
                        currentStep[i] = loadedSequence[Layer, Step, i]
                    NextState = ProcessState.CHECK_CURRENT_STEP
                # Step or layer not found, means we reached the end probably, will have to go to next layer
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
                with open(savePath, 'w') as file:
                    file.write('')
                print("You reached the end :)")
                break

    except Exception as e:
        print ("Error while in State: " + str(State) + " NextState: " + str(NextState) + " Step: " + str(Step) + " Layer: " + str(Layer))
        traceback.print_exc()

def LoopChecker():
  CheckedArucoisFineDontWorryAboutIt = True
  return CheckedArucoisFineDontWorryAboutIt
