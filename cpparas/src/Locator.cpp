#include <thread>
#include <chrono>
#include <stdexcept>
#include "Locator.hpp"
#include "MarkerDetector.hpp"
#include "RegionExtractor.hpp"

Locator::Locator(std::shared_ptr<StateMachine> stateMachine_, std::shared_ptr<ImageLoader> imageLoader_)
    : stateMachine(stateMachine_)
    , imageLoader(imageLoader_)
    , PiCamera(1440,1440)
{
}

//Kill thread, which in turn will kill camera thread as well;
Locator::~Locator()
{
    locator_running = false;
    if (locator_thread.joinable()) {
        locator_thread.join();
    }
}

//Start locator thread
void Locator::Start_Locator_thread()
{
    locator_running = true;
    locator_thread = std::thread(&Locator::Locator_thread, this);
}

void Locator::Locator_thread()
{
    //start Camera thread
    PiCamera.Camera_thread_worker_start();
    while(locator_running)
    {
        //Get a new frame
        new_full_frame = PiCamera.Camera_get_frame();
        //if new frame is none, camera is dead, so we need to stop locator
        if(new_full_frame == nullptr)
        {
            locator_running = false;
            break;
        }

        //find corners, warp and crop image here

        //save last frame to be used by main thread
        last_cut_frame = new_cut_frame;

        //wait a bit, no need to run this at full powaa
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    PiCamera.Camera_thread_worker_stop();
    
}

image_t* Locator::Get_new_frame()
{
    if(!locator_running)
    {
        throw std::runtime_error("Camera and locator thread stopped unexpectedly");
    }
    return last_cut_frame;
    
}