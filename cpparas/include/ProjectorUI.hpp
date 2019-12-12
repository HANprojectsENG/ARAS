#ifndef PROJECTORUI_HPP
#define PROJECTORUI_HPP

#include "Projection.hpp"
#include <gtkmm/window.h>

class ProjectorUI : public Gtk::Window {
public:
    ProjectorUI(std::shared_ptr<Projection> projection_);
    virtual ~ProjectorUI();

private:
    std::shared_ptr<Projection> projection;
};

#endif /* PROJECTORUI_HPP */
