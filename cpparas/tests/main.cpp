#include <gtest/gtest.h>
#include <gtkmm.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    int ret = RUN_ALL_TESTS();
    return ret;
}
