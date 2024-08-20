#ifndef JEFF_GL_H
#define JEFF_GL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <sys/types.h>

typedef struct _gl_rgba {
  double red;
  double green;
  double blue;
  double alpha;
} rgba_t;

typedef struct _gl_rgb {
  double red;
  double green;
  double blue;
} rgb_t;

typedef struct _gl_init {
  rgba_t *rgba;
  rgb_t *rgb;
} gl_init_t;

void init(gl_init_t *args);
void display(void);
void glfw_init(void);
void glew_init(GLFWwindow *window);
uint esc_not_pressed(GLFWwindow *window);
void window_run(GLFWwindow *window);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_GL_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
