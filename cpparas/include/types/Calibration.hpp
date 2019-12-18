#ifndef CALIBRATION_HPP
#define CALIBRATION_HPP

#include <cstdint>

#define with(T, ...) \
    ([] { T ${}; __VA_ARGS__; return $; }())

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

const Calibration DEFAULT_CALIBRATION = with(Calibration,
    $.cameraHorizontalFov = 62.2f,
    $.cameraVerticalFov = 48.8f,
    $.cameraHeight = 0.65f,

    $.captureResolutionCols = 1440,
    $.captureResolutionRows = 1440,

    $.projectionWidth = 0.60f,
    $.projectionHeight = 0.40f,

    $.projectorResolutionCols = 1280,
    $.projectorResolutionRows = 720,

    $.maxLayers = 20,
    $.legoPerLayer = 50,
    $.dataPerLego = 28,

    $.baseplateCols = 48,
    $.baseplateRows = 48,

    $.blockHeight = 0.0096,
    $.blockUnitLength = 0.008,
    $.maxBlockLayers = 20,

    $.boardLocationMargin = 2);

#endif /* CALIBRATION_HPP */
