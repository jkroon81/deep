/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <math.h>
#include "SDL_opengl.h"
#include "vector.h"
#include "mesh.h"

/* static functions */
static void _sphere_draw_triangle(float *a, float *b, float *c, int subdivs)
{
  float v1[3], v2[3], v3[3];

  if (subdivs > 0) {
    vector3f_add(v1, a, b);
    vector3f_normalize(v1, v1);
    vector3f_add(v2, a, c);
    vector3f_normalize(v2, v2);
    vector3f_add(v3, c, b);
    vector3f_normalize(v3, v3);
    _sphere_draw_triangle(a, v1, v2, subdivs - 1);
    _sphere_draw_triangle(c, v2, v3, subdivs - 1);
    _sphere_draw_triangle(b, v3, v1, subdivs - 1);
    _sphere_draw_triangle(v1, v3, v2, subdivs - 1);
  } else {
    glNormal3fv(a);
    glVertex3fv(a);
    glNormal3fv(b);
    glVertex3fv(b);
    glNormal3fv(c);
    glVertex3fv(c);
  }
}

/* functions */
void mesh_square(int subdivs)
{
  int i, j;

  glNormal3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  for (i = 0; i < subdivs; i++)
    for (j = 0; j < subdivs; j++) {
      glTexCoord2f(j * 1.0 / subdivs, i * 1.0 / subdivs);
      glVertex3f(-0.5 + j * 1.0 / subdivs, -0.5 + i * 1.0 / subdivs, 0.0);
      glTexCoord2f((j + 1) * 1.0 / subdivs, i * 1.0 / subdivs);
      glVertex3f(-0.5 + (j + 1) * 1.0 / subdivs, -0.5 + i * 1.0 / subdivs,
		 0.0);
      glTexCoord2f((j + 1) * 1.0 / subdivs, (i + 1) * 1.0 / subdivs);
      glVertex3f(-0.5 + (j + 1) * 1.0 / subdivs,
		 -0.5 + (i + 1) * 1.0 / subdivs, 0.0);
      glTexCoord2f(j * 1.0 / subdivs, (i + 1) * 1.0 / subdivs);
      glVertex3f(-0.5 + j * 1.0 / subdivs, -0.5 + (i + 1) * 1.0 / subdivs,
		 0.0);
    }
  glEnd();
}

void mesh_box(int subdivs)
{
  int i;

  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.5);
  for (i = 0; i < 4; i++) {
    glTranslatef(0.5, 0.0, -0.5);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    mesh_square(subdivs);
  }
  glTranslatef(0.0, -0.5, -0.5);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  mesh_square(subdivs);
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(180.0, 1.0, 0.0, 0.0);
  mesh_square(subdivs);
  glPopMatrix();
}

void mesh_hemisphere(int subdivs)
{
  float v0[] = { 0.0, 1.0, 0.0 };
  float v1[] = { 0.0, 0.0, 1.0 };
  float v2[] = { -sqrt(3.0) / 2.0, 0.0, -1.0 / 2.0 };
  float v3[] = { sqrt(3.0) / 2.0, 0.0, -1.0 / 2.0 };

  if (subdivs > 7)
    subdivs = 7;
  glBegin(GL_TRIANGLES);
  _sphere_draw_triangle(v0, v2, v1, subdivs);
  _sphere_draw_triangle(v0, v1, v3, subdivs);
  _sphere_draw_triangle(v0, v3, v2, subdivs);
  glEnd();
}

void mesh_cylinder(int segments)
{
  float angle, step;
  float v0[2], v1[2];

  if (segments > 120)
    segments = 120;
  step = 2.0 * M_PI / segments;
  v0[0] = 1.0;
  v0[1] = 0.0;
  glBegin(GL_QUADS);
  for (angle = step; angle <= 2.0 * M_PI + step; angle += step) {
    v1[0] = cos(angle);
    v1[1] = -sin(angle);
    glNormal3f(v0[0], 0.0, v0[1]);
    glVertex3f(v0[0], 1.0, v0[1]);
    glVertex3f(v0[0], -1.0, v0[1]);
    glNormal3f(v1[0], 0.0, v1[1]);
    glVertex3f(v1[0], -1.0, v1[1]);
    glVertex3f(v1[0], 1.0, v1[1]);
    v0[0] = v1[0];
    v0[1] = v1[1];
  }
  glEnd();
}
