#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "operators.h"
#include "types/Brick.hpp"
#include "types/Color.hpp"
#include <tuple>
#include <vector>

namespace cpparas {

class Projection {
public:
    Projection(uint32_t width, uint32_t height);
    ~Projection();

    void clear();
    void showOutline(Brick brick, int studX, int studY);
    void showInfo(int step, int layer, const std::vector<Brick>& expectedAndNextBricks);
    void complete();

    const image_t* getImage() const;

private:
    image_t* image;
    bool isAvailable;
};

} // namespace cpparas

#endif /* PROJECTION_HPP */
