#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "operators.h"
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

namespace cpparas {

class Camera {
public:
    Camera(uint32_t w, uint32_t h);
    ~Camera();
    void Camera_thread_worker();
    void Camera_thread_worker_start();
    void Camera_thread_worker_stop();
    image_t* Camera_get_frame();

protected:
    //camera stuff
    std::string raspi_parameters;
    uint32_t width, height;
    //buffer
    image_t* captured_frame;
    //threads
    bool threadRunning = false;
    std::thread camera_thread;
    bool is_ready = false;
    std::mutex mtx;
    std::condition_variable cond_var;
};

} // namespace cpparas

#endif /* CAMERA_HPP */
