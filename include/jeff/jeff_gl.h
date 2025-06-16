#if !defined(JEFF_GL_H)
#define JEFF_GL_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include "jtypes.h"

void init(gl_init_t *args);
void display(void);
void glfw_init(void);
void glew_init(GLFWwindow *window);
jbool esc_not_pressed(GLFWwindow *const window);
void window_run(GLFWwindow *window);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JEFF_GL_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
