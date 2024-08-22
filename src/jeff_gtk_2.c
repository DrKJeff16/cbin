#include <gio/gio.h>           // for g_application_run, G_APPLICATION, G_AP...
#include <glib-object.h>       // for g_object_unref, g_signal_connect, g_si...
#include <glib.h>              // for g_print, gpointer
#include <gtk/gtk.h>           // for GTK_WINDOW, GtkWidget, GTK_ALIGN_CENTER
#include <stdlib.h>            // for NULL
#include <gobject/gclosure.h>  // for G_CALLBACK
#include <jeff/jeff_gtk.h>     // for activate, print_hello

void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello World!\n");
}

void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window, *button, *box;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  gtk_window_set_child(GTK_WINDOW(window), box);

  button = gtk_button_new_with_label("Message");

  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);

  gtk_box_append(GTK_BOX(box), button);
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  int status = 0;
  GtkApplication *app;
  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
