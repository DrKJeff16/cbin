#include <gtk/gtk.h>
#include <cairo.h>
#include <jeff/jmemory.h>
#include <jeff/jeff_gtk.h>

static cairo_surface_t *surface = NULL;
static double start_x = 0., start_y = 0.;

void clear_surface(void) {
  cairo_t *cr = cairo_create(surface);

  cairo_set_source_rgba(cr, 1, 1, 1, 0.8666f);
  cairo_paint(cr);

  cairo_destroy(cr);
}

void resize_cb(GtkWidget *widget, const int width, const int height, gpointer data) {
  if (surface) {
    cairo_surface_destroy(surface);
    surface = NULL;
  }

  GdkSurface **single_surface = MALLOC(GdkSurface*);

  *single_surface = gtk_native_get_surface(gtk_widget_get_native(widget));

  if (*single_surface) {
    surface = gdk_surface_create_similar_surface(*single_surface, CAIRO_CONTENT_COLOR_ALPHA, gtk_widget_get_width(widget), gtk_widget_get_height(widget));

    clear_surface();
  }

  free(single_surface);
}

void draw_cb(GtkDrawingArea *drawing_area, cairo_t *cr, const int width, const int height, gpointer data) {
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);
}

void draw_brush(GtkWidget *widget, const double x, const double y) {
  cairo_t *cr = cairo_create(surface);

  cairo_rectangle(cr, x - 3., y - 3., 6., 6.);
  cairo_fill(cr);

  cairo_destroy(cr);

  gtk_widget_queue_draw(widget);
}

static double start_x, start_y;

void drag_begin(GtkGestureDrag *gesture, const double x, const double y, GtkWidget *area) {
  start_x = x;
  start_y = y;

  draw_brush(area, x, y);
}

void drag_update(GtkGestureDrag *gesture, const double x, const double y, GtkWidget *area) {
  draw_brush(area, start_x + x, start_y + y);
}

void drag_end(GtkGestureDrag *gesture, const double x, const double y, GtkWidget *area) {
  draw_brush(area, start_x + x, start_y + y);
}

void pressed(GtkGestureClick *gesture, const int n_press, const double x, const double y, GtkWidget *area) {
  clear_surface();
  gtk_widget_queue_draw(area);
}

void close_window(void) {
  if (surface) {
    cairo_surface_destroy(surface);
  }
}

void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window, *frame, *drawing_area;
  GtkGesture *drag, *press;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Drawing Area");

  g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

  frame = gtk_frame_new(NULL);
  gtk_window_set_child(GTK_WINDOW(window), frame);

  drawing_area = gtk_drawing_area_new();
  /* set a minimum size */
  gtk_widget_set_size_request(drawing_area, 100, 100);

  gtk_frame_set_child(GTK_FRAME(frame), drawing_area);

  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_cb, NULL, NULL);

  g_signal_connect_after(drawing_area, "resize", G_CALLBACK(resize_cb), NULL);

  drag = gtk_gesture_drag_new();
  gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(drag), GDK_BUTTON_PRIMARY);
  gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER(drag));
  g_signal_connect(drag, "drag-begin", G_CALLBACK(drag_begin), drawing_area);
  g_signal_connect(drag, "drag-update", G_CALLBACK(drag_update), drawing_area);
  g_signal_connect(drag, "drag-end", G_CALLBACK(drag_end), drawing_area);

  press = gtk_gesture_click_new();
  gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(press), GDK_BUTTON_SECONDARY);
  gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER(press));

  g_signal_connect(press, "pressed", G_CALLBACK(pressed), drawing_area);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
