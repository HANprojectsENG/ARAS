#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include "ImageLoader.hpp"
#include "RegionExtractor.hpp"
#include "StateMachine.hpp"

class Locator {
public:
    Locator(std::shared_ptr<StateMachine> stateMachine_, std::shared_ptr<ImageLoader> imageLoader_);

private:
    std::shared_ptr<StateMachine> stateMachine;
    std::shared_ptr<ImageLoader> imageLoader;
};

#endif /* LOCATOR_HPP */
