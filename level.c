/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <stdio.h>
#include <string.h>
#include "SDL_opengl.h"
#include "mesh.h"
#include "being.h"
#include "perlin.h"
#include "list.h"
#include "entity.h"
#include "square.h"
#include "vector.h"
#include "camera.h"
#include "level.h"

/* defines */
#define BUFFER_SIZE	512
#define MAZE_SIZE	128

/* global variables */
int texture[256];

/* static variables */
static Square *_maze[MAZE_SIZE][MAZE_SIZE];
static Being *_viewer = NULL;

/* static functions */
static int _read_map(FILE * file)
{
  int x, y;
  char line[BUFFER_SIZE];

  x = y = 0;
  while (1) {
    if ((fgets(line, BUFFER_SIZE, file) == NULL)
	|| (strlen(line) > MAZE_SIZE))
      return -1;
    if ((line[0] == '\n'))
      break;
    for (x = 0; x < MAZE_SIZE && x < strlen(line) - 2; x++)
      switch (line[x]) {
      case SQUARE_EMPTY:
	_maze[x][y] = square_create_empty();
	break;
      case SQUARE_SOLID:
	_maze[x][y] = square_create_solid();
	break;
      case SQUARE_FAKE_SOLID:
	_maze[x][y] = square_create_fake_solid();
	break;
      case SQUARE_ROTATE_LEFT:
	_maze[x][y] = square_create_rotator(-1);
	break;
      case SQUARE_ROTATE_RIGHT:
	_maze[x][y] = square_create_rotator(1);
	break;
      case SQUARE_ROTATE_BACK:
	_maze[x][y] = square_create_rotator(2);
	break;
      default:
	return -1;
      }
    y++;
  }
  return 0;
}

static int _read_start(char *line)
{
  int x, y, face;

  if (sscanf(line, "START = %d, %d, %d\n", &x, &y, &face) != 3)
    return -1;
  being_set_position(_viewer, x, y, face);
  return 0;
}

static int _read_entity(char *line)
{
  if (strstr(line, "DOOR") != NULL)
    entity_create_door(line);
  else if (strstr(line, "BUTTON") != NULL)
    entity_create_button(line);
  else
    return -1;
  return 0;
}

static void _load_textures(void)
{
  texture[ASPHALT_TEXTURE] = perlin_asphalt();
  texture[STONE_BRICKS_TEXTURE] = perlin_stone_bricks(3, 5);
}

/* functions */
void level_set_viewer(Being * viewer)
{
  _viewer = viewer;
}

int level_load(char *filename, Being * viewer)
{
  char line[BUFFER_SIZE];
  float light_position[4] = { 0.0, 0.0, 0.0, 1.0 };
  FILE *file;

  if ((file = fopen(filename, "r")) == NULL)
    return -1;
  _viewer = viewer;
  _load_textures();
  memset(_maze, 0, sizeof(Square *) * MAZE_SIZE * MAZE_SIZE);
  while (fgets(line, BUFFER_SIZE, file) != NULL) {
    if (line[0] == '#' || line[0] == '\n')
      continue;
    if (strcmp(line, "MAP\n") == 0) {
      if (_read_map(file) < 0)
	return -1;
    } else if (strstr(line, "START") != NULL) {
      if (_read_start(line) < 0)
	return -1;
    } else {
      if (_read_entity(line) < 0)
	return -1;
    }
  }
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  return 0;
}

void level_draw(void)
{
  int x, y;

  camera_set_lens(65.0, 640.0 / 480.0, 1.0, 1000.0);
  camera_set_position(0.0, 0.0, 5.0);
  camera_set_target(0.0, 0.0, -1.0);
  camera_update_matrix();
  glScalef(10.0, 10.0, 10.0);
  being_apply_rotation(_viewer);
  being_apply_translation(_viewer);
  for (x = 1; x < MAZE_SIZE - 2; x++)
    for (y = 1; y < MAZE_SIZE - 2; y++)
      if (_maze[x][y] != NULL)
	square_draw(_maze[x][y], x, y);
}

void *level_get_square(int x, int y)
{
  return _maze[x][y];
}

void level_update(int time)
{
  int x, y;

  for (x = 0; x < MAZE_SIZE; x++)
    for (y = 0; y < MAZE_SIZE; y++)
      if (_maze[x][y] != NULL)
	square_update(_maze[x][y]);
}
