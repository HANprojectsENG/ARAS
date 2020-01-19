#include "CoordinateMatrix.hpp"
#include "types/Calibration.hpp"
#include <gtest/gtest.h>

using namespace cpparas;

TEST(CoordinateMatrixSuite, CalculateValues)
{
    const Calibration calibration = DEFAULT_CALIBRATION;
    CoordinateMatrix coordinateMatrix(calibration);
    coordinateMatrix.update(0, 0, 1000, 1000);

    const PointMatrix& matrix = coordinateMatrix.getMatrix();

    EXPECT_EQ(matrix[0][0][0], (Point<int32_t> { 0, 0 })) << "Left-top of the baseplate at the bottom layer is the left-top of the input coordinates";
    EXPECT_EQ(matrix[0][calibration.baseplateRows - 1][calibration.baseplateCols - 1], (Point<int32_t> { 1000, 1000 })) << "Right-bottom of the baseplate (plus one) is at the bottom-right of the input coordinates (plus one)";
    EXPECT_TRUE(matrix[calibration.maxLayers / 2][0][0].col < matrix[0][0][0].col) << "coordinates move further from the center as the layer goes up";
    EXPECT_TRUE(matrix[calibration.maxLayers / 2][0][0].row < matrix[0][0][0].row) << "coordinates move further from the center as the layer goes up";
    EXPECT_TRUE(matrix[calibration.maxLayers / 2][calibration.baseplateRows - 1][calibration.baseplateCols - 1].col > matrix[0][calibration.baseplateRows - 1][calibration.baseplateCols - 1].col) << "coordinates move further from the center as the layer goes up";
    EXPECT_TRUE(matrix[calibration.maxLayers / 2][calibration.baseplateRows - 1][calibration.baseplateCols - 1].row > matrix[0][calibration.baseplateRows - 1][calibration.baseplateCols - 1].row) << "coordinates move further from the center as the layer goes up";
}

TEST(CoordinateMatrixSuite, MatrixSize)
{
    const Calibration calibration = DEFAULT_CALIBRATION;
    CoordinateMatrix coordinateMatrix(calibration);
    coordinateMatrix.update(0, 0, 1000, 1000);

    const PointMatrix& matrix = coordinateMatrix.getMatrix();
    EXPECT_EQ(matrix.size(), calibration.maxLayers);
    EXPECT_EQ(matrix[0].size(), calibration.baseplateRows);
    EXPECT_EQ(matrix[0][0].size(), calibration.baseplateCols);
    EXPECT_EQ(matrix[calibration.maxLayers - 1].size(), calibration.baseplateRows);
    EXPECT_EQ(matrix[calibration.maxLayers - 1][calibration.baseplateRows - 1].size(), calibration.baseplateCols);
}
