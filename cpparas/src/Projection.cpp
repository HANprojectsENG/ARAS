#include "Projection.hpp"
#include "operators.h"
#include "types/Point.hpp"

namespace cpparas {

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

    int brickIdx = 0;
    float brickPosRow = PROJECTION_INFO_ORIGIN.row;
    for (const Brick& brick : expectedAndNextBricks) {
        for (int w = 0; w < brick.width; w++) {
            for (int h = 0; h < brick.height; h++) {
                int pos[2] = { static_cast<int>(image->cols * PROJECTION_INFO_ORIGIN.col + image->rows * PROJECTION_STUD_SIZE * w), static_cast<int>(image->rows * brickPosRow + image->rows * PROJECTION_STUD_SIZE * h) };
                int size[2] = { static_cast<int>(image->rows * PROJECTION_STUD_INNER_SIZE), static_cast<int>(image->rows * PROJECTION_STUD_INNER_SIZE) };
                pixel_t color;
                color.rgb888_pixel = COLOR_DISPLAY_VALUES.at(brick.color);
                drawRect(image, pos, size, color, SHAPE_FILL, 0);
            }
        }
        brickPosRow += PROJECTION_STUD_SIZE * brick.height + PROJECTION_BRICK_DISTANCE;
        if (brickIdx == 0)
            brickPosRow += PROJECTION_SEPARATOR_HEIGHT;
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

} // namespace cpparas
