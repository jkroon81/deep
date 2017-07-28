/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SDL_opengl.h"
#include "vector.h"
#include "level.h"
#include "list.h"
#include "square.h"
#include "being.h"

/* defines */
#define ACTION_MOVE	1
#define ACTION_FACE	2
#define ACTION_HIT_WALL	3

/* structs */
typedef struct {
  int type;
  int direction;
} Action;

struct _Being {
  int position[2];
  float rotation[3];
  float translation[3];
  List *action_list;
  struct {
    int t_reset;
    int t_move[2];
    int t_next[2];
    float t_angle;
    int r_reset;
    int r_direction;
    int r_start_angle;
    float r_angle;
    float speed;
  } vars;
};

/* static functions */
static void _update_translation(Being * b, int time, Action * action)
{
  float alpha;
  Action reaction;

  if (b->vars.t_reset) {
    b->vars.t_reset = 0;
    b->vars.t_angle = 0.0;
    switch (action->direction) {
    case BEING_MOVE_FORWARD:
      b->vars.t_move[0] =
	sin(rint(b->rotation[1]) / 4.0 * 360.0 * M_PI / 180.0);
      b->vars.t_move[1] =
	-cos(rint(b->rotation[1]) / 4.0 * 360.0 * M_PI / 180.0);
      break;
    case BEING_MOVE_BACK:
      b->vars.t_move[0] =
	-sin(rint(b->rotation[1]) / 4.0 * 360.0 * M_PI / 180.0);
      b->vars.t_move[1] =
	cos(rint(b->rotation[1]) / 4.0 * 360.0 * M_PI / 180.0);
      break;
    case BEING_MOVE_LEFT:
      b->vars.t_move[0] =
	-cos(rint(b->rotation[1]) / 4.0 * 360.0 * M_PI / 180.0);
      b->vars.t_move[1] =
	-sin(rint(b->rotation[1]) / 4.0 * 360.0 * M_PI / 180.0);
      break;
    case BEING_MOVE_RIGHT:
      b->vars.t_move[0] =
	cos(rint(b->rotation[1]) / 4.0 * 360.0 * M_PI / 180.0);
      b->vars.t_move[1] =
	sin(rint(b->rotation[1]) / 4.0 * 360.0 * M_PI / 180.0);
      break;
    }
    vector2i_add(b->vars.t_next, b->position, b->vars.t_move);
    if (square_type(level_get_square(b->vars.t_next[0], b->vars.t_next[1])) ==
	SQUARE_SOLID) {
      b->vars.t_reset = 1;
      reaction.type = ACTION_HIT_WALL;
      reaction.direction = action->direction;
      list_insert_copy_last(b->action_list, &reaction, sizeof(reaction));
      list_remove_first(b->action_list);
    }
  }
  b->vars.t_angle += 0.007 * time * b->vars.speed;
  if (b->vars.t_angle >= M_PI) {
    b->vars.t_reset = 1;
    b->vars.t_angle = 0.0;
    square_leave(level_get_square(b->position[0], b->position[1]), b);
    vector2i_add(b->position, b->position, b->vars.t_move);
    square_enter(level_get_square(b->position[0], b->position[1]), b);
    vector3f_set(b->translation, -b->position[0], 0.0, -b->position[1]);
    list_remove_first(b->action_list);
  } else {
    alpha = (1.0 - cos(b->vars.t_angle)) / 2.0;
    vector3f_set(b->translation, -b->position[0] - alpha * b->vars.t_move[0],
		 0.0, -b->position[1] - alpha * b->vars.t_move[1]);
  }
}

static void _update_rotation(Being * b, int time, Action * action)
{
  float alpha = 0.0;

  if (b->vars.r_reset) {
    b->vars.r_reset = 0;
    b->vars.r_angle = 0.0;
    b->vars.r_start_angle = (int) b->rotation[1];
    switch (action->direction) {
    case BEING_FACE_LEFT:
      b->vars.r_direction = -1.0;
      break;
    case BEING_FACE_RIGHT:
      b->vars.r_direction = 1.0;
      break;
    }
  }
  b->vars.r_angle += 0.007 * time * b->vars.speed;
  if (b->vars.r_angle > M_PI) {
    b->vars.r_reset = 1;
    b->rotation[1] = b->vars.r_start_angle + b->vars.r_direction;
    list_remove_first(b->action_list);
  } else {
    alpha = (1.0 - cos(b->vars.r_angle)) / 2.0;
    b->rotation[1] = b->vars.r_start_angle + b->vars.r_direction * alpha;
  }
}

/* functions */
Being *being_create(void)
{
  Being *b;

  b = malloc(sizeof(Being));
  memset(b, 0, sizeof(Being));
  b->vars.t_reset = 1;
  b->vars.r_reset = 1;
  b->vars.speed = 1.0;
  b->action_list = list_create();
  return b;
}

void being_set_position(Being * b, int x, int y, int face)
{
  vector2i_set(b->position, x, y);
  square_enter(level_get_square(b->position[0], b->position[1]), b);
  vector3f_set(b->translation, -b->position[0], 0.0, -b->position[1]);
  b->rotation[1] = face;
}

void being_get_position(Being * b, float *x, float *y, float *face)
{
  *x = -b->translation[0];
  *y = -b->translation[2];
  *face = b->rotation[1] / 4.0 * 360.0;
}

void being_update(Being * b, int time)
{
  Action *action;

  action = list_get_first(b->action_list);
  if (action != NULL)
    switch (action->type) {
    case ACTION_MOVE:
      _update_translation(b, time, action);
      break;
    case ACTION_FACE:
      _update_rotation(b, time, action);
      break;
    case ACTION_HIT_WALL:
      list_remove_first(b->action_list);
      break;
    }
}

void being_apply_rotation(Being * b)
{
  glRotatef(b->rotation[1] / 4.0 * 360.0, 0.0, 1.0, 0.0);
  glRotatef(b->rotation[0] / 4.0 * 360.0, 1.0, 0.0, 0.0);
  glRotatef(b->rotation[2] / 4.0 * 360.0, 0.0, 0.0, 1.0);
}

void being_apply_translation(Being * b)
{
  glTranslatef(b->translation[0], b->translation[1], b->translation[2]);
}

void being_move(Being * b, int direction)
{
  Action action;
  action.type = ACTION_MOVE;
  action.direction = direction;
  list_insert_copy_last(b->action_list, &action, sizeof(action));
}

void being_face(Being * b, int direction)
{
  Action action;
  action.type = ACTION_FACE;
  action.direction = direction;
  list_insert_copy_last(b->action_list, &action, sizeof(action));
}

void being_rotate(Being * b, int degree)
{
  b->rotation[1] += degree;
}
