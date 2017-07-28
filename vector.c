/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <math.h>
#include "vector.h"

/* defines */
#define SQR(A)			((A)*(A))

/* functions */
void vector3f_copy(float *a, float *b)
{
  a[0] = b[0];
  a[1] = b[1];
  a[2] = b[2];
}

void vector2f_copy(float *a, float *b)
{
  a[0] = b[0];
  a[1] = b[1];
}

void vector2i_set(int *r, int x, int y)
{
  r[0] = x;
  r[1] = y;
}

void vector2f_set(float *r, float x, float y)
{
  r[0] = x;
  r[1] = y;
}

void vector2i_add(int *r, int *a, int *b)
{
  r[0] = a[0] + b[0];
  r[1] = a[1] + b[1];
}

void vector2i_copy(int *a, int *b)
{
  a[0] = b[0];
  a[1] = b[1];
}

void vector3f_normalize(float *r, float *e)
{
  float length;

  length = sqrt(SQR(e[0]) + SQR(e[1]) + SQR(e[2]));
  r[0] = e[0] / length;
  r[1] = e[1] / length;
  r[2] = e[2] / length;
}

float vector3f_dot(float *a, float *b)
{
  return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

float vector2f_dot(float *a, float *b)
{
  return (a[0] * b[0] + a[1] * b[1]);
}

void vector2f_scale(float *r, float scale, float *a)
{
  r[0] = scale * a[0];
  r[1] = scale * a[1];
}

void vector3f_scale(float *r, float scale, float *a)
{
  r[0] = scale * a[0];
  r[1] = scale * a[1];
  r[2] = scale * a[2];
}

void vector3f_add(float *r, float *a, float *b)
{
  r[0] = a[0] + b[0];
  r[1] = a[1] + b[1];
  r[2] = a[2] + b[2];
}

void vector3f_subtract(float *r, float *a, float *b)
{
  r[0] = a[0] - b[0];
  r[1] = a[1] - b[1];
  r[2] = a[2] - b[2];
}

void vector3f_cross(float *r, float *a, float *b)
{
  r[0] = a[1] * b[2] - a[2] * b[1];
  r[1] = a[2] * b[0] - a[0] * b[2];
  r[2] = a[0] * b[1] - a[1] * b[0];
}

void vector3f_set(float *r, float x, float y, float z)
{
  r[0] = x;
  r[1] = y;
  r[2] = z;
}

void vector4f_set(float *r, float x, float y, float z, float v)
{
  r[0] = x;
  r[1] = y;
  r[2] = z;
  r[3] = v;
}

void vector2f_swap(float *a, float *b)
{
  float temp[2];

  vector2f_copy(temp, a);
  vector2f_copy(a, b);
  vector2f_copy(b, temp);
}
