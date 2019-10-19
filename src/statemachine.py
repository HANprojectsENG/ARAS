import util
import os
import time
import numpy as np
from enum import Enum
from constants import MAX_DATA_PER_LEGO, MAX_LAYERS, MAX_LEGO_PER_LAYER


class ProcessState(Enum):
    INIT = 0
    STARTING = 1
    CHECK_CURRENT_STEP = 2
    PROJECT_STEP = 3
    WAIT = 4
    PROJECTOR_OFF = 5
    CHECK_NEXT_STEP = 6
    FINAL_STEP = 7


def processManager(loadedSequence, savePath):
    # oh boi
    State = None
    NextState = ProcessState.INIT
    Layer = 0
    Step = 0
    currentStep = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint32)
    checkStep = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint32)
    try:
        filePath = savePath
        while True:
            State = NextState
            # Initial state, only here once, at the beginning
            if State == ProcessState.INIT:
                if os.path.exists(filePath):
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
                                print("Loaded from last run. Last completed Step: " +
                                      str(Step) + " on Layer: " + str(Layer))
                                NextState = ProcessState.CHECK_NEXT_STEP
                            else:
                                print("Error reading save file in INIT :/")
                                break
                else:
                    # The save file doesn't exist, starting from 0
                    NextState = ProcessState.STARTING

            elif State == ProcessState.STARTING:
                Layer = 0
                Step = 0
                NextState = ProcessState.CHECK_CURRENT_STEP

            elif State == ProcessState.CHECK_CURRENT_STEP:
                print("We are in currently in Layer: " +
                      str(Layer) + " Step: " + str(Step))
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
                    with open(filePath, 'w+') as file:
                        file.write(str(Layer) + ", " + str(Step))
                # Check next step
                nextStep = Step + 1
                if nextStep != MAX_LEGO_PER_LAYER:
                    # Load next step
                    for i in range(0, MAX_DATA_PER_LEGO):
                        checkStep[i] = loadedSequence[Layer, nextStep, i]
                else:
                    # Reached max step on layer, setting step to -1 will force to move to next layer
                    checkStep[1] = -1
                # Check if next step and layer exists
                if (checkStep[1] == nextStep and checkStep[0] == Layer):
                    # Check next step data structure
                    for i in range(0, (checkStep[2]*2)):
                        if checkStep[4+i] == 0:
                            print(
                                "Error checking step Coordinates in CHECK_NEXT_STEP :/")
                            break
                    # Everything ok, moving step index +1 for the main loop
                    Step = Step + 1
                    # Load current step to use later
                    for i in range(0, MAX_DATA_PER_LEGO):
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
                with open(filePath, 'w') as file:
                    file.write('')
                print("You reached the end :)")
                break

    except Exception as e:
        print("oh no :/ Error while in State: " + str(State) + " NextState: " +
              str(NextState) + " Step: " + str(Step) + " Layer: " + str(Layer))
        print(e)