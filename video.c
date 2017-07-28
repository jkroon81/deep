/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include "SDL_video.h"
#include "SDL_opengl.h"
#include "SDL_mouse.h"
#include "video.h"

/* statics */
int _width = 0;
int _height = 0;

/* functions */
int video_init(int width, int height, char *title)
{
  int flags, bpp;
  const SDL_VideoInfo *info;

  info = SDL_GetVideoInfo();
  bpp = info->vfmt->BitsPerPixel;
  flags = SDL_OPENGL;
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  if (SDL_SetVideoMode(width, height, bpp, flags) == 0)
    return -1;
  _width = width;
  _height = height;
  SDL_WM_SetCaption(title, title);
  SDL_ShowCursor(0);
  SDL_WarpMouse(0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glCullFace(GL_BACK);
  glShadeModel(GL_SMOOTH);
  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_RESCALE_NORMAL);
  glEnable(GL_COLOR_MATERIAL);
  return 0;
}

void video_get_size(int *width, int *height)
{
  *width = _width;
  *height = _height;
}
