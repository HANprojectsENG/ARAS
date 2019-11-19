import numpy as np
from constants import MAX_LAYERS, MAX_LEGO_PER_LAYER, MAX_DATA_PER_LEGO, BAD_FILE_FORMAT_ERROR, EMPTY_FILE_LINE_WARNING


def openFile(filePath):
    # Doing my best to get rid of magic numbers, more code but far more readable
    with open(filePath) as file:
        matrix = np.zeros((MAX_LAYERS, MAX_LEGO_PER_LAYER,
                           MAX_DATA_PER_LEGO), dtype=np.uint32)
        index = np.zeros((MAX_LAYERS), dtype=np.uint8)
        errorFlag = False
        print("Starting lsf file parser!")
        # Go over every line in the file
        for cnt, line in enumerate(file):
            LineData = parseLegoData(line, cnt)
            # try block because normal return of parseLegoData is a list, otherwise it;s an int or None, easy to capture in a try block
            try:
                # Check if parser parsed data or not
                if LineData == BAD_FILE_FORMAT_ERROR:
                    print("Error Code " + str(BAD_FILE_FORMAT_ERROR))
                    errorFlag = True
                    break
                elif LineData is None:
                    print("Warning Code " + str(EMPTY_FILE_LINE_WARNING) + " Line: " + str(cnt+1))
            except:
                # Parser worked, now putting data into final array
                currentLayer = LineData[0]
                for i in range(0, MAX_DATA_PER_LEGO):
                    matrix[currentLayer, index[currentLayer], i] = LineData[i]
                print("Line " + str(cnt+1) + " parsed!")
                index[currentLayer] = index[currentLayer] + 1
        if errorFlag:
            return -1
        else:
            print("Parsing done!")
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
                print(
                    "Lego coordinates don't match selected lego size in line " + str(lineNumber+1))
                return BAD_FILE_FORMAT_ERROR
            else:
                # Add all parsed data into a single list
                stepArray = np.append(
                    np.array([layer, step, legosize, color]), np.asarray(coordinates))

                # add zeros at the end of list if list is not full, max arguments = 28 = single 2x6 lego brick
                while totalArgs != MAX_DATA_PER_LEGO:
                    stepArray = np.append(stepArray, 0)
                    totalArgs = totalArgs + 1

                return stepArray
        except ValueError:
            # Value error kicks when the int conversions above fail, meaning invalid characters
            print("File has invalid data or format in line " +
                  str(lineNumber+1) + " , pls fix!")
            return BAD_FILE_FORMAT_ERROR
    else:
        return None
