#ifndef CALIBRATION_HPP
#define CALIBRATION_HPP

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
    _.blockUnitLength = 0.008);

} // namespace cpparas

#endif /* CALIBRATION_HPP */
