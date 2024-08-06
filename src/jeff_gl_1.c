#include <math.h>
#include <jeff/jeff.h>
#include <jeff/jeff_gl.h>

void init(gl_init_t *args) {
  if (args == NULL) {
    die(1, "Init args are NULL");
  }

  glClearColor(args->rgba->red, args->rgba->green, args->rgba->blue, args->rgba->alpha);

  glColor3f(args->rgb->red, args->rgb->green, args->rgb->blue);

  glPointSize(1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(-780, 780, -420, 420);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  float x, y, i;

  for (i = 0.; i < (2 * PI); i += 0.001) {
    x = 200. * cos(i);
    y = 200. * sin(i);

    glVertex2i(x, y);
  }

  glEnd();
  glFlush();
}

int main(int argc, char **argv) {
  gl_init_t *init_args = ALLOC(gl_init_t, 1);
  init_args->rgba = ALLOC(rgba_t, 1);
  init_args->rgb = ALLOC(rgb_t, 1);

  init_args->rgba->red = 0.0;
  init_args->rgba->green = 0.0;
  init_args->rgba->blue = 0.0;
  init_args->rgba->alpha = 1.0;

  init_args->rgb->red = 0.0;
  init_args->rgb->green = 1.0;
  init_args->rgb->blue = 0.0;

  int *pargc = ALLOC(int, 1);
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
