/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <stdlib.h>
#include <stdio.h>
#include "SDL_opengl.h"
#include "mesh.h"
#include "square.h"
#include "level.h"
#include "entity.h"

/* defines */
#define ENTITY_DOOR	1
#define ENTITY_BUTTON	2

/* structs */
typedef struct {
  int type;
  int placement;
  Square *square;
} Common;

typedef struct {
  Common common;
  int closed;
} DoorEntity;

typedef struct {
  Common common;
} ButtonEntity;

union _Entity {
  Common common;
  DoorEntity door;
  ButtonEntity button;
};

/* statics */
static void _draw_door(DoorEntity * door)
{
  int i;

  glPushMatrix();
  glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
  glBindTexture(GL_TEXTURE_2D, texture[ASPHALT_TEXTURE]);
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(-0.5, 0.0, -0.5);
  glScalef(0.1, 1.0, 0.1);
  mesh_box(1);
  glTranslatef(10.0, 0.0, 0.0);
  mesh_box(1);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.0, 0.45, -0.5);
  glScalef(1.0, 0.1, 0.1);
  mesh_box(1);
  glPopMatrix();
  glPushMatrix();
  glDisable(GL_TEXTURE_2D);
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.5, -0.025, -0.5);
  glScalef(0.025, 0.45, 0.025);
  for (i = 0; i < 4; i++) {
    glTranslatef(8.0, 0.0, 0.0);
    mesh_cylinder(8);
  }
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.0, 0.525, -0.5);
  glRotatef(90.0, 0.0, 0.0, 1.0);
  glScalef(0.025, 0.45, 0.025);
  for (i = 0; i < 5; i++) {
    glTranslatef(-8.0, 0.0, 0.0);
    mesh_cylinder(8);
  }
  glPopAttrib();
  glPopMatrix();
}

static void _draw_button(ButtonEntity * button)
{
  glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
  glDisable(GL_TEXTURE_2D);
  glColor3f(0.0, 0.4, 0.0);
  glTranslatef(0.0, 0.0, -0.5);
  glScalef(0.025, 0.025, 0.015);
  glRotatef(90, 1.0, 0.0, 0.0);
  mesh_hemisphere(2);
  glPopAttrib();
}

/* functions */
void entity_create_door(char *line)
{
  int pos[2], placement;
  Entity *entity;
  Square *square;

  sscanf(line, "DOOR = %d, %d, %d\n", &pos[0], &pos[1], &placement);
  square = level_get_square(pos[0], pos[1]);
  entity = malloc(sizeof(Entity));
  entity->common.type = ENTITY_DOOR;
  entity->common.placement = placement;
  entity->common.square = square;
  entity->door.closed = 1;
  square_place(square, entity);
}

void entity_create_button(char *line)
{
  int pos[2], placement;
  Entity *entity;
  Square *square;

  sscanf(line, "BUTTON = %d, %d, %d\n", &pos[0], &pos[1], &placement);
  square = level_get_square(pos[0], pos[1]);
  entity = malloc(sizeof(Entity));
  entity->common.type = ENTITY_BUTTON;
  entity->common.placement = placement;
  entity->common.square = square;
  square_place(square, entity);
}

void entity_draw(Entity * entity)
{
  glPushMatrix();
  glRotatef(-entity->common.placement * 90.0, 0.0, 1.0, 0.0);
  switch (entity->common.type) {
  case ENTITY_BUTTON:
    _draw_button(&entity->button);
    break;
  case ENTITY_DOOR:
    _draw_door(&entity->door);
    break;
  }
  glPopMatrix();
}

int entity_type(Entity * entity)
{
  return entity->common.type;
}
