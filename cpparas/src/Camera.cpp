#include "Camera.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include "operators.h"
//test
#include <chrono>

Camera::Camera(uint32_t w, uint32_t h)
{
    //compose final parameter string for raspivid
    width = w;
    height = h; 
    raspi_parameters = 
    " --width " + std::to_string(width) +
    " --height " + std::to_string(height) +
    " --metering matrix" +
    " --ISO 100" +
    //" --flush" +
    " --framerate 10" +
    " --initial pause" +
    " --timeout 0" +
    " --nopreview" +
    " --raw -" +
    " --raw-format rgb" +
    " --output /dev/null";  
}

Camera::~Camera()
{
    //kill the thread if object is done with life
    threadRunning = 2;
    if (thread1.joinable())
    {
        thread1.join();
    }
}

void Camera::Camera_thread_worker()
{
    //init new buffers
    Cam_data = new char[width*height*3];
    captured_frame = newRGB888Image(width, height);
    uint32_t bufferSize = width*height*3;
    //start raspivid and pipe
    std::string cmd="ls";// + raspi_parameters;
    FILE *fpipe = popen(cmd.c_str(),"r");
    if(fpipe==NULL) 
    {
        std::cout<<"Failed to open camera / pipe / raspivid"<<std::endl; 
    }
    else
    {
        while(threadRunning != 2)
        {
            //read pipe data into buffer. One whole frame per read
            auto result = fread (Cam_data,1,bufferSize,fpipe);
            //std::cout<<"read this many bytes: "<<std::to_string(result)<<" out of this many bytes: "<<std::to_string(bufferSize)<<std::endl;
            if(threadRunning == 0){threadRunning = 1;}

            //convert raw data to image_t if requested 
            if(get_new_frame){
                composed_frame = false;
                get_new_frame = false;
                for (uint32_t row = 0; row < height; row++) {
                    for (uint32_t col = 0; col < width; col++) {
                        rgb888_pixel_t pixel;
                        uint32_t index = row + col * 3;
                        pixel.r = Cam_data[index];
                        pixel.g = Cam_data[index + 1];
                        pixel.b = Cam_data[index + 2];
                        setRGB888Pixel(captured_frame, col, row, pixel);
                    }
                }
                composed_frame = true;
            }
        }    
        pclose(fpipe);
    }
}

void Camera::Camera_thread_worker_start()
{
    //start thread and wait till its's completelly up and running
    thread1 = std::thread (&Camera::Camera_thread_worker, this);
    while(threadRunning == 0){;}
}

image_t* Camera::Camera_get_frame()
{
    uint64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    //ask thread for a new frame, wait till its complete
    get_new_frame = true;
    composed_frame = false;
    while(composed_frame == false){;}

    uint64_t finish = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    uint64_t totaltime = finish - start;
    std::cout<<"get image op time(ms): "<<std::to_string(totaltime)<<std::endl;

    return captured_frame;
}
