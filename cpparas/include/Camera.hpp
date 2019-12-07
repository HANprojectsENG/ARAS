#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <iostream>
#include <thread>
#include "operators.h"

class Camera {
public:
    Camera(uint32_t w, uint32_t h);
    ~Camera();
    void Camera_thread_worker();
    void Camera_thread_worker_start();
    image_t* Camera_get_frame();

private:
    image_t* captured_frame;
    bool composed_frame = false;
    bool get_new_frame = false;
    std::thread thread1;
    uint32_t threadRunning = 0;
    char *Cam_data;
    std::string raspi_parameters;
    uint32_t width, height;
};

#endif /* CAMERA_HPP */
