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

    /**
     * @brief Returns the projection image revision. Can be used to determine whether the image has changed.
     */
    uint32_t getImageRevision() const;

private:
    image_t* image;
    uint32_t imageRevision;
    bool isAvailable;
    Calibration calibration;
};

} // namespace cpparas

#endif /* PROJECTION_HPP */
