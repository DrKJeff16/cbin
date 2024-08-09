#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <jeff/jeff.h>
#include <jeff/jeff_gtk.h>

void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello World!\n");
}

void quit_cb(GtkWindow *window) {
  gtk_window_close(window);
}

void activate(GtkApplication *app, gpointer user_data) {
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "builder.ui", NULL);

  GObject *window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  GObject *button;
  button = gtk_builder_get_object(builder, "button1");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  button = gtk_builder_get_object(builder, "button2");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  button = gtk_builder_get_object(builder, "quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(quit_cb), window);

  gtk_widget_set_visible(GTK_WIDGET(window), TRUE);

  g_object_unref(builder);
}

int main(int argc, char **argv) {
#ifdef GTK_SRCDR
  g_chdir(GTK_SRCDIR)
#endif

  GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
