#include "Locator.hpp"
#include "MarkerDetector.hpp"
#include "RegionExtractor.hpp"
#include <chrono>
#include <stdexcept>
#include <thread>

namespace cpparas {

Locator::Locator(std::shared_ptr<ImageLoader> imageLoader_)
    : imageLoader(imageLoader_)
    , PiCamera(1440, 1440)
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
    if (!locator_running) {
        locator_running = true;
        source_type = imageLoader->Get_source_type();
        locator_thread = std::thread(&Locator::Locator_thread, this);
        //lock calling thread until locator is running
        while(locator_thread_starting) {;}
    }
}

// Stop Locator thread. Also stops camera thread if active
void Locator::Stop_Locator_thread()
{
    locator_running = false;
    if (locator_thread.joinable()) {
        locator_thread.join();
    }
}

void Locator::Locator_thread()
{
    if (source_type == CAMERA) {
        //start Camera thread
        PiCamera.Camera_thread_worker_start();
    }
    while (locator_running) {
        if (source_type == CAMERA) {
            //Get a new frame from camera
            new_full_frame = PiCamera.Camera_get_frame();
        } else if (source_type == IMAGE) {
            //Load user image
            new_full_frame = imageLoader->Get_source_image();
        }
        //if new frame is none, camera is dead, so we need to stop locator
        if (new_full_frame == nullptr) {
            locator_running = false;
            break;
        }

        //find corners, warp and crop image here

        //save last frame to be used by main thread
        new_cut_frame = new_full_frame;

        //only unlock the main thread after at least a full frame has been received.
        locator_thread_starting = false;
        //wait a bit, no need to run this at full powaa
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    PiCamera.Camera_thread_worker_stop();
}

//Get latest cut frame from locator
image_t* Locator::Get_new_frame()
{
    if (!locator_running) {
        throw std::runtime_error("Camera and locator thread stopped unexpectedly");
    }
    if (new_cut_frame == nullptr) {
        throw std::runtime_error("Locator tried to return an empty image. You tried to use the camera on a device other than the Pi, didn't you? :)");
    }
    return new_cut_frame;
}

//Send a frame to image loader
void Locator::Send_frame_to_ui(image_t* frame)
{
    if (!locator_running) {
        throw std::runtime_error("Camera and locator thread stopped unexpectedly");
    }
    imageLoader->Set_UI_frame(frame);
}

} // namespace cpparas
