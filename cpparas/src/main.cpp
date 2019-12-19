#include <gtkmm.h>

#include "ControlUI.hpp"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    ControlUI controlUI;

    return app->run(controlUI);
}
