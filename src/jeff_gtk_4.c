#include <gio/gio.h>
#include <glib-object.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <gobject/gclosure.h>
#include <string.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>
#include <jeff/jeff_gtk.h>

extern const char title[16];

void print_hello(GtkWidget *widget, gpointer data) {
  g_print("%s\n", "Hello World!");
}

void print_hello_reversed(GtkWidget *widget, gpointer data) {
  char *str = CALLOC(char, 14);
  stpcpy(str, "Hello, World!");

  g_print("%s\n", str_reversed(str));
  free(str);
}

void quit_cb(GtkWindow *window) {
  gtk_window_close(window);
}

void activate(GtkApplication *app, gpointer user_data) {
  GtkBuilder *builder = gtk_builder_new();
#define _JASSET_DIR "/home/drjeff16/.local/share/jassets/builder.ui"
  gtk_builder_add_from_file(builder, _JASSET_DIR, NULL);

  GObject *window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  GObject *button = NULL;
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

  int status = 0;
  GtkApplication *app = gtk_application_new(title, G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
