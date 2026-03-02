#include <gtkmm.h>

#include <gtkmm_example.hpp>

MyWindow::MyWindow() {
  set_title("Basic application");
  set_default_size(200, 200);
}

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.examples.base");
  return app->make_window_and_run<MyWindow>(argc, argv);
}
