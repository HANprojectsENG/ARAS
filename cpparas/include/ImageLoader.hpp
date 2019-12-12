#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include "Camera.hpp"

class ImageLoader {
public:
    ImageLoader();

private:
    std::shared_ptr<Camera> camera;
};

#endif /* IMAGELOADER_HPP */
