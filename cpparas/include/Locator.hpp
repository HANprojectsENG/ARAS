#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include <thread>
#include "ImageLoader.hpp"
#include "RegionExtractor.hpp"
#include "StateMachine.hpp"
#include "operators.h"
#include "Camera.hpp"

class Locator {
public:
    Locator(std::shared_ptr<StateMachine> stateMachine_, std::shared_ptr<ImageLoader> imageLoader_);
    ~Locator();
    void Start_Locator_thread();
    void Locator_thread();
    image_t* Get_new_frame();

private:
    bool locator_running = false;
    std::thread locator_thread; 
    image_t* last_cut_frame;
    image_t* new_cut_frame;
    image_t* new_full_frame;
    std::shared_ptr<StateMachine> stateMachine;
    std::shared_ptr<ImageLoader> imageLoader;
    Camera PiCamera;
};

#endif /* LOCATOR_HPP */
