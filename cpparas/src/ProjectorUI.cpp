#include "ProjectorUI.hpp"
#include <glibmm/main.h>

namespace cpparas {

ProjectorUI::ProjectorUI(std::shared_ptr<Projection> projection_)
    : projection(projection_)
    , imageArea()
{
    set_title("ProjectorUI");
    fullscreen();

    add(imageArea);

    imageArea.show();

    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &ProjectorUI::update),
        100);
}

ProjectorUI::~ProjectorUI()
{
}

bool ProjectorUI::update()
{
    const image_t* image = projection->getImage();
    if (image) {
        imageArea.setImage(image);
    }
    return true;
}

} // namespace cpparas
