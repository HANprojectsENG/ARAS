#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include "Camera.hpp"
#include "ImageLoader.hpp"
#include "RegionExtractor.hpp"
#include "operators.h"
#include <thread>

namespace cpparas {

class Locator {
public:
    Locator(std::shared_ptr<ImageLoader> imageLoader_);
    ~Locator();
    void Start_Locator_thread();
    void Stop_Locator_thread();
    void Locator_thread();
    image_t* Get_new_frame();
    void Send_frame_to_ui(image_t* frame);

private:
    bool locator_running = false;
    bool locator_thread_starting = true;
    std::thread locator_thread;
    image_t* new_cut_frame;
    image_t* new_full_frame;
    SourceType source_type;
    std::shared_ptr<ImageLoader> imageLoader;
    Camera PiCamera;
};

} // namespace cpparas

#endif /* LOCATOR_HPP */
