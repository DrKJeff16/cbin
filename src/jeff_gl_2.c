#include <GL/glew.h>       // for glewExperimental, GL_TRUE, glClear, glewInit
#include <GLFW/glfw3.h>    // for glfwWindowHint, GLFWwindow, glfwCreateWindow
#include <stdlib.h>        // for NULL
#include <sys/types.h>     // for u_char, uint
#include <jeff/jeff.h>     // for die
#include <jeff/jeff_gl.h>  // for esc_not_pressed, glew_init, glfw_init, win...

void glfw_init(void) {
  glewExperimental = (u_char)1;
  if (!glfwInit()) {
    die(-1, "`glfwInit()` failed");
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void glew_init(GLFWwindow *window) {
  if (window == NULL) {
    glfwTerminate();
    die(1, "Failed to open GLFW window. Incompatible with version 3.3. Try 2.1");
  }

  glfwMakeContextCurrent(window);
  if (!glewExperimental) {
    glewExperimental = (u_char)1;
  }

  if (glewInit() != GLEW_OK) {
    die(1, "Failed to initialize GLEW.");
  }
}

uint esc_not_pressed(GLFWwindow *window) {
  return (
    uint)((glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)));
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

  return 0;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
