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
    /**
     * @brief Starts the locator thread if it's not already running.
     */
    void Start_Locator_thread();
    /**
     * @brief Stops the locator thread.
     */
    void Stop_Locator_thread();
    /**
     * @brief Returns the latest available cropped frame. Does not wait.
     */
    image_t* Get_new_frame();
    /**
     * @brief Sends a frame to the ImageLoader that is used by the ControlUI.
     */
    void Send_frame_to_ui(image_t* frame);
    /**
     * @brief Returns whether the first frame has been received.
     *        When using the camera, this will return false for a few seconds
     *        while the camera is warming up.
     */
    bool First_frame_received();
    /**
     * @brief Returns whether the baseplate is shifted and needs to be adjusted by the user.
     */
    bool Location_checker();

private:
    void Locator_thread();

    std::atomic<bool> locator_running;
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
    std::vector<Point<int32_t>> corner_points_old;
    Point<int32_t> Central_camera_point;
    Point<int32_t> Central_board_point;
};

} // namespace cpparas

#endif /* LOCATOR_HPP */
