import cv2
import numpy as np

MAX_DISPLAY_WIDTH = 960
MAX_DISPLAY_HEIGHT = 960


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
    for j in range(dots_size[1]):
        for i in range(dots_size[0]):
            cv2.circle(
                    image,
                    (int(destination_pos[0] + i / dots_size[0] * destination_size[0]),
                     int(destination_pos[1] + j / dots_size[1] * destination_size[1])),
                    2,
                    (255, 0, 0),
                    -1)

