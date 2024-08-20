#ifndef JEFF_GTK_H
#define JEFF_GTK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <cairo.h>
#include <gtk/gtk.h>

void clear_surface(void);
void draw_cb(GtkDrawingArea *drawing_area, cairo_t *cr, const int width, const int height,
             gpointer data);
void resize_cb(GtkWidget *widget, const int width, const int height, gpointer data);
void draw_brush(GtkWidget *widget, const double x, const double y);
void quit_cb(GtkWindow *window);
void drag_begin(GtkGestureDrag *gesture, const double x, const double y, GtkWidget *area);
void drag_update(GtkGestureDrag *gesture, const double x, const double y, GtkWidget *area);
void drag_end(GtkGestureDrag *gesture, const double x, const double y, GtkWidget *area);
void pressed(GtkGestureClick *gesture, const int n_press, const double x, const double y,
             GtkWidget *area);

void close_window(void);

void activate(GtkApplication *app, gpointer user_data);
void print_hello(GtkWidget *widget, gpointer data);
void print_hello_reversed(GtkWidget *widget, gpointer data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_GTK_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
