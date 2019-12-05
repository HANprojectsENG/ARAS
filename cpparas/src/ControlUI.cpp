#include "ControlUI.hpp"
#include "operators.h"
#include "util/ImageArea.hpp"
#include "util/ImageUtils.hpp"
#include <fstream>
#include <gtkmm/filechooserdialog.h>
#include <iostream>

const std::string LAST_IMAGE_CONF_PATH = ".cpparas-last-image";

ControlUI::ControlUI()
    : widgetContainer()
    , selectImageButton("Select image")
    , useLastImageButton("Use last image")
    , useCameraButton("Use camera")
    , separator()
    , imageViewport()
    , imageArea()
    , displayImage(nullptr)
{
    this->set_title("Control UI");

    widgetContainer.set_margin_top(5);
    widgetContainer.set_column_spacing(5);
    widgetContainer.set_row_spacing(5);
    selectImageButton.set_hexpand(false);
    useLastImageButton.set_hexpand(false);
    useCameraButton.set_hexpand(false);
    separator.set_hexpand(true);
    imageViewport.set_vexpand(true);
    imageViewport.set_hexpand(true);

    selectImageButton.signal_clicked().connect(sigc::mem_fun(*this,
        &ControlUI::on_select_image_button_clicked));
    useLastImageButton.signal_clicked().connect(sigc::mem_fun(*this,
        &ControlUI::on_use_last_image_button_clicked));
    useCameraButton.signal_clicked().connect(sigc::mem_fun(*this,
        &ControlUI::on_use_camera_button_clicked));

    imageViewport.add(imageArea);
    widgetContainer.attach(selectImageButton, 1, 1, 1, 1);
    widgetContainer.attach(useLastImageButton, 2, 1, 1, 1);
    widgetContainer.attach(useCameraButton, 3, 1, 1, 1);
    widgetContainer.attach(separator, 4, 1, 1, 1);
    widgetContainer.attach(imageViewport, 1, 2, 4, 1);
    this->add(widgetContainer);

    selectImageButton.show();
    useLastImageButton.show();
    useCameraButton.show();
    widgetContainer.show();
    separator.show();
    imageViewport.show();
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
    std::ifstream inFile(LAST_IMAGE_CONF_PATH);
    if (!inFile.good())
        return;
    std::string filePath;
    std::getline(inFile, filePath);
    inFile.close();
    this->set_input_image(filePath);
}

void ControlUI::on_use_camera_button_clicked()
{
    // TODO: remove test code.
    StateMachine st;
    st.init();
    st.doCycle();
}

void ControlUI::set_input_image(const std::string& filePath)
{
    image_t* inputImage = ImageUtils::loadImageFromFile(filePath);

    std::ofstream outFile(LAST_IMAGE_CONF_PATH);
    outFile << filePath;
    outFile.close();

    if (displayImage)
        deleteImage(displayImage);
    displayImage = ImageUtils::performTestOperations(inputImage);
    deleteImage(inputImage);
    imageArea.setImage(displayImage);
}