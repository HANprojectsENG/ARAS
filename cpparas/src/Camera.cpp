#include "Camera.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include "operators.h"

//MAX SUPPORTED RESOLUTION FOR CONSTRUCTOR IS 1440x1440.
//IF USING ANYTHING BELOW THAT, MAKE SURE PIXEL ASPECT RATIO IS 1:1


Camera::Camera(uint32_t w, uint32_t h)
{
    //compose final parameter string for raspivid
    width = w;
    height = h; 
    raspi_parameters = 
    " -md 2 --width " + std::to_string(width) +
    " --height " + std::to_string(height) +
    " --metering matrix" +
    " --ISO 100" +
    " --flush" +
    " --framerate 15" +
    " --initial pause" +
    " --timeout 0" +
    " --nopreview" +
    " --raw -" +
    " --raw-format rgb"; 
}

Camera::~Camera()
{
    //kill the thread if object is done with life
    threadRunning = false;
    if (camera_thread.joinable()){
        camera_thread.join();
    }
}

void Camera::Camera_thread_worker()
{
    //init new buffer
    captured_frame = newRGB888Image(width, height);
    uint32_t bufferSize = width*height*3;
    //start raspivid and pipe
    std::string cmd="raspivid" + raspi_parameters;
    FILE *fpipe = popen(cmd.c_str(),"r");
    if(fpipe==NULL) {
        std::cout<<"Failed to open camera / pipe / raspivid"<<std::endl; 
    }
    else{
        while(threadRunning){
            // read pipe data into buffer. One whole frame per read
            // if all bytes are in, convert raw data to image_t
            fread ((uint8_t*)captured_frame->data,1,bufferSize,fpipe);

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
    camera_thread = std::thread (&Camera::Camera_thread_worker, this);
    std::unique_lock<std::mutex> locker(mtx);
    while (!is_ready)
    {cond_var.wait(locker);}
}

image_t* Camera::Camera_get_frame()
{
    //ask thread for new frame, lock main thread while getting frame
    is_ready = false;
    std::unique_lock<std::mutex> locker(mtx);
    while (!is_ready)
    {cond_var.wait(locker);}
    return captured_frame;
}

void Camera::Camera_calibrate()
{
    if(threadRunning){
        if (camera_thread.joinable()){
            camera_thread.join();
        }
    }
    raspivid_out = new char[5000];
    std::string cmd="raspivid -md 2 --width " + std::to_string(width) +
    " --height " + std::to_string(height) +
    " --nopreview --ISO 100 --settings -o /dev/null -t 1";
    FILE *fpipe = popen(cmd.c_str(),"r");
    if(fpipe==NULL) {
        std::cout<<"Failed to open camera / pipe / raspivid"<<std::endl; 
    }
    else{
        uint32_t result = fread (raspivid_out,1,5000,fpipe);
        std::cout<<std::to_string(result)<<std::endl;
        std::string output(raspivid_out);
        std::cout<<output<<std::endl;
    }
}
