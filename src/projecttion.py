import cv2

fullscreen_window_name = "Fullscreen output"

def show_image_fullscreen(image):
    cv2.namedWindow(fullscreen_window_name, cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO | cv2.WINDOW_GUI_EXPANDED)
    cv2.setWindowProperty(fullscreen_window_name, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
    cv2.imshow(fullscreen_window_name, image)
