#include <gio/gio.h>           // for g_application_run, G_APPLICATION, G_AP...
#include <glib-object.h>       // for g_object_unref, g_signal_connect
#include <glib.h>              // for gpointer
#include <gtk/gtk.h>           // for GTK_WINDOW, GtkApplication, gtk_applic...
#include <stdlib.h>            // for NULL
#include <gobject/gclosure.h>  // for G_CALLBACK
#include <jeff/jeff_gtk.h>     // for activate

const char app_id[] = "org.gtk.example";

void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);

  g_object_unref(app);

  return status;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
