#include "Locator.hpp"
#include "MarkerDetector.hpp"
#include "RegionExtractor.hpp"
#include <chrono>
#include <stdexcept>
#include <thread>

namespace cpparas {

Locator::Locator(std::shared_ptr<ImageLoader> imageLoader_)
    : locator_running(false)
    , first_frame(false)
    , moved_interupt(false)
    , active_corner_detection(true)
    , imageLoader(imageLoader_)
    , PiCamera(1440, 1440)
    , RegExtractor(800, 800)
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
    if (source_type == SourceType::CAMERA) {
        //start Camera thread
        PiCamera.Camera_thread_worker_start();
    }

    while (locator_running) {
        if (source_type == SourceType::CAMERA) {
            //Get a new frame from camera
            new_full_frame = PiCamera.Camera_get_frame();
        } else if (source_type == SourceType::IMAGE) {
            //Load user image
            new_full_frame = imageLoader->Get_source_image();
        } else {
            //smth is wrong I can feel it
            locator_running = false;
            break;
        }
        //if new frame is none, camera is dead, so we need to stop locator
        if (new_full_frame == nullptr) {
            locator_running = false;
            break;
        }

        //Get cameras center point
        Central_camera_point.col = new_full_frame->cols / 2;
        Central_camera_point.row = new_full_frame->rows / 2;

        //find corners
        if(active_corner_detection){
            corner_points = RegExtractor.updateImage(new_full_frame);
        }
        if (corner_points.size() == 3) {

            //caclulate center point based on 3 points
            Central_board_point.col = (corner_points[0].col + corner_points[2].col) / 2;
            // the magic number 50 is an offset because the camera is not perfectly centered to the projector
            Central_board_point.row = ((corner_points[0].row + corner_points[2].row) / 2) + 50;

            // Reset flag
            moved_interupt = false;

            //compare those points with the camera central point
            if ((Central_board_point.col - Central_camera_point.col) > MAX_DIVIATION || (Central_board_point.col - Central_camera_point.col) < -MAX_DIVIATION) {
                moved_interupt = true;
            }

            if ((Central_board_point.row - Central_camera_point.row) > MAX_DIVIATION || (Central_board_point.row - Central_camera_point.row) < -MAX_DIVIATION) {
                moved_interupt = true;
            }

            // Get the new cut frame
            new_cut_frame = RegExtractor.getRegionImage();

            // Save good coordinates
            corner_points_old = corner_points;

            // Set first frame accuaried bool
            if (!first_frame) {
                first_frame = true;
            }

        } else {
            //No new points found but we have older coordinates
            if (corner_points_old.size() == 3) {
                int32_t colpos[3] = {
                    corner_points_old[0].col,
                    corner_points_old[1].col,
                    corner_points_old[2].col,
                };
                int32_t rowpos[3] = {
                    corner_points_old[0].row,
                    corner_points_old[1].row,
                    corner_points_old[2].row
                };
                //cut and warp frame using old coordinates
                warp(new_full_frame, new_cut_frame, colpos, rowpos);
            } else {
                // If no points were found at all, do nothing and try again
                std::cout<<"No coordinates found, like at all, not even once since we started:/"<<std::endl;
            }
        }

        //wait a bit, no need to run this at full powaa
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    PiCamera.Camera_thread_worker_stop();
}

//Get latest cut frame from locator
image_t* Locator::Get_new_frame()
{
    if (!locator_running) {
        throw std::runtime_error("Camera and locator thread stopped unexpectedly");
    }
    if (new_cut_frame->type != IMGTYPE_RGB888) {
        throw std::runtime_error("Locator tried to return wrong type (and probably empty) image. That's not good");
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

// Check if at least one frame is available
bool Locator::First_frame_received()
{
    return first_frame;
}

// Check if board or camera has moved
bool Locator::Location_checker()
{
    return moved_interupt;
}

void Locator::Active_corner_detection(bool state)
{
    active_corner_detection = state;
}

} // namespace cpparas
