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
const Point<float> PROJECTION_MOVE_BASEPLATE_WARNING_ORIGIN { 0.77f, 0.1f };
// This is a factor of the projection image width.
const float PROJECTION_STEP_FONT_SCALE = 0.004f;
const float PROJECTION_MOVE_BASEPLATE_WARNING_FONT_SCALE = 0.0033f;
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
    /**
     * @brief Creates a projection image for the projector UI.
     */
    Projection(Calibration calibration_);
    ~Projection();

    /**
     * @brief Clears the projection image. The projection image will be unavailable to other entities.
     * @note A clear() eventually needs to be followed up by a complete().
     */
    void clear();
    /**
     * @brief Shows an outline of the baseplate.
     */
    void showBaseplateOutline();
    /**
     * @brief Shows an outline of a brick on the baseplate.
     */
    void showBrickOutline(Brick brick, int studX, int studY, int layer);
    /**
     * @brief Shows building information like the current step and layer and the next bricks to be placed.
     */
    void showInfo(StateStep stateStep, const std::vector<Brick>& expectedAndNextBricks);
    /**
     * @brief Shows a warning that the baseplate has been moved and needs to be re-aligned by the user.
     */
    void showMoveBaseplateWarning();
    /**
     * @brief Makes the projection image available to other entities.
     */
    void complete();

    /**
     * @brief Returns the projection image.
     * @return valid pointer = projection image. nullptr = projection image is unavailable.
     */
    const image_t* getImage() const;

private:
    image_t* image;
    bool isAvailable;
    Calibration calibration;
};

} // namespace cpparas

#endif /* PROJECTION_HPP */
