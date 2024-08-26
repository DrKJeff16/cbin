#include <GL/gl.h>
#include <GL/glu.h>           // for gluOrtho2D
#include <GL/freeglut_std.h>  // for glutCreateWindow, glutDisplayFunc, glut...
#include <math.h>             // for cos, sin
#include <stdlib.h>           // for free, NULL
#include <jeff/jeff.h>        // for die, PI
#include <jeff/jmemory.h>     // for MALLOC
#include <jeff/jeff_gl.h>     // for gl_init_t, rgb_t, rgba_t, display, init

void init(gl_init_t *args) {
  if (args == NULL) {
    die(127, "Init args are NULL");
  }

  glClearColor(args->rgba->red, args->rgba->green, args->rgba->blue, args->rgba->alpha);

  glColor3f(args->rgb->red, args->rgb->green, args->rgb->blue);

  glPointSize(1.f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(-780, 780, -420, 420);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  float x = 0.f, y = 0.f;
  float i;

  for (i = 0.f; i < (J_TAU_F); i += 0.001f) {
    x = 200.f * cos(i);
    y = 200.f * sin(i);

    glVertex2i(x, y);
  }

  glEnd();
  glFlush();
}

int main(int argc, char **argv) {
  gl_init_t *init_args = MALLOC(gl_init_t);
  init_args->rgba = MALLOC(rgba_t);
  init_args->rgb = MALLOC(rgb_t);

  init_args->rgba->red = 0.f;
  init_args->rgba->green = 0.f;
  init_args->rgba->blue = 0.f;
  init_args->rgba->alpha = 1.f;

  init_args->rgb->red = 0.f;
  init_args->rgb->green = 1.f;
  init_args->rgb->blue = 0.f;

  int *pargc = MALLOC(int);
  *pargc = argc;

  glutInit(pargc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize(1920, 1080);
  glutInitWindowPosition(0, 0);

  glutCreateWindow("Circle Drawing");
  init(init_args);

  glutDisplayFunc(display);
  glutMainLoop();

  free(pargc);
  free(init_args->rgb);
  free(init_args->rgba);
  free(init_args);
  return 0;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
