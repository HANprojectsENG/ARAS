import cv2

MAX_DISPLAY_WIDTH = 960
MAX_DISPLAY_HEIGHT = 960

def fit_display(image):
    while image.shape[0] > MAX_DISPLAY_HEIGHT or image.shape[1] > MAX_DISPLAY_WIDTH:
        image = cv2.pyrDown(image)
    return image
