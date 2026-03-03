#include <gtkmm/application.h>
#include <gtkmm/button.h>

#include <gtkmm_example.hpp>
#include <iostream>

#include "glibmm/signalproxy.h"
#include "gtkmm/box.h"
#include "gtkmm/enums.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "sigc++/functors/mem_fun.h"

MyWindow::MyWindow() {
  // This corresponds to Gtk::Bin::add_pixlabel("info.xpm", "cool button") in gtkmm3.
  // Create Image and Label widgets:
  auto pmap = Gtk::make_managed<Gtk::Image>("info.xpm");
  auto label = Gtk::make_managed<Gtk::Label>("cool button");
  label->set_expand(true);

  // Put them in a Box:
  auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
  hbox->append(*pmap);
  hbox->append(*label);

  // And put that Box in the button:
  m_button.set_child(*hbox);

  set_title("Pixmap'd buttons!");

  m_button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::hello_world_button));

  m_button.set_margin(10);
  set_child(m_button);
}

MyWindow::~MyWindow() {
}

void MyWindow::hello_world_button() {
  std::cout << "Hello World\n";
}

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.example");

  // Shows the window and returns when it is closed.
  return app->make_window_and_run<MyWindow>(argc, argv);
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
