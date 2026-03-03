#if !defined(GTKMM_EXAMPLE_HPP)
#define GTKMM_EXAMPLE_HPP 1

#include <gtkmm.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>

class MyWindow: public Gtk::Window {
 public:
  MyWindow();
  ~MyWindow() override;

 protected:
  // Signal handlers
  void hello_world_button();

  // Member widgets
  Gtk::Button m_button;
};

#endif /* !GTKMM_EXAMPLE_HPP */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
