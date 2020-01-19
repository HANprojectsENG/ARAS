#ifndef CALIBRATION_HPP
#define CALIBRATION_HPP

#include "types/Point.hpp"
#include "types/Rect.hpp"
#include <cstdint>

#define constructS(T, ...) \
    ([] { T _{}; __VA_ARGS__; return _; }())

namespace cpparas {

/**
 * @brief Calibration parameters
 */
struct Calibration {
    /* Camera FOV */
    float cameraHorizontalFov;
    float cameraVerticalFov;
    /** Camera height in meters */
    float cameraHeight;

    /* Camera capture resolution */
    /* TODO: Use this in Camera */
    uint32_t captureResolutionCols;
    uint32_t captureResolutionRows;

    /** Projection width in meters */
    float projectionWidth;
    /** Projection height in meters */
    float projectionHeight;

    /** Projector height from the baseplate in meters */
    float projectorHeight;
    /** Projector resolution width in pixels */
    uint32_t projectorResolutionCols;
    /** Projector resolution height in pixels */
    uint32_t projectorResolutionRows;

    /** Max number of layers in a building */
    uint32_t maxLayers;

    /** Width of the baseplate in studs */
    uint32_t baseplateCols;
    /** Length of the baseplate in studs */
    uint32_t baseplateRows;

    /** Height of a block in meters */
    float blockHeight;
    /** Length of one block unit (width or length) in meters */
    float blockUnitLength;

    // The following calibration is not represented in pixels;
    // it's represented in a factor (percentage) of the projection image.
    // For example: (0.8, 0.2) is at the right-top of the projection image.
    /** Size of the baseplate on the projection image */
    Rect<float> projectionOutline;

    // The following calibration is not represented in pixels;
    // it's represented in a factor (percentage) of the projection image.
    // For example: (0.8, 0.2) is at the right-top of the projection image.
    Point<float> projectionInfoOrigin;
    Point<float> projectionStepInfoOrigin;
    Point<float> projectionMoveBaseplateWarningOrigin;
    // This is a factor of the projection image width.
    float projectionStepFontScale;
    float projectionMoveBaseplateWarningFontScale;
    // These are factors of the projection image height.
    float projectionSeparatorHeight;
    float projectionStudSize;
    float projectionStudInnerSize;
    float projectionBrickDistance;
    float projectionNextFactor;
    // This is a factor of the projection image width.
    float projectionNextHorizOffset;
};

const Calibration DEFAULT_CALIBRATION = constructS(Calibration,
    _.cameraHorizontalFov = 62.2f,
    _.cameraVerticalFov = 48.8f,
    _.cameraHeight = 0.65f,

    _.captureResolutionCols = 1440,
    _.captureResolutionRows = 1440,

    _.projectionWidth = 0.60f,
    _.projectionHeight = 0.40f,

    _.projectorResolutionCols = 1280,
    _.projectorResolutionRows = 720,

    _.maxLayers = 20,

    _.baseplateCols = 48,
    _.baseplateRows = 48,

    _.blockHeight = 0.0096,
    _.blockUnitLength = 0.008,

    _.projectionOutline = { { 0.08f, -0.18f }, 0.76f, 1.34f },

    _.projectionInfoOrigin = { 0.87f, 0.2f },
    _.projectionStepInfoOrigin = { 0.87f, 0.07f },
    _.projectionMoveBaseplateWarningOrigin = { 0.77f, 0.1f },

    _.projectionStepFontScale = 0.004f,
    _.projectionMoveBaseplateWarningFontScale = 0.0033f,

    _.projectionSeparatorHeight = 0.02f,
    _.projectionStudSize = 0.04f,
    _.projectionStudInnerSize = 0.035f,
    _.projectionBrickDistance = 0.01f,
    _.projectionNextFactor = 0.6f,
    _.projectionNextHorizOffset = 0.01f);

} // namespace cpparas

#endif /* CALIBRATION_HPP */
