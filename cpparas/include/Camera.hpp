#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "operators.h"
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

namespace cpparas {

class Camera {
public:
    /**
     * @brief Creates a camera device.
     * @input w Frame buffer width. Needs to be supported by `raspivid`.
     * @input h Frame buffer height.
     */
    Camera(uint32_t w, uint32_t h);
    ~Camera();
    /**
     * @brief Starts the camera thread which will capture frames.
     * @note This function does no checking on whether a camera thread has already been started.
     */
    void Camera_thread_worker_start();
    /**
     * @brief Stops the camera thread.
     */
    void Camera_thread_worker_stop();
    /**
     * @brief Waits for a camera frame to be available.
     * @return valid pointer = frame has been received successfully. nullptr = camera thread has failed.
     */
    image_t* Camera_get_frame();

private:
    void Camera_thread_worker();
    //camera stuff
    std::string raspi_parameters;
    uint32_t width, height;
    //buffer
    image_t* captured_frame;
    //threads
    std::atomic<bool> threadRunning;
    std::atomic<bool> is_ready;
    std::thread camera_thread;
    std::mutex mtx;
    std::condition_variable cond_var;
};

} // namespace cpparas

#endif /* CAMERA_HPP */
