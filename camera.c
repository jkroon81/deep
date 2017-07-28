/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <math.h>
#include "SDL_opengl.h"
#include "vector.h"
#include "camera.h"

/* static variables */
static float _position[3] = { 0.0, 0.0, 0.0 };
static float _target[3] = { 0.0, 0.0, 0.0 };
static float _up[3] = { 0.0, 1.0, 0.0 };

/* functions */
void camera_update_matrix(void)
{
  float x[3], y[3], z[3], matrix[4][4];

  vector3f_subtract(z, _position, _target);
  vector3f_normalize(z, z);
  vector3f_cross(x, _up, z);
  vector3f_normalize(x, x);
  vector3f_cross(y, z, x);
  vector4f_set(matrix[0], x[0], y[0], z[0], 0.0);
  vector4f_set(matrix[1], x[1], y[1], z[1], 0.0);
  vector4f_set(matrix[2], x[2], y[2], z[2], 0.0);
  vector4f_set(matrix[3], 0.0, 0.0, 0.0, 1.0);
  glLoadMatrixf((float *) matrix);
  glTranslatef(-_position[0], -_position[1], -_position[2]);
}

void camera_set_position(float x, float y, float z)
{
  vector3f_set(_position, x, y, z);
}

void camera_set_target(float x, float y, float z)
{
  vector3f_set(_target, x, y, z);
}

void camera_set_up(float x, float y, float z)
{
  vector3f_set(_up, x, y, z);
}

void camera_set_lens(float fovy, float aspect, float near, float far)
{
  float left, right, bottom, top, x, y, a, b, c, d, matrix[4][4];

  top = near * tan(fovy * M_PI / 360.0);
  bottom = -top;
  left = bottom * aspect;
  right = top * aspect;
  x = (2.0 * near) / (right - left);
  y = (2.0 * near) / (top - bottom);
  a = (right + left) / (right - left);
  b = (top + bottom) / (top - bottom);
  c = -(far + near) / (far - near);
  d = -(2.0 * far * near) / (far - near);
  vector4f_set(matrix[0], x, 0.0, 0.0, 0.0);
  vector4f_set(matrix[1], 0.0, y, 0.0, 0.0);
  vector4f_set(matrix[2], a, b, c, -1.0);
  vector4f_set(matrix[3], 0.0, 0.0, d, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf((float *) matrix);
  glMatrixMode(GL_MODELVIEW);
}
