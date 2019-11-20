#include "ImageArea.hpp"
#include <gtkmm.h>

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    Gtk::Window window;
    window.set_default_size(200, 200);

    const int32_t IMAGE_COLS = 200;
    const int32_t IMAGE_ROWS = 200;
    image_t* image = newRGB888Image(IMAGE_COLS, IMAGE_ROWS);
    for (int32_t j = 0; j < IMAGE_ROWS; j++) {
        for (int32_t i = 0; i < IMAGE_COLS; i++) {
            setRGB888Pixel(image, i, j, (rgb888_pixel_t) { .r = 255, .g = 0, .b = 0 });
        }
    }

    ImageArea area;
    area.setImage(image);
    window.add(area);
    area.show();

    return app->run(window);
}
