#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include "Camera.hpp"
#include "ImageLoader.hpp"
#include "RegionExtractor.hpp"
#include "operators.h"
#include <atomic>
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
    bool First_frame_received();
    bool Location_checker();

private:
    std::atomic<bool> locator_running;
    std::atomic<bool> locator_thread_starting;
    std::atomic<bool> first_frame;
    std::atomic<bool> moved_interupt;
    std::thread locator_thread;
    image_t* new_cut_frame;
    image_t* new_full_frame;
    SourceType source_type;
    std::shared_ptr<ImageLoader> imageLoader;
    Camera PiCamera;
    RegionExtractor RegExtractor;
    int32_t MAX_DIVIATION = 20;
    std::vector<Point<int32_t>> corner_points;
    Point<int32_t> Central_camera_point;
    Point<int32_t> Central_board_point;
};

} // namespace cpparas

#endif /* LOCATOR_HPP */
