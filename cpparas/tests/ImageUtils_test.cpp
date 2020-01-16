#include "operators.h"
#include "util/ImageUtils.hpp"
#include <cstring>
#include <gdkmm/pixbuf.h>
#include <gtest/gtest.h>
#include <stdio.h>

using namespace cpparas;

TEST(ImageUtilsSuite, LoadImageFromFile)
{
    const std::string imgPath = CPPARAS_TEST_DATA_DIR "/loadimage.png";
    image_t* image = ImageUtils::loadImageFromFile(imgPath);

    const int nPixels = 4;
    rgb888_pixel_t expectedData[4] = {
        { 0, 0, 0 },
        { 255, 0, 0 },
        { 0, 255, 0 },
        { 0, 0, 255 }
    };

    EXPECT_EQ(image->cols, 2) << "image number of columns is not equal";
    EXPECT_EQ(image->rows, 2) << "image number of rows is not equal";
    EXPECT_EQ(image->type, IMGTYPE_RGB888) << "image type is not equal";
    EXPECT_EQ(image->view, IMGVIEW_CLIP) << "image view is not equal";

    for (std::size_t idx = 0; idx < nPixels; idx++) {
        EXPECT_EQ(((rgb888_pixel_t*)image->data)[idx].r, expectedData[idx].r) << "pixel " << idx << " r is not equal";
        EXPECT_EQ(((rgb888_pixel_t*)image->data)[idx].g, expectedData[idx].g) << "pixel " << idx << " g is not equal";
        EXPECT_EQ(((rgb888_pixel_t*)image->data)[idx].b, expectedData[idx].b) << "pixel " << idx << " b is not equal";
    }

    deleteImage(image);
}

// NOTE: This test depends on correct loadImageFromFile behaviour.
TEST(ImageUtilsSuite, SaveImageToFile)
{
    const std::string imgPath = CPPARAS_TEST_DATA_DIR "/loadimage.png";
    image_t* image = ImageUtils::loadImageFromFile(imgPath);
    const std::string saveImgPath = P_tmpdir "/cpparas_test.png";

    ImageUtils::saveImageToFile(image, saveImgPath, "png");
    image_t* savedImage = ImageUtils::loadImageFromFile(imgPath);

    EXPECT_EQ(savedImage->cols, image->rows) << "image number of columns is not equal";
    EXPECT_EQ(savedImage->rows, image->rows) << "image number of rows is not equal";
    for (int idx = 0; idx < savedImage->cols * savedImage->rows; idx++) {
        EXPECT_EQ(((rgb888_pixel_t*)savedImage->data)[idx].r, ((rgb888_pixel_t*)image->data)[idx].r) << "pixel " << idx << " r is not equal";
        EXPECT_EQ(((rgb888_pixel_t*)savedImage->data)[idx].g, ((rgb888_pixel_t*)image->data)[idx].g) << "pixel " << idx << " g is not equal";
        EXPECT_EQ(((rgb888_pixel_t*)savedImage->data)[idx].b, ((rgb888_pixel_t*)image->data)[idx].b) << "pixel " << idx << " b is not equal";
    }

    deleteImage(image);
}

// NOTE: This test depends on correct loadImageFromFile behaviour.
TEST(ImageUtilsSuite, ImageToPixBuf)
{
    const std::string imgPath = CPPARAS_TEST_DATA_DIR "/loadimage.png";
    image_t* image = ImageUtils::loadImageFromFile(imgPath);

    Glib::RefPtr<Gdk::Pixbuf> pixbuf = ImageUtils::imageToPixbuf(image);

    EXPECT_EQ(pixbuf->get_width(), image->cols);
    EXPECT_EQ(pixbuf->get_height(), image->rows);
    EXPECT_EQ(pixbuf->get_n_channels(), 3);

    deleteImage(image);
}

TEST(ImageUtilsSuite, PixBufToImage)
{
    const std::string imgPath = CPPARAS_TEST_DATA_DIR "/loadimage.png";
    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(imgPath);

    image_t* image = ImageUtils::pixbufToImage(pixbuf);

    EXPECT_EQ(image->cols, pixbuf->get_width());
    EXPECT_EQ(image->rows, pixbuf->get_height());
    EXPECT_EQ(image->type, IMGTYPE_RGB888) << "image type is not equal";
    EXPECT_EQ(image->view, IMGVIEW_CLIP) << "image view is not equal";

    deleteImage(image);
}
