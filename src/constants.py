######################### Error/Warning Codes #######################

# lsfparser
BAD_FILE_FORMAT_ERROR = 69  #lsf file has bad format - cannot be read properly
EMPTY_FILE_LINE_WARNING = 70 #lsf line has empty line, skipping line

# State machine
SAVE_FILE_READ_ERROR = 71 #cannot read or write the save file
CHECK_NEXT_STEP_COORDINATES_ERROR = 72 #coordinates don't much specified lego size

#############################################################

####################### Module Constants ####################

# State machine constants
MAX_LAYERS = 20 # Max layers the stame machine can go through, should be the same as MAX_BLOCK_LAYERS
MAX_LEGO_PER_LAYER = 50 # Max amount of bricks allowed per layers
MAX_DATA_PER_LEGO = 28 # Max data points per lego, 28 means 4 data points standard + 12 x/y coordinates, for up to a 2x6 lego piece

# Constants used by the coordinates module
CAMERA_HORIZONTAL_FOV = 62.2
CAMERA_HORIZONTAL_FOV = 62.2,  # Degrees
CAMERA_VERTICAL_FOV = 48.8,
CAMERA_HEIGHT = 0.65  # Meters, height from the camera sensor to the baseplate

BLOCK_HEIGHT = 0.0096  # Meters
BLOCK_UNIT_LENGTH = 0.008
MAX_BLOCK_LAYERS = 20
BASEPLATE_SIZE = (48, 48)  # Block units

# Projection calibration
PROJECTION_SIZE = (0.60, 0.40)  # Meters
PROJECTION_OFFSET = (0.00, 0.00)  # Meters
PROJECTOR_HEIGHT = 0.80  # Meters
PROJECTOR_RESOLUTION = (854, 480)

# Max size for image debug windows
MAX_DISPLAY_WIDTH = 960
MAX_DISPLAY_HEIGHT = 960

# Camera capture resolution
CAPTURE_RESOLUTION = (1640, 1232)

# After cutting out an image based on markers, there still might be some misalignment.
BASEPLATE_CUTOUT_POS = (4, 0)
BASEPLATE_CUTOUT_SIZE = (992, 994)

#############################################################
