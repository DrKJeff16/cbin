#ifndef JEFF_GL_H
#define JEFF_GL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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

void init(gl_init_t*);
void display(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_GL_H */
