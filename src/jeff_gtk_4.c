#include <gio/gio.h>           // for g_application_run, G_APPLICATION, G_AP...
#include <glib-object.h>       // for g_object_unref, g_signal_connect, GObject
#include <glib.h>              // for g_print, gpointer, TRUE
#include <gtk/gtk.h>           // for gtk_builder_get_object, GtkApplication
#include <stdlib.h>            // for NULL
#include <gobject/gclosure.h>  // for G_CALLBACK
#include <jeff/jeff_gtk.h>     // for activate, print_hello, print_hello_rev...

void print_hello(GtkWidget *widget, gpointer data) { g_print("Hello World!\n"); }

void print_hello_reversed(GtkWidget *widget, gpointer data) { g_print("!dlroW olleH\n"); }

void quit_cb(GtkWindow *window) { gtk_window_close(window); }

void activate(GtkApplication *app, gpointer user_data) {
  GtkBuilder *builder = gtk_builder_new();
#ifndef _JASSET_DIR
#define _JASSET_DIR "~/.local/share/jassets/builder.ui"
#endif /* !_JASSET_DIR */
  gtk_builder_add_from_file(builder, "assets/builder.ui", NULL);

  GObject *window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  GObject *button;
  button = gtk_builder_get_object(builder, "button1");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  button = gtk_builder_get_object(builder, "button2");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello_reversed), NULL);
  button = gtk_builder_get_object(builder, "quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(quit_cb), window);

  gtk_widget_set_visible(GTK_WIDGET(window), TRUE);

  g_object_unref(builder);
}

int main(int argc, char **argv) {
#ifdef GTK_SRCDIR
  g_chdir(GTK_SRCDIR);
#endif /* GTK_SRCDIR */

  GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
