#ifndef JEFF_H
#define JEFF_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#ifndef PI
#define PI 3.14159
#endif // !PI

#ifndef ALLOC
#define ALLOC(type, n) (type*) malloc(sizeof(type) * n)
#endif // !ALLOC

#ifndef ERR
#define ERR(msg) fprintf(stderr, "%s\n", msg)
#endif // !ERR

bool jxor(const bool, const bool);
void err(const char*);
void die(const bool, const char*);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !JEFF_H
