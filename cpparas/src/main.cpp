#include <gtkmm.h>

#include "Camera.hpp"
#include "ColorClassifier.hpp"
#include "ControlUI.hpp"
#include "CoordinateMatrix.hpp"
#include "HandDetection.hpp"
#include "ImageLoader.hpp"
#include "LSFParser.hpp"
#include "Locator.hpp"
#include "MarkerDetector.hpp"
#include "Projection.hpp"
#include "ProjectorUI.hpp"
#include "RegionExtractor.hpp"
#include "StateMachine.hpp"
#include "StudChecker.hpp"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    ControlUI controlUI;

    return app->run(controlUI);
}
