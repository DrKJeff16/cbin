#ifndef JEFF_GTK_H
#define JEFF_GTK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <cairo.h>

static cairo_surface_t *surface = NULL;
static double start_x, start_y;

static void clear_surface(void);
static void resize_cb(GtkWidget*, const int, const int, gpointer);
static void draw_cb(GtkDrawingArea*, cairo_t*, const int, const int, gpointer);
static void draw_brush(GtkWidget*, const double, const double);
static void quit_cb(GtkWindow*);
static void drag_begin(GtkGestureDrag*, const double, const double, GtkWidget*);
static void drag_update(GtkGestureDrag*, const double, const double, GtkWidget*);
static void drag_end(GtkGestureDrag*, const double, const double, GtkWidget*);
static void pressed(GtkGestureClick*, const int, const double, const double, GtkWidget*);
static void close_window(void);

static void activate(GtkApplication*, gpointer);
static void print_hello(GtkWidget*, gpointer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_GTK_H */
