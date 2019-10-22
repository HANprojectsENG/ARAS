import cv2
import coordinates
from constants import PROJECTION_OFFSET, PROJECTION_SIZE, PROJECTOR_RESOLUTION, PROJECTOR_HEIGHT, BASEPLATE_SIZE, BLOCK_UNIT_LENGTH

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
    baseplate_top_left_screen_coords = (
        (PROJECTOR_RESOLUTION[0] / 2) - (PROJECTOR_RESOLUTION[0] /
                                         2) * (baseplate_real_size[0] / PROJECTION_SIZE[0]),
        (PROJECTOR_RESOLUTION[1] / 2) - (PROJECTOR_RESOLUTION[1] /
                                         2) * (baseplate_real_size[0] / PROJECTION_SIZE[1])
    )
    baseplate_bottom_right_screen_coords = (
        (PROJECTOR_RESOLUTION[0] / 2) + (PROJECTOR_RESOLUTION[0] /
                                         2) * (baseplate_real_size[0] / PROJECTION_SIZE[0]),
        (PROJECTOR_RESOLUTION[1] / 2) + (PROJECTOR_RESOLUTION[1] /
                                         2) * (baseplate_real_size[0] / PROJECTION_SIZE[1])
    )
    return (util.map_number(block_pos[0] / (BASEPLATE_SIZE[0] - 1), baseplate_top_left_screen_coords[0], baseplate_bottom_right_screen_coords[0]), util.map_number(block_pos[1] / (BASEPLATE_SIZE[1] - 1), baseplate_top_left_screen_coords[1], baseplate_bottom_right_screen_coords[1]))


def create_block_outline_image(layer, block_pos, block_size):
    image = np.zeros(
        (PROJECTOR_RESOLUTION[0], PROJECTOR_RESOLUTION[1], 3), np.uint8)

    cv2.rectangle(image, get_block_screen_coordinate(layer, block_pos), get_block_screen_coordinate(
        layer, (block_pos[0] + block_size[0], block_pos[1] + block_size[1])), (255, 255, 255), 3)

    return image
