#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <sys/types.h>
#include <jeff/jeff.h>
#include <jeff/jeff_gl.h>

void glfw_init(void) {
  glewExperimental = (u_char)1;
  int glfw_s = glfwInit();
  if (!glfw_s) {
    vdie(-1, "`glfwInit()` failed (%d)\n", glfw_s);
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void glew_init(GLFWwindow *window) {
  if (null_ptr(window)) {
    exec_vdie(1, glfwTerminate, "Failed to open GLFW window\n%s\n", " Incompatible with version 3.3. Try 2.1");
  }

  glfwMakeContextCurrent(window);
  if (!glewExperimental) {
    glewExperimental = (u_char)1;
  }

  GLenum init_s = glewInit();
  if (init_s != GLEW_OK) {
    vdie(1, "Failed to initialize GLEW (%d)\n", init_s);
  }
}

jbool esc_not_pressed(GLFWwindow *const window) {
  return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window);
}

void window_run(GLFWwindow *window) {
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  do {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (esc_not_pressed(window));
}

int main(int argc, char **argv) {
  glfw_init();

  GLFWwindow *window = glfwCreateWindow(1920, 1080, "Tutorial 02", NULL, NULL);

  glew_init(window);
  window_run(window);

  exec_vdie(0, glfwTerminate, NULL);
  return 0;
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
