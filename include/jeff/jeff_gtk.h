#ifndef JEFF_GTK_H
#define JEFF_GTK_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <cairo.h>
#include <gtk/gtk.h>

static const char title[16] = "org.gtk.example";

void clear_surface(void);
void draw_cb(GtkDrawingArea *drawing_area, cairo_t *cr, const int width, const int height, gpointer data);
void resize_cb(GtkWidget *widget, const int width, const int height, gpointer data);
void draw_brush(GtkWidget *widget, const double x, const double y);
void quit_cb(GtkWindow *window);
void drag_begin(GtkGestureDrag *gesture, const double x, const double y, GtkWidget *area);
void drag_update(GtkGestureDrag *gesture, const double x, const double y, GtkWidget *area);
void drag_end(GtkGestureDrag *gesture, const double x, const double y, GtkWidget *area);
void pressed(GtkGestureClick *gesture, const int n_press, const double x, const double y, GtkWidget *area);

void close_window(void);

void activate(GtkApplication *app, gpointer user_data);
void print_hello(GtkWidget *widget, gpointer data);
void print_hello_reversed(GtkWidget *widget, gpointer data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_GTK_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
