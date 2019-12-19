#ifndef CONTROLUI_HPP
#define CONTROLUI_HPP

#include "ImageLoader.hpp"
#include "LSFParser.hpp"
#include "Locator.hpp"
#include "StateMachine.hpp"
#include "debug/DebugUI.hpp"
#include "util/ImageArea.hpp"
#include "util/StateMachineWidget.hpp"
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/separator.h>
#include <gtkmm/window.h>
#include <memory>

class ControlUI : public Gtk::Window {
public:
    ControlUI();
    virtual ~ControlUI();

private:
    void set_input_image(const std::string& filePath);
    void set_sequence_file(const std::string& filePath);
    void on_select_image_button_clicked();
    void on_use_last_image_button_clicked();
    void on_use_camera_button_clicked();
    void on_select_sequence_file_button_clicked();
    void on_use_last_sequence_file_button_clicked();
    void on_open_debug_ui_button_clicked();

    image_t* displayImage;
    std::shared_ptr<StateMachine> stateMachine;
    std::shared_ptr<ImageLoader> imageLoader;
    std::shared_ptr<Locator> locator;

    std::shared_ptr<DebugUI> debugUI;

    Gtk::Grid widgetContainer;
    Gtk::Button selectImageButton;
    Gtk::Button useLastImageButton;
    Gtk::Button useCameraButton;
    Gtk::Separator separator1;
    Gtk::Button selectSequenceFileButton;
    Gtk::Button useLastSequenceFileButton;
    Gtk::Separator separator2;
    Gtk::Button openDebugUIButton;
    Gtk::Separator separator3;
    Gtk::ScrolledWindow imageViewport;
    StateMachineWidget stateMachineWidget;
    ImageArea imageArea;
};

#endif /* CONTROLUI_HPP */
