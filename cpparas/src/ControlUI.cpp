#include "ControlUI.hpp"
#include "operators.h"
#include "util/ImageArea.hpp"
#include "util/ImageUtils.hpp"
#include <iostream>

ControlUI::ControlUI()
    : area()
{
    image_t* inputImage = ImageUtils::loadImageFromFile("../../snippets/setups/nobuilding/final_test_1.jpg");
    displayImage = ImageUtils::performTestOperations(inputImage);
    deleteImage(inputImage);

    area.setImage(displayImage);
    this->add(area);
    area.show();
}

ControlUI::~ControlUI()
{
    deleteImage(displayImage);
}

void ControlUI::on_button_clicked()
{
    std::cout << "Hello World" << std::endl;
}
