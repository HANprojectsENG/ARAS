import cv2
import numpy as np
import coordinates
import util
from constants import PROJECTION_OFFSET, PROJECTION_SIZE, PROJECTOR_RESOLUTION, PROJECTOR_HEIGHT, BASEPLATE_SIZE, BLOCK_UNIT_LENGTH, BLOCK_HEIGHT, CAMERA_HEIGHT

fullscreen_window_name = "Fullscreen output"


def show_image_fullscreen(image):
    cv2.namedWindow(fullscreen_window_name, cv2.WINDOW_NORMAL |
                    cv2.WINDOW_KEEPRATIO | cv2.WINDOW_GUI_EXPANDED)
    cv2.setWindowProperty(fullscreen_window_name,
                          cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
    cv2.imshow(fullscreen_window_name, image)


def get_block_screen_coordinate(layer, block_pos):
    baseplate_real_size = (
        BASEPLATE_SIZE[0] * BLOCK_UNIT_LENGTH, BASEPLATE_SIZE[1] * BLOCK_UNIT_LENGTH)
    layer_factor = 1 / ((CAMERA_HEIGHT - layer * BLOCK_HEIGHT) / CAMERA_HEIGHT)
    # Baseplate corner screen distance from the center
    screen_dist_x = (PROJECTOR_RESOLUTION[0] /
                       2) * (baseplate_real_size[0] / PROJECTION_SIZE[0]) * layer_factor
    screen_dist_y = (PROJECTOR_RESOLUTION[1] /
                       2) * (baseplate_real_size[1] / PROJECTION_SIZE[1]) * layer_factor
    # Projection offset in screen coordinates
    screen_offset_x = (PROJECTOR_RESOLUTION[0] / PROJECTION_SIZE[0]) * PROJECTION_OFFSET[0]
    screen_offset_y = (PROJECTOR_RESOLUTION[1] / PROJECTION_SIZE[1]) * PROJECTION_OFFSET[1]
    # Generate screen coordinates for baseplate corners
    baseplate_layer_top_left_screen_coords = (
        (PROJECTOR_RESOLUTION[0] / 2) - screen_dist_x + screen_offset_x,
        (PROJECTOR_RESOLUTION[1] / 2) - screen_dist_y + screen_offset_y
    )
    baseplate_layer_right_bottom_screen_coords = (
        (PROJECTOR_RESOLUTION[0] / 2) + screen_dist_x + screen_offset_x,
        (PROJECTOR_RESOLUTION[1] / 2) + screen_dist_y + screen_offset_y
    )
    # Map block position to baseplate screen corner coordinates
    screen_x = util.map_number(block_pos[0], (0, BASEPLATE_SIZE[0] - 1),
                               (baseplate_layer_top_left_screen_coords[0], baseplate_layer_right_bottom_screen_coords[0]))
    screen_y = util.map_number(block_pos[1], (0, BASEPLATE_SIZE[1] - 1),
                               (baseplate_layer_top_left_screen_coords[1], baseplate_layer_right_bottom_screen_coords[1]))
    return (int(screen_x), int(screen_y))


def create_block_outline_image(layer, block_pos, block_size):
    image = np.zeros(
        (PROJECTOR_RESOLUTION[1], PROJECTOR_RESOLUTION[0], 3), np.uint8)

    left_top_corner = get_block_screen_coordinate(layer, block_pos)
    bottom_right_corner = get_block_screen_coordinate(
        layer, (block_pos[0] + block_size[0], block_pos[1] + block_size[1]))

    rectangle_thickness = 3 / \
        ((CAMERA_HEIGHT - layer * BLOCK_HEIGHT) / CAMERA_HEIGHT)

    cv2.rectangle(image, left_top_corner, bottom_right_corner,
                  (255, 255, 255), int(rectangle_thickness))

    return image
