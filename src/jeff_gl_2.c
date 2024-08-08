#include <stdbool.h>
#include <jeff/jeff.h>
#include <jeff/jeff_gl.h>

void glfw_init(void) {
  glewExperimental = true;
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
    glewExperimental = true;
  }

  if (glewInit() != GLEW_OK) {
    die(1, "Failed to initialize GLEW.");
  }
}

bool esc_not_pressed(GLFWwindow *window) {
  return (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));
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
