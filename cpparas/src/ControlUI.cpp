#include "ControlUI.hpp"
#include "debug/DebugUI.hpp"
#include "operators.h"
#include "util/ImageArea.hpp"
#include "util/ImageUtils.hpp"
#include "util/Preferences.hpp"
#include <fstream>
#include <gtkmm/filechooserdialog.h>
#include <iostream>

const std::string LAST_IMAGE_CONF_PATH = ".cpparas-last-image";

ControlUI::ControlUI()
    : displayImage(nullptr)
    , stateMachine(std::make_shared<StateMachine>())
    , widgetContainer()
    , selectImageButton("Select image")
    , useLastImageButton("Use last")
    , useCameraButton("Use camera")
    , separator1()
    , selectSequenceFileButton("Select sequence file")
    , useLastSequenceFileButton("Use last")
    , separator2()
    , openDebugUIButton("Debug")
    , separator3()
    , imageViewport()
    , stateMachineWidget(stateMachine)
    , imageArea()
{
    this->set_title("Control UI");

    widgetContainer.set_margin_top(5);
    widgetContainer.set_column_spacing(5);
    widgetContainer.set_row_spacing(5);
    separator3.set_hexpand(true);
    stateMachineWidget().set_hexpand(true);
    stateMachineWidget().set_vexpand(false);
    imageViewport.set_vexpand(true);
    imageViewport.set_hexpand(true);

    selectImageButton.signal_clicked().connect(sigc::mem_fun(*this,
        &ControlUI::on_select_image_button_clicked));
    useLastImageButton.signal_clicked().connect(sigc::mem_fun(*this,
        &ControlUI::on_use_last_image_button_clicked));
    useCameraButton.signal_clicked().connect(sigc::mem_fun(*this,
        &ControlUI::on_use_camera_button_clicked));
    selectSequenceFileButton.signal_clicked().connect(sigc::mem_fun(*this,
        &ControlUI::on_select_sequence_file_button_clicked));
    useLastSequenceFileButton.signal_clicked().connect(sigc::mem_fun(*this,
        &ControlUI::on_use_last_sequence_file_button_clicked));
    openDebugUIButton.signal_clicked().connect(sigc::mem_fun(*this,
        &ControlUI::on_open_debug_ui_button_clicked));

    imageViewport.add(imageArea);
    widgetContainer.attach(selectImageButton, 1, 1, 1, 1);
    widgetContainer.attach(useLastImageButton, 2, 1, 1, 1);
    widgetContainer.attach(useCameraButton, 3, 1, 1, 1);
    widgetContainer.attach(separator1, 4, 1, 1, 1);
    widgetContainer.attach(selectSequenceFileButton, 5, 1, 1, 1);
    widgetContainer.attach(useLastSequenceFileButton, 6, 1, 1, 1);
    widgetContainer.attach(separator2, 7, 1, 1, 1);
    widgetContainer.attach(openDebugUIButton, 8, 1, 1, 1);
    widgetContainer.attach(separator3, 9, 1, 1, 1);
    widgetContainer.attach(stateMachineWidget(), 1, 2, 9, 1);
    widgetContainer.attach(imageViewport, 1, 3, 9, 1);
    this->add(widgetContainer);

    selectImageButton.show();
    useLastImageButton.show();
    useCameraButton.show();
    separator1.show();
    selectSequenceFileButton.show();
    useLastSequenceFileButton.show();
    widgetContainer.show();
    separator2.show();
    openDebugUIButton.show();
    separator3.show();
    imageViewport.show();
    stateMachineWidget().show();
    imageArea.show();

    useLastImageButton.grab_focus();
}

ControlUI::~ControlUI()
{
    if (displayImage)
        deleteImage(displayImage);
}

void ControlUI::on_select_image_button_clicked()
{
    Gtk::FileChooserDialog dialog("Please choose a file",
        Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:
    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Image files");
    filter_text->add_pixbuf_formats();
    dialog.add_filter(filter_text);

    //Show the dialog and wait for a user response:
    int result = dialog.run();

    //Handle the response:
    switch (result) {
    case (Gtk::RESPONSE_OK): {
        std::string filename = dialog.get_filename();
        this->set_input_image(filename);
        break;
    }
    default: {
        // User cancelled.
        break;
    }
    }
}

void ControlUI::on_use_last_image_button_clicked()
{
    Preferences preferences = Preferences::fromFile();
    if (preferences.lastImageFile == "") {
        return;
    }
    this->set_input_image(preferences.lastImageFile);
}

void ControlUI::on_use_camera_button_clicked()
{
}

void ControlUI::on_select_sequence_file_button_clicked()
{
    Gtk::FileChooserDialog dialog("Please choose a file",
        Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:
    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Lego Sequence File");
    filter_text->add_pattern("*.lsf");
    dialog.add_filter(filter_text);

    //Show the dialog and wait for a user response:
    int result = dialog.run();

    //Handle the response:
    switch (result) {
    case (Gtk::RESPONSE_OK): {
        std::string filename = dialog.get_filename();
        this->set_sequence_file(filename);
        break;
    }
    default: {
        // User cancelled.
        break;
    }
    }
}

void ControlUI::on_use_last_sequence_file_button_clicked()
{
    Preferences preferences = Preferences::fromFile();
    if (preferences.lastSequenceFile == "") {
        return;
    }
    this->set_sequence_file(preferences.lastSequenceFile);
}

void ControlUI::on_open_debug_ui_button_clicked()
{
    debugUI = std::make_shared<DebugUI>(stateMachine);
    debugUI->show();
}

void ControlUI::set_input_image(const std::string& filePath)
{
    image_t* inputImage = ImageUtils::loadImageFromFile(filePath);

    if (displayImage)
        deleteImage(displayImage);
    displayImage = ImageUtils::performTestOperations(inputImage);
    deleteImage(inputImage);
    imageArea.setImage(displayImage);

    Preferences newPreferences;
    newPreferences.lastImageFile = filePath;
    newPreferences.saveToFile();
}

void ControlUI::set_sequence_file(const std::string& filePath)
{
    lsfData = std::make_shared<LSFParser::LSFData>(LSFParser::Load_LSF_file(filePath));

    Preferences newPreferences;
    newPreferences.lastSequenceFile = filePath;
    newPreferences.saveToFile();
}
