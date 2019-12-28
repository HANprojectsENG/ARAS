#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "operators.h"
#include "types/Brick.hpp"
#include "types/Color.hpp"
#include "types/Point.hpp"
#include <tuple>
#include <vector>

namespace cpparas {

const Point<float> PROJECTION_INFO_ORIGIN { 0.8f, 0.2f };
const float PROJECTION_SEPARATOR_HEIGHT = 0.02f;
const float PROJECTION_STUD_SIZE = 0.04f;
const float PROJECTION_STUD_INNER_SIZE = 0.035f;
const float PROJECTION_BRICK_DISTANCE = 0.01f;

class Projection {
public:
    Projection(uint32_t width, uint32_t height);
    ~Projection();

    void clear();
    void showOutline(Brick brick, int studX, int studY);
    void showInfo(int step, int layer, const std::vector<Brick>& expectedAndNextBricks);
    void complete();

    const image_t* getImage() const;

private:
    image_t* image;
    bool isAvailable;
};

} // namespace cpparas

#endif /* PROJECTION_HPP */
