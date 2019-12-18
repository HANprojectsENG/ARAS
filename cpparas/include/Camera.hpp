#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <iostream>
#include <thread>
#include <mutex> 
#include <condition_variable>
#include "operators.h"

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

#endif /* CAMERA_HPP */
