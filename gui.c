/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include "SDL_opengl.h"
#include "level.h"
#include "video.h"
#include "gui.h"

/* defines */
#define BORDER_SIZE	0.02

/* static functions */
static void _enter_2d_mode(void)
{
  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_RESCALE_NORMAL);
  glDisable(GL_COLOR_MATERIAL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void _enter_3d_mode(void)
{
  glPopAttrib();
}

static void _draw_border_shader(void)
{
  glPushAttrib(GL_CURRENT_BIT);
  glBegin(GL_QUADS);
  glColor4f(0.0, 0.0, 0.0, 1.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.0, 0.8);
  glColor4f(0.0, 0.0, 0.0, 0.0);
  glVertex2f(BORDER_SIZE, 0.8);
  glVertex2f(BORDER_SIZE, 0.0);
  glVertex2f(0.0, BORDER_SIZE);
  glVertex2f(0.8, BORDER_SIZE);
  glColor4f(0.0, 0.0, 0.0, 1.0);
  glVertex2f(0.8, 0.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.8, 0.8);
  glVertex2f(0.8, 0.0);
  glColor4f(0.0, 0.0, 0.0, 0.0);
  glVertex2f(0.8 - BORDER_SIZE, 0.0);
  glVertex2f(0.8 - BORDER_SIZE, 0.8);
  glVertex2f(0.0, 0.8 - BORDER_SIZE);
  glVertex2f(0.8, 0.8 - BORDER_SIZE);
  glColor4f(0.0, 0.0, 0.0, 1.0);
  glVertex2f(0.8, 0.8);
  glVertex2f(0.0, 0.8);
  glEnd();
  glPopAttrib();
}

/* functions */
void gui_draw(void)
{
  int width, height;

  video_get_size(&width, &height);
  glViewport(0, 0, 0.8 * width, 0.8 * height);
  level_draw();
  glViewport(0, 0, width, height);
  _enter_2d_mode();
  _draw_border_shader();
  _enter_3d_mode();
}
