#include <gio/gio.h>           // for g_application_run, G_APPLICATION, G_AP...
#include <glib-object.h>       // for g_signal_connect, g_object_unref, g_si...
#include <glib.h>              // for g_print, gpointer
#include <gtk/gtk.h>           // for gtk_button_new_with_label, gtk_grid_at...
#include <stdlib.h>            // for NULL
#include <gobject/gclosure.h>  // for G_CALLBACK
#include <jeff/jeff_gtk.h>     // for activate, print_hello

void print_hello(GtkWidget *widget, gpointer user_data) { g_print("Hello World!\n"); }

void activate(GtkApplication *app, gpointer data) {
  GtkWidget *window, *grid, *button;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);

  button = gtk_button_new_with_label("Button 1");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label("Button 2");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label("QUIT");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);
  gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 4, 1);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
