#include "Camera.hpp"
#include "operators.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <unistd.h>

namespace cpparas {

//MAX SUPPORTED RESOLUTION FOR CONSTRUCTOR IS 1440x1440.
//IF USING ANYTHING BELOW THAT, MAKE SURE PIXEL ASPECT RATIO IS 1:1

Camera::Camera(uint32_t w, uint32_t h)
    : threadRunning(false)
    , is_ready(false)
{
    //compose final parameter string for raspivid
    width = w;
    height = h;
    raspi_parameters = " -md 2 --width " + std::to_string(width) + " --height " + std::to_string(height) + " --metering matrix" + " --ISO 100" + " --flush" + " --framerate 15" + " --initial pause" + " --timeout 0" + " --nopreview" + " --raw -" + " --raw-format rgb";
}

Camera::~Camera()
{
    //kill the thread if object is done with life
    threadRunning = false;
    if (camera_thread.joinable()) {
        camera_thread.join();
    }
}

void Camera::Camera_thread_worker()
{
    //init new buffer
    captured_frame = newRGB888Image(width, height);
    captured_frame->view = IMGVIEW_CLIP;
    captured_frame->type = IMGTYPE_RGB888;
    uint32_t bufferSize = width * height * 3;
    //start raspivid and pipe
    std::string cmd = "raspivid" + raspi_parameters;
    FILE* fpipe = popen(cmd.c_str(), "r");
    if (fpipe == NULL) {
        std::cout << "Failed to open camera / pipe / raspivid" << std::endl;
    } else {
        while (threadRunning) {
            // read pipe data into buffer. One whole frame per read
            // if all bytes are in, convert raw data to image_t
            size_t readBytes = fread((uint8_t*)captured_frame->data, 1, bufferSize, fpipe);
            if (readBytes != bufferSize) {
                threadRunning = false;
            }
            // signal main thread that a new frame is ready, unlock mutex
            std::unique_lock<std::mutex> locker(mtx);
            is_ready = true;
            cond_var.notify_one();
        }
        // close pipe, also kill raspivid in the process by starving mmal, sorry raspivid :(
        pclose(fpipe);
    }
}

void Camera::Camera_thread_worker_start()
{
    //start thread and wait till its's completelly up and running
    threadRunning = true;
    camera_thread = std::thread(&Camera::Camera_thread_worker, this);
    std::unique_lock<std::mutex> locker(mtx);
    while (!is_ready) {
        cond_var.wait(locker);
    }
}

void Camera::Camera_thread_worker_stop()
{
    threadRunning = false;
    if (camera_thread.joinable()) {
        camera_thread.join();
    }
}

image_t* Camera::Camera_get_frame()
{
    //chek if camera is running
    if (threadRunning) {
        //wait for new frame to be available
        is_ready = false;
        std::unique_lock<std::mutex> locker(mtx);
        while (!is_ready) {
            cond_var.wait(locker);
        }
    }
    //check camera again, in case camera crashed while getting a new frame
    if (threadRunning) {
        return captured_frame;
    } else {
        return nullptr;
    }
}

} // namespace cpparas
