#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "operators.h"
#include "types/Brick.hpp"
#include "types/Calibration.hpp"
#include "types/Color.hpp"
#include "types/Point.hpp"
#include "types/Rect.hpp"
#include "util/StateStep.hpp"
#include <tuple>
#include <vector>

namespace cpparas {

// The following calibration is not represented in pixels;
// it's represented in a factor (percentage) of the projection image.
// For example: (0.8, 0.2) is at the right-top of the projection image.
const Point<float> PROJECTION_INFO_ORIGIN { 0.8f, 0.2f };
const Point<float> PROJECTION_STEP_INFO_ORIGIN { 0.8f, 0.07f };
// This is a factor of the projection image width.
const float PROJECTION_STEP_FONT_SCALE = 0.004f;
// These are factors of the projection image height.
const float PROJECTION_SEPARATOR_HEIGHT = 0.02f;
const float PROJECTION_STUD_SIZE = 0.04f;
const float PROJECTION_STUD_INNER_SIZE = 0.035f;
const float PROJECTION_BRICK_DISTANCE = 0.01f;
const float PROJECTION_NEXT_FACTOR = 0.6f;
// This is a factor of the projection image width.
const float PROJECTION_NEXT_HORIZ_OFFSET = 0.01f;

const Rect<float> PROJECTION_OUTLINE = { { 0.15f, 0.01f }, 0.6f, 0.98f };

class Projection {
public:
    Projection(Calibration calibration_);
    ~Projection();

    void clear();
    void showOutline(Brick brick, int studX, int studY, int layer);
    void showInfo(StateStep stateStep, const std::vector<Brick>& expectedAndNextBricks);
    void complete();

    const image_t* getImage() const;

private:
    image_t* image;
    bool isAvailable;
    Calibration calibration;
};

} // namespace cpparas

#endif /* PROJECTION_HPP */
