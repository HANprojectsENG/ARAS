#include "MarkerDetector.hpp"
#include "operators.h"
#include "types/Point.hpp"
#include "util/ImageUtils.hpp"
#include <gtest/gtest.h>

using namespace cpparas;

TEST(MarkerDetectorSuite, DetectMarkers)
{
    const std::vector<std::string> imgPaths = {
        CPPARAS_TEST_DATA_DIR "/corners1.jpg",
        CPPARAS_TEST_DATA_DIR "/corners2.jpg",
    };
    std::vector<image_t*> images;
    for (const std::string& imgPath : imgPaths) {
        images.push_back(ImageUtils::loadImageFromFile(imgPath));
    }

    const std::vector<std::vector<Point<int32_t>>> expectedResults = {
        { { 176, 280 },
            { 968, 320 },
            { 944, 1080 } },
        { { 360, 216 },
            { 1160, 232 },
            { 1120, 1016 } }
    };
    const int32_t maxDeviation = 10;

    std::vector<std::vector<Point<int32_t>>> results;
    for (const image_t* image : images) {
        results.push_back(MarkerDetector::detectMarkers(image));
    }

    for (std::size_t idx = 0; idx < results.size(); idx++) {
        EXPECT_EQ(results[idx].size(), expectedResults[idx].size());
        for (std::size_t i = 0; i < std::min(results[idx].size(), expectedResults[idx].size()); i++) {
            EXPECT_LE(results[idx][i].distanceTo(expectedResults[idx][i]), maxDeviation) << "image " << idx << " point " << i << " " << results[idx][i].to_string() << " and " << expectedResults[idx][i].to_string() << " are not equal";
        }
        deleteImage(images[idx]);
    }
}
