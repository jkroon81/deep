/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <stdlib.h>
#include "SDL_opengl.h"
#include "perlin.h"

/* defines */
#define ABS(A)	((A) > 0 ? (A) : -(A))
#define SIZE	256

/* static variables */
static float _map[SIZE][SIZE][3];

/* static functions */
static float _noise(void)
{
  return (float) rand() / RAND_MAX;
}

static int _download_map(void)
{
  int id, x, y;
  unsigned char map[SIZE][SIZE][3];

  for (x = 0; x < SIZE; x++)
    for (y = 0; y < SIZE; y++) {
      map[y][x][0] = (unsigned char) (_map[y][x][0] * 255.0);
      map[y][x][1] = (unsigned char) (_map[y][x][1] * 255.0);
      map[y][x][2] = (unsigned char) (_map[y][x][2] * 255.0);
    }
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SIZE, SIZE, 0, GL_RGB,
	       GL_UNSIGNED_BYTE, map);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  return id;
}

static void _set_color(int x, int y, float r, float g, float b)
{
  _map[y][x][0] = r;
  _map[y][x][1] = g;
  _map[y][x][2] = b;
}

static void _multiply_color(int x, int y, float r, float g, float b)
{
  _map[y][x][0] *= r;
  _map[y][x][1] *= g;
  _map[y][x][2] *= b;
}

static void _fill(float r, float b, float g)
{
  int x, y;

  for (x = 0; x < SIZE; x++)
    for (y = 0; y < SIZE; y++)
      _set_color(x, y, r, g, b);
}

static void swap(int *a, int *b)
{
  int temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

static void _draw_h_line(int x1, int x2, int y, float r, float g, float b)
{
  int x;

  if (y < 0 || y >= SIZE)
    return;
  if (x1 > x2)
    swap(&x1, &x2);
  if (x1 < 0)
    x1 = 0;
  if (x2 >= SIZE)
    x2 = SIZE - 1;
  for (x = x1; x < x2; x++)
    _multiply_color(x, y, r, g, b);
}

static void _draw_v_line(int x, int y1, int y2, float r, float g, float b)
{
  int y;

  if (x < 0 || x >= SIZE)
    return;
  if (y1 > y2)
    swap(&y1, &y2);
  if (y1 < 0)
    y1 = 0;
  if (y2 >= SIZE)
    y2 = SIZE - 1;
  for (y = y1; y < y2; y++)
    _multiply_color(x, y, r, g, b);
}

static void _smooth_h_line(int x1, int x2, int y, int size, float r, float g,
			   float b)
{
  int dy;
  float dr, dg, db;

  dr = (1.0 - r) / size * 2.0;
  dg = (1.0 - g) / size * 2.0;
  db = (1.0 - b) / size * 2.0;
  for (dy = -size / 2; dy < size / 2; dy++)
    _draw_h_line(x1, x2, y + dy, r + dr * ABS(dy), g + dg * ABS(dy),
		 b + dr * ABS(dy));
}

static void _smooth_v_line(int x, int y1, int y2, int size, float r, float g,
			   float b)
{
  int dx;
  float dr, dg, db;

  dr = (1.0 - r) / size * 2.0;
  dg = (1.0 - g) / size * 2.0;
  db = (1.0 - b) / size * 2.0;
  for (dx = -size / 2; dx < size / 2; dx++)
    _draw_v_line(x + dx, y1, y2, r + dr * ABS(dx), g + dg * ABS(dx),
		 b + dr * ABS(dx));
}

static void _add_noise(void)
{
  int x, y;
  float value;

  for (x = 0; x < SIZE; x++)
    for (y = 0; y < SIZE; y++) {
      value = (0.5 + _noise() * 0.5);
      _multiply_color(x, y, value, value, value);
    }
}

/* functions */
int perlin_asphalt(void)
{
  _fill(1.0, 1.0, 1.0);
  _add_noise();
  return _download_map();
}

int perlin_stone_bricks(int bricks_x, int bricks_y)
{
  int x, y, x_spacing, y_spacing;

  _fill(1.0, 1.0, 1.0);
  y_spacing = (int) ((float) SIZE / bricks_y);
  x_spacing = (int) ((float) SIZE / bricks_x);
  for (y = 0; y <= SIZE - y_spacing; y += y_spacing) {
    if (y != 0)
      _smooth_h_line(0, SIZE, y, 6, 0.3, 0.3, 0.3);
    for (x = ((y / y_spacing) % 2) * x_spacing / 2; x <= SIZE; x += x_spacing)
      _smooth_v_line(x, y, y + y_spacing, 6, 0.3, 0.3, 0.3);
  }
  _add_noise();
  return _download_map();
}
