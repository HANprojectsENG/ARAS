#include "debug/DebugUI.hpp"
#include "debug/Debug.hpp"
#include "util/ImageArea.hpp"
#include <glibmm/main.h>
#include <numeric>

namespace cpparas {

DebugUI::DebugUI(std::shared_ptr<StateMachine> stateMachine_)
    : stateMachine(stateMachine_)
    , widgetContainer()
    , logViewport()
    , logTextView()
    , stateNameLabel()
    , imageViewport()
    , imageContainer()
    , imageArea()
    , currentImage(nullptr)
{
    set_title("DebugUI");
    set_default_size(800, 700);
    set_resizable(false);

    widgetContainer.set_margin_top(5);
    widgetContainer.set_column_spacing(5);
    widgetContainer.set_row_spacing(5);
    widgetContainer.set_column_homogeneous(true);
    widgetContainer.set_row_homogeneous(true);
    logTextView.set_editable(false);
    logTextView.set_hexpand(true);
    imageViewport.set_hexpand(true);
    imageViewport.set_vexpand(true);

    stateNameLabel.set_justify(Gtk::JUSTIFY_LEFT);

    logViewport.add(logTextView);
    imageViewport.add(imageArea);
    widgetContainer.attach(stateNameLabel, 1, 1, 1, 1);
    widgetContainer.attach(logViewport, 1, 2, 1, 5);
    widgetContainer.attach(imageViewport, 1, 7, 1, 15);

    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &DebugUI::update),
        100);

    add(widgetContainer);
    widgetContainer.show();
    logTextView.show();
    logViewport.show();
    stateNameLabel.show();
    imageViewport.show();
    imageContainer.show();
    imageArea.show();
}

DebugUI::~DebugUI()
{
}

bool DebugUI::update()
{
    if (Debug::getLines()) {
        std::string newText = std::accumulate(Debug::getLines()->begin(), Debug::getLines()->end(), std::string(""), [](const std::string& ss, const std::string& s) {
            return ss.empty() ? s : ss + "\n" + s;
        });
        if (logTextView.get_buffer()->get_text() != newText) {
            logTextView.get_buffer()->set_text(newText);
            Glib::RefPtr<Gtk::Adjustment> adj = logViewport.get_vadjustment();
            adj->set_value(adj->get_upper());
        }
    }

    stateNameLabel.set_text(std::string("Current state: ") + stateMachine->getCurrentStateName());

    const image_t* image = Debug::getImage();
    if (currentImage != image) {
        if (image) {
            imageArea.setImage(image);
        }
        currentImage = image;
    }

    return true;
}

} // namespace cpparas
