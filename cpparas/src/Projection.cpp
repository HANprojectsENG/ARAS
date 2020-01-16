#include "Projection.hpp"
#include "debug/Debug.hpp"
#include "operators.h"
#include "operators_fonts.h"
#include "types/Point.hpp"

namespace cpparas {

Projection::Projection(Calibration calibration_)
    : isAvailable(false)
    , calibration(calibration_)
{
    image = newRGB888Image(calibration.projectorResolutionCols, calibration.projectorResolutionRows);
}

Projection::~Projection()
{
    deleteImage(image);
}

void Projection::clear()
{
    isAvailable = false;
    erase(image);
}

float mapNumber(float value, std::pair<float, float> src, std::pair<float, float> dst)
{
    return ((value - src.first) / (src.second - src.first)) * (dst.second - dst.first) + dst.first;
}

Point<float> blockScreenCoordinate(Calibration calibration, int studX, int studY, int layer)
{
    float layerFactor = 1.0f / ((calibration.cameraHeight - (float)layer * calibration.blockHeight) / calibration.cameraHeight);
    // Baseplate corner screen distance from the center
    Point<float> screenDist = {
        0.5f * layerFactor,
        0.5f * layerFactor,
    };
    // Projection offset in screen coordinates
    Point<float> screenOffset = {
        (1.0f / calibration.projectionWidth) * 0.0f, // TODO: Replace by projection offset
        (1.0f / calibration.projectionHeight) * 0.0f // TODO: Replace by projection offset
    };
    // Generate screen coordinates for baseplate corners
    Point<float> baseplateLayerTopLeftScreenCoords = {
        0.5f - screenDist.col + screenOffset.col,
        0.5f - screenDist.row + screenOffset.row,
    };
    Point<float> baseplateLayerRightBottomScreenCoords = {
        0.5f + screenDist.col + screenOffset.col,
        0.5f + screenDist.row + screenOffset.row,
    };
    // Map block position to baseplate screen corner coordinates
    Point<float> screenCoord = {
        mapNumber(studX, std::make_pair(0.0f, calibration.baseplateCols),
            std::make_pair(baseplateLayerTopLeftScreenCoords.col, baseplateLayerRightBottomScreenCoords.col)),
        mapNumber(studY, std::make_pair(0.0f, calibration.baseplateRows),
            std::make_pair(baseplateLayerTopLeftScreenCoords.row, baseplateLayerRightBottomScreenCoords.row))
    };
    return screenCoord;
}

Point<int> baseplateCoordToProjectionCoord(Point<float> baseplateCoord, int imageWidth, int imageHeight)
{
    Point<int> result = {
        static_cast<int>(mapNumber(baseplateCoord.col, std::make_pair(0.0f, 1.0f), std::make_pair(imageWidth * PROJECTION_OUTLINE.origin.col, imageWidth * (PROJECTION_OUTLINE.origin.col + PROJECTION_OUTLINE.width)))),
        static_cast<int>(mapNumber(baseplateCoord.row, std::make_pair(0.0f, 1.0f), std::make_pair(imageHeight * PROJECTION_OUTLINE.origin.row, imageHeight * (PROJECTION_OUTLINE.origin.row + PROJECTION_OUTLINE.height))))
    };
    return result;
}

void Projection::showBaseplateOutline()
{
    int opos[2] = { static_cast<int>(image->cols * PROJECTION_OUTLINE.origin.col), static_cast<int>(image->rows * PROJECTION_OUTLINE.origin.row) };
    int osize[2] = { static_cast<int>(image->cols * PROJECTION_OUTLINE.width), static_cast<int>(image->rows * PROJECTION_OUTLINE.height) };
    pixel_t ocolor;
    ocolor.rgb888_pixel.r = 255;
    ocolor.rgb888_pixel.g = 255;
    ocolor.rgb888_pixel.b = 255;

    drawRect(image, opos, osize, ocolor, SHAPE_BORDER, 5);
}

void Projection::showBrickOutline(Brick brick, int studX, int studY, int layer)
{
    Point<float> baseplateCoord = blockScreenCoordinate(calibration, studX, studY, layer);
    Point<float> baseplateCoord2 = blockScreenCoordinate(calibration, studX + brick.width, studY + brick.height, layer);
    Debug::println(std::string("Coords: (") + std::to_string(baseplateCoord.col) + std::string(", ") + std::to_string(baseplateCoord.row) + std::string(") (") + std::to_string(baseplateCoord2.col) + std::string(", ") + std::to_string(baseplateCoord2.row) + std::string(")"));
    Point<int> projectionCoord = baseplateCoordToProjectionCoord(baseplateCoord, image->cols, image->rows);
    Point<int> projectionCoord2 = baseplateCoordToProjectionCoord(baseplateCoord2, image->cols, image->rows);
    int bpos[2] = { projectionCoord.col, projectionCoord.row };
    int bsize[2] = { projectionCoord2.col - projectionCoord.col, projectionCoord2.row - projectionCoord.row };
    Debug::println(std::string("Brick position: (") + std::to_string(bpos[0]) + std::string(", ") + std::to_string(bpos[1]) + std::string(") ") + std::to_string(bsize[0]) + std::string("x") + std::to_string(bsize[1]));
    pixel_t bcolor;
    bcolor.rgb888_pixel = COLOR_DISPLAY_VALUES.at(brick.color);
    drawRect(image, bpos, bsize, bcolor, SHAPE_FILL, 3);
}

void Projection::showInfo(StateStep stateStep, const std::vector<Brick>& expectedAndNextBricks)
{
    pixel_t stepcolor;
    stepcolor.rgb888_pixel.r = 255;
    stepcolor.rgb888_pixel.g = 255;
    stepcolor.rgb888_pixel.b = 255;
    int32_t steppos[] = { static_cast<int>(image->cols * PROJECTION_STEP_INFO_ORIGIN.col), static_cast<int>(image->rows * PROJECTION_STEP_INFO_ORIGIN.row) };
    uint8_t stepscale = static_cast<uint8_t>(image->cols * PROJECTION_STEP_FONT_SCALE);
    if (stepscale == 0)
        stepscale = 1;
    std::string stepstr = std::string("STEP ") + std::to_string(stateStep.step)
        + std::string("\nLAYER ") + std::to_string(stateStep.layer);
    drawText(image, stepstr.c_str(), font_simple6pt, steppos, stepscale, stepcolor);

    int brickIdx = 0;
    float brickPosRow = PROJECTION_INFO_ORIGIN.row;
    for (const Brick& brick : expectedAndNextBricks) {
        float factor = brickIdx == 0 ? 1.0f : PROJECTION_NEXT_FACTOR;
        for (uint32_t w = 0; w < brick.width; w++) {
            for (uint32_t h = 0; h < brick.height; h++) {
                int pos[2] = { static_cast<int>(image->cols * (PROJECTION_INFO_ORIGIN.col + (brickIdx == 0 ? 0.0f : PROJECTION_NEXT_HORIZ_OFFSET)) + factor * image->rows * PROJECTION_STUD_SIZE * w), static_cast<int>(image->rows * brickPosRow + factor * image->rows * PROJECTION_STUD_SIZE * h) };
                int size[2] = { static_cast<int>(factor * (image->rows * PROJECTION_STUD_INNER_SIZE)), static_cast<int>(factor * (image->rows * PROJECTION_STUD_INNER_SIZE)) };
                pixel_t color;
                color.rgb888_pixel = COLOR_DISPLAY_VALUES.at(brick.color);
                drawRect(image, pos, size, color, SHAPE_FILL, 0);
            }
        }
        brickPosRow += factor * PROJECTION_STUD_SIZE * brick.height + PROJECTION_BRICK_DISTANCE;
        if (brickIdx == 0)
            brickPosRow += PROJECTION_SEPARATOR_HEIGHT;
        brickIdx++;
    }
}

void Projection::showMoveBaseplateWarning()
{
    pixel_t stepcolor;
    stepcolor.rgb888_pixel.r = 255;
    stepcolor.rgb888_pixel.g = 64;
    stepcolor.rgb888_pixel.b = 64;
    int32_t steppos[] = { static_cast<int>(image->cols * PROJECTION_MOVE_BASEPLATE_WARNING_ORIGIN.col), static_cast<int>(image->rows * PROJECTION_MOVE_BASEPLATE_WARNING_ORIGIN.row) };
    uint8_t stepscale = static_cast<uint8_t>(image->cols * PROJECTION_MOVE_BASEPLATE_WARNING_FONT_SCALE);
    drawText(image, "ALIGN THE\nBASEPLATE WITH\nTHE OUTLINE", font_simple6pt, steppos, stepscale, stepcolor);
}

void Projection::complete()
{
    isAvailable = true;
}

const image_t* Projection::getImage() const
{
    if (!isAvailable) {
        return nullptr;
    } else {
        return image;
    }
}

} // namespace cpparas
