#ifndef CALIBRATION_HPP
#define CALIBRATION_HPP

#include <cstdint>

#define constructS(T, ...) \
    ([] { T _{}; __VA_ARGS__; return _; }())

namespace cpparas {

struct Calibration {
    float cameraHorizontalFov;
    float cameraVerticalFov;
    float cameraHeight;

    uint32_t captureResolutionCols;
    uint32_t captureResolutionRows;

    float projectionWidth;
    float projectionHeight;

    float projectorHeight;
    uint32_t projectorResolutionCols;
    uint32_t projectorResolutionRows;

    uint32_t maxLayers;
    uint32_t legoPerLayer;
    uint32_t dataPerLego;

    uint32_t baseplateCols;
    uint32_t baseplateRows;

    float blockHeight;
    float blockUnitLength;
    float maxBlockLayers;

    uint32_t boardLocationMargin;
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
    _.legoPerLayer = 50,
    _.dataPerLego = 28,

    _.baseplateCols = 48,
    _.baseplateRows = 48,

    _.blockHeight = 0.0096,
    _.blockUnitLength = 0.008,
    _.maxBlockLayers = 20,

    _.boardLocationMargin = 2);

} // namespace cpparas

#endif /* CALIBRATION_HPP */
