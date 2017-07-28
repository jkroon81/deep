/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <stdlib.h>
#include "SDL_opengl.h"
#include "mesh.h"
#include "list.h"
#include "perlin.h"
#include "level.h"
#include "square.h"

/* structs 'n unions */
typedef struct {
  int type;
  List *entities;
  List *beings;
} Common;

typedef struct {
  Common common;
  int rotate;
  int degree;
} RotatorSquare;

typedef struct {
  Common common;
} EmptySquare;

typedef EmptySquare FakeSquare;
typedef EmptySquare SolidSquare;

union _Square {
  Common common;
  SolidSquare solid;
  EmptySquare empty;
  RotatorSquare rotator;
  FakeSquare fake;
};

/* statics */
static void _draw_wall(void)
{
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture[STONE_BRICKS_TEXTURE]);
  glTranslatef(0.0, 0.0, -0.5);
  mesh_square(3);
  glPopMatrix();
}

static void _draw_ceiling(void)
{
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture[ASPHALT_TEXTURE]);
  glTranslatef(0.0, 0.5, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  mesh_square(3);
  glPopMatrix();
}

static void _draw_floor(void)
{
  glPushAttrib(GL_CURRENT_BIT);
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture[ASPHALT_TEXTURE]);
  glColor3f(0.6, 0.6, 0.6);
  glTranslatef(0.0, -0.5, 0.0);
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  mesh_square(3);
  glPopMatrix();
  glPopAttrib();
}

/* functions */
Square *square_create_solid(void)
{
  Square *square;

  square = malloc(sizeof(Square));
  square->common.type = SQUARE_SOLID;
  return square;
}

Square *square_create_empty(void)
{
  Square *square;

  square = square_create_solid();
  square->common.type = SQUARE_EMPTY;
  square->common.entities = list_create();
  return square;
}

Square *square_create_fake_solid(void)
{
  Square *square;

  square = square_create_solid();
  square->common.type = SQUARE_FAKE_SOLID;
  square->common.entities = list_create();
  return square;
}

Square *square_create_rotator(int degree)
{
  Square *square;

  square = square_create_solid();
  square->common.type = SQUARE_ROTATOR;
  square->common.beings = list_create();
  square->common.entities = list_create();
  square->rotator.rotate = 1;
  square->rotator.degree = degree;
  return square;
}

char square_type(Square * square)
{
  if (square != NULL)
    return square->common.type;
  else
    return SQUARE_SOLID;
}

void square_update(Square * square)
{
  Being *b;

  switch (square->common.type) {
  case SQUARE_ROTATOR:
    if (list_size(square->common.beings) != 0 && square->rotator.rotate) {
      square->rotator.rotate = 0;
      list_reset(square->common.beings);
      while ((b = list_get(square->common.beings))) {
	being_rotate(b, square->rotator.degree);
	list_next(square->common.beings);
      }
    } else if (list_size(square->common.beings) == 0)
      square->rotator.rotate = 1;
    break;
  }
}

void square_enter(Square * square, Being * being)
{
  switch (square->common.type) {
  case SQUARE_ROTATOR:
    list_insert_last(square->common.beings, being);
    break;
  }
}

void square_leave(Square * square, Being * being)
{
  switch (square->common.type) {
  case SQUARE_ROTATOR:
    list_remove(square->common.beings, being);
    break;
  }
}

void square_place(Square * square, Entity * entity)
{
  switch (square->common.type) {
  case SQUARE_EMPTY:
  case SQUARE_ROTATOR:
  case SQUARE_FAKE_SOLID:
    list_insert_last(square->common.entities, entity);
    break;
  }
}

void square_remove(Square * square, Entity * entity)
{
  switch (square->common.type) {
  case SQUARE_EMPTY:
  case SQUARE_ROTATOR:
  case SQUARE_FAKE_SOLID:
    list_remove(square->common.entities, entity);
    break;
  }
}

void square_draw(Square * square, int x, int y)
{
  int i;
  Entity *entity;
  char face[4];

  glPushMatrix();
  glTranslatef(x, 0, y);
  face[0] = square_type(level_get_square(x, y + 1));
  face[1] = square_type(level_get_square(x + 1, y));
  face[2] = square_type(level_get_square(x, y - 1));
  face[3] = square_type(level_get_square(x - 1, y));
  switch (square->common.type) {
  case SQUARE_SOLID:
    break;
  case SQUARE_EMPTY:
  case SQUARE_ROTATOR:
  case SQUARE_FAKE_SOLID:
    _draw_floor();
    _draw_ceiling();
    glRotatef(180.0, 0.0, 1.0, 0.0);
    for (i = 0; i < 4; i++) {
      if (face[i] == SQUARE_SOLID || face[i] == SQUARE_FAKE_SOLID)
	_draw_wall();
      glRotatef(90.0, 0.0, 1.0, 0.0);
    }
    glRotatef(180.0, 0.0, 1.0, 0.0);
    break;
  }
  switch (square->common.type) {
  case SQUARE_EMPTY:
  case SQUARE_ROTATOR:
  case SQUARE_FAKE_SOLID:
    list_reset(square->common.entities);
    while ((entity = list_get(square->common.entities)) != NULL) {
      entity_draw(entity);
      list_next(square->common.entities);
    }
    break;
  }
  glPopMatrix();
}
