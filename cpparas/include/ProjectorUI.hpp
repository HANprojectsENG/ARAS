#ifndef PROJECTORUI_HPP
#define PROJECTORUI_HPP

#include "Projection.hpp"
#include "util/ImageArea.hpp"
#include <gtkmm/window.h>

namespace cpparas {

class ProjectorUI : public Gtk::Window {
public:
    ProjectorUI(std::shared_ptr<Projection> projection_);
    virtual ~ProjectorUI();

private:
    bool update();

    std::shared_ptr<Projection> projection;
    ImageArea imageArea;
};

} // namespace cpparas

#endif /* PROJECTORUI_HPP */
