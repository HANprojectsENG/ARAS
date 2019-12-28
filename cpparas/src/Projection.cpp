#include "Projection.hpp"
#include "operators.h"
#include "types/Point.hpp"

Projection::Projection(uint32_t width, uint32_t height)
    : isAvailable(false)
{
    image = newRGB888Image(width, height);
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

void Projection::showOutline(Brick brick, int studX, int studY)
{
    (void)brick;
    (void)studX;
    (void)studY;
}

void Projection::showInfo(int step, int layer, const std::vector<Brick>& expectedAndNextBricks)
{
    (void)step;
    (void)layer;

    const Point2D nextOrigin { static_cast<int>(image->cols * 0.8f), static_cast<int>(image->rows * 0.2f) };
    const Point2D studSize { static_cast<int>(image->rows * 0.04f), static_cast<int>(image->rows * 0.04f) };
    const Point2D studInnerSize { static_cast<int>(studSize.col * 0.9f), static_cast<int>(studSize.row * 0.9f) };
    const int brickDistance = static_cast<int>(studSize.row * 0.3f);
    const int separatorHeight = static_cast<int>(studSize.row * 2.0f);
    int brickIdx = 0;
    int brickPosRow = nextOrigin.row;
    for (const Brick& brick : expectedAndNextBricks) {
        for (int w = 0; w < brick.width; w++) {
            for (int h = 0; h < brick.height; h++) {
                int pos[2] = { nextOrigin.col + studSize.col * w, brickPosRow + studSize.row * h };
                int size[2] = { studInnerSize.col, studInnerSize.row };
                pixel_t color;
                color.rgb888_pixel = COLOR_DISPLAY_VALUES.at(brick.color);
                drawRect(image, pos, size, color, SHAPE_FILL, 0);
            }
        }
        brickPosRow += studSize.row * brick.height + brickDistance;
        if (brickIdx == 0)
            brickPosRow += separatorHeight;
        brickIdx++;
    }
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
