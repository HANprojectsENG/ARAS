#include "debug/DebugUI.hpp"
#include "debug/Debug.hpp"
#include <glibmm/main.h>
#include <numeric>

DebugUI::DebugUI()
    : widgetContainer()
    , logViewport()
    , logTextView()
{
    this->set_title("DebugUI");
    this->set_default_size(400, 300);
    this->set_resizable(false);

    logTextView.set_editable(false);
    logTextView.set_hexpand(true);
    logTextView.set_vexpand(true);

    logViewport.add(logTextView);
    widgetContainer.attach(logViewport, 1, 1, 1, 1);

    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &DebugUI::update),
        100);

    this->add(widgetContainer);
    widgetContainer.show();
    logTextView.show();
    logViewport.show();
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
    return true;
}
