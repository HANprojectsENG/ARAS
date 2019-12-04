#include "ControlUI.hpp"
#include "operators.h"
#include "util/ImageArea.hpp"
#include "util/ImageUtils.hpp"
#include <gtkmm.h>
#include <iostream>

const std::string TEST_IMAGE_PATH = "../../snippets/setups/nobuilding/test-small-markers.jpg";

ControlUI::ControlUI()
    : widgetContainer()
    , selectImageButton("Select image")
    , useCameraButton("Use camera")
    , separator()
    , imageViewport()
    , imageArea()
{
    this->set_input_image(TEST_IMAGE_PATH);
    this->set_title("Control UI");
    imageArea.setImage(displayImage);
    widgetContainer.set_row_spacing(5);
    widgetContainer.attach(selectImageButton, 1, 1);
    widgetContainer.attach(useCameraButton, 2, 1);
    widgetContainer.attach(separator, 3, 1);
    widgetContainer.attach(imageViewport, 1, 2, 3);
    selectImageButton.set_hexpand(false);
    useCameraButton.set_hexpand(false);
    separator.set_hexpand(true);
    imageViewport.set_vexpand(true);
    imageViewport.set_hexpand(true);
    imageViewport.add(imageArea);
    /* widgetContainer.set_expand(); */
    /* area.set_halign(Gtk::Align::FILL); */
    this->add(widgetContainer);
    selectImageButton.show();
    useCameraButton.show();
    imageArea.show();
    widgetContainer.show();
    separator.show();
    imageViewport.show();
}

ControlUI::~ControlUI()
{
    deleteImage(displayImage);
}

void ControlUI::on_button_clicked()
{
    std::cout << "Hello World" << std::endl;
}

void ControlUI::set_input_image(const std::string& filePath)
{
    image_t* inputImage = ImageUtils::loadImageFromFile(filePath);
    displayImage = ImageUtils::performTestOperations(inputImage);
    deleteImage(inputImage);
}
