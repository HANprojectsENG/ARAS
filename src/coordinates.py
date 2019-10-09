import numpy as np

CAMERA_HORIZONTAL_FOV = 62.2
CAMERA_HORIZONTAL_FOV = 62.2,  # Degrees
CAMERA_VERTICAL_FOV = 48.8,
CAMERA_HEIGHT = 0.65  # Meters, height from the camera sensor to the baseplate

BLOCK_HEIGHT = 0.0096  # Meters
BLOCK_UNIT_LENGTH = 0.008
MAX_BLOCK_LAYERS = 20
BASEPLATE_SIZE = (48, 48)  # Block units

# Calculates a nub coordinate matrix from the given baseplate size.
# This matrix contains the predicted screen coordinates for every nub in the building area.
# This is a 4D matrix. The dimensions are as follows:
# - Layer
# - Horizontal nub index
# - Vertical nub index
# - X (0) or Y (1) screen coordinates


def calculate_nub_coordinate_matrix(baseplate_corners_pos, baseplate_corners_size):
    matrix = np.zeros(
        (MAX_BLOCK_LAYERS, BASEPLATE_SIZE[1], BASEPLATE_SIZE[0], 2), dtype=np.float32)
    baseplate_midpoint = (
        (baseplate_corners_pos[0] + baseplate_corners_size[0]) / 2,
        (baseplate_corners_pos[1] + baseplate_corners_size[1]) / 2
    )

    for k in range(MAX_BLOCK_LAYERS):
        for j in range(BASEPLATE_SIZE[1]):
            for i in range(BASEPLATE_SIZE[0]):
                matrix[k][j][i] = np.array([
                    # Take the midpoint of the baseplate
                    baseplate_midpoint[0]
                    # Add the nub index corrected for the midpoint
                    + (i - (BASEPLATE_SIZE[0] / 2) + 0.5)
                    # Multiply by the nub size
                    * (baseplate_corners_size[0] / (BASEPLATE_SIZE[0] - 1))
                    # Adjust for the block layer (x' = x / z)
                    / ((CAMERA_HEIGHT - k * BLOCK_HEIGHT) / CAMERA_HEIGHT),
                    # Do the same but for calculating the Y position.
                    baseplate_midpoint[1]
                    + (j - (BASEPLATE_SIZE[1] / 2) + 0.5)
                    * (baseplate_corners_size[1] / (BASEPLATE_SIZE[1] - 1))
                    / ((CAMERA_HEIGHT - k * BLOCK_HEIGHT) / CAMERA_HEIGHT)
                ], dtype=np.float32)

    return matrix
