#include "debug/DebugUI.hpp"
#include "debug/Debug.hpp"
#include <glibmm/main.h>
#include <numeric>

DebugUI::DebugUI(StateMachine* stateMachine_)
    : stateMachine(stateMachine_)
    , widgetContainer()
    , logViewport()
    , logTextView()
    , stateNameLabel()
    , brickPositionLabel("Brick position: 16,16 2x8")
    , expectedValueLabel("Expected colour: -")
{
    this->set_title("DebugUI");
    this->set_default_size(500, 400);
    this->set_resizable(false);

    widgetContainer.set_margin_top(5);
    widgetContainer.set_column_spacing(5);
    widgetContainer.set_row_spacing(5);
    widgetContainer.set_column_homogeneous(true);
    logTextView.set_editable(false);
    logTextView.set_hexpand(true);
    logTextView.set_vexpand(true);

    stateNameLabel.set_justify(Gtk::JUSTIFY_LEFT);
    brickPositionLabel.set_justify(Gtk::JUSTIFY_LEFT);
    expectedValueLabel.set_justify(Gtk::JUSTIFY_LEFT);

    logViewport.add(logTextView);
    widgetContainer.attach(stateNameLabel, 1, 1, 1, 1);
    widgetContainer.attach(brickPositionLabel, 2, 1, 1, 1);
    widgetContainer.attach(expectedValueLabel, 3, 1, 1, 1);
    widgetContainer.attach(logViewport, 1, 2, 3, 1);

    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &DebugUI::update),
        100);

    this->add(widgetContainer);
    widgetContainer.show();
    logTextView.show();
    logViewport.show();
    stateNameLabel.show();
    brickPositionLabel.show();
    expectedValueLabel.show();
}

DebugUI::~DebugUI()
{
}

bool DebugUI::update()
{
    if (Debug::lines) {
        std::string newText = std::accumulate(Debug::lines->begin(), Debug::lines->end(), std::string(""), [](const std::string& ss, const std::string& s) {
            return ss.empty() ? s : ss + "\n" + s;
        });
        if (logTextView.get_buffer()->get_text() != newText) {
            logTextView.get_buffer()->set_text(newText);
            Glib::RefPtr<Gtk::Adjustment> adj = logViewport.get_vadjustment();
            adj->set_value(adj->get_upper());
        }
    }

    stateNameLabel.set_text(std::string("Current state: ") + stateMachine->getCurrentStateName());

    return true;
}
