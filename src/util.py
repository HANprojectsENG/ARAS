import cv2
import numpy as np
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
    with open(filePath) as fp:
        matrix = np.zeros((MAX_LAYERS,MAX_LEGO_PER_LAYER,MAX_DATA_PER_LEGO), dtype=np.uint32)
        index = np.zeros((MAX_LAYERS), dtype=np.uint8)
        errorFlag = False
        # Go over every line in the file
        for cnt, line in enumerate(fp):
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
                while totalArgs != 28:
                    stepArray = np.append(stepArray, 0)
                    totalArgs = totalArgs + 1

                return stepArray
        except ValueError:
            # Value error kicks when the int conversions above fail, meaning invalid characters
            print("File has invalid data or format in line " + str(lineNumber+1) + " , pls fix!")
            return BAD_FILE_FORMAT_ERROR
    else:
        return None