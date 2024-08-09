#ifndef JEFF_GTK_H
#define JEFF_GTK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <cairo.h>

void clear_surface(void);
void resize_cb(GtkWidget*, const int, const int, gpointer);
void draw_cb(GtkDrawingArea*, cairo_t*, const int, const int, gpointer);
void draw_brush(GtkWidget*, const double, const double);
void quit_cb(GtkWindow*);
void drag_begin(GtkGestureDrag*, const double, const double, GtkWidget*);
void drag_update(GtkGestureDrag*, const double, const double, GtkWidget*);
void drag_end(GtkGestureDrag*, const double, const double, GtkWidget*);
void pressed(GtkGestureClick*, const int, const double, const double, GtkWidget*);

void close_window(void);

void activate(GtkApplication *app, gpointer user_data);
void print_hello(GtkWidget*, gpointer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_GTK_H */
