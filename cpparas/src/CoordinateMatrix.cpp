#include "CoordinateMatrix.hpp"
#include <stdexcept>

CoordinateMatrix::CoordinateMatrix(Calibration calibration_)
    : calibration(calibration_)
{
}

void CoordinateMatrix::update(uint32_t baseplateX, uint32_t baseplateY, uint32_t baseplateWidth, uint32_t baseplateHeight)
{
    if (matrix.size() == 0) {
        for (uint32_t layer = 0; layer < calibration.maxLayers; layer++) {
            matrix.push_back(std::vector<std::vector<Point2D>>());
            for (uint32_t row = 0; row < calibration.baseplateRows; row++) {
                matrix[layer].push_back(std::vector<Point2D>());
                for (uint32_t col = 0; col < calibration.baseplateCols; col++) {
                    Point2D point;
                    point.col = 0;
                    point.row = 0;
                    matrix[layer][row].push_back(point);
                }
            }
        }
    }

    Point2D baseplateMidpoint;
    baseplateMidpoint.col = baseplateX + baseplateWidth / 2;
    baseplateMidpoint.row = baseplateY + baseplateHeight / 2;

    for (uint32_t layer = 0; layer < calibration.maxLayers; layer++) {
        for (uint32_t row = 0; row < calibration.baseplateRows; row++) {
            for (uint32_t col = 0; col < calibration.baseplateCols; col++) {
                Point2D point;
                point.col = // Take the midpoint of the baseplate
                    (float)baseplateMidpoint.col
                    // Add the nub index corrected for the midpoint
                    + ((float)col - ((float)calibration.baseplateCols / 2.0f) + 0.5f)
                        // Multiply by the nub size
                        * ((float)baseplateWidth / ((float)calibration.baseplateCols - 1.0f))
                        // Adjust for the block layer (x' = x / z)
                        / ((calibration.cameraHeight - layer * calibration.blockHeight) / calibration.cameraHeight);
                point.col = // Do the same for the row
                    (float)baseplateMidpoint.row
                    // Add the nub index corrected for the midpoint
                    + ((float)row - ((float)calibration.baseplateRows / 2.0f) + 0.5f)
                        // Multiply by the nub size
                        * ((float)baseplateWidth / ((float)calibration.baseplateRows - 1.0f))
                        // Adjust for the block layer (x' = x / z)
                        / ((calibration.cameraHeight - layer * calibration.blockHeight) / calibration.cameraHeight);
                matrix[layer][row][col] = point;
            }
        }
    }
}

const PointMatrix& CoordinateMatrix::getMatrix()
{
    if (matrix.size() == 0) {
        throw std::logic_error("coordinate matrix not calculated yet");
    }
    return matrix;
}
