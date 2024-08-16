#ifndef JEFF_GL_H
#define JEFF_GL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

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
