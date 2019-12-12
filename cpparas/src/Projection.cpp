#include "Projection.hpp"
#include "operators.h"

Projection::Projection(uint32_t width, uint32_t height)
{
    image = newRGB888Image(width, height);
}

Projection::~Projection()
{
    deleteImage(image);
}

void Projection::clear()
{
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
    (void)expectedAndNextBricks;
}

image_t* Projection::getImage() const
{
    return image;
}
