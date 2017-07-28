/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include "SDL.h"
#include "SDL_opengl.h"
#include "video.h"
#include "camera.h"
#include "mesh.h"

/* functions */
static void _transform(float x, float y, float z, float x_rot, float y_rot)
{
  glTranslatef(x, y, z);
  glRotatef(y_rot, 1.0, 0.0, 0.0);
  glRotatef(x_rot, 0.0, 1.0, 0.0);
}

int main(int argc, char **argv)
{
  float x_rot = 0, y_rot = 0;
  Uint8 loop = 1;
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);
  video_init(640, 480, "test_shapes");
  SDL_WM_GrabInput(SDL_GRAB_ON);
  glEnable(GL_LIGHT0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -8, 8, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  camera_set_position(0.0, 0.0, 9.0);
  camera_update_matrix();
  glColor3f(1.0, 0.0, 0.0);
  while (loop) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    _transform(-8.0, 6.0, 0.0, x_rot, y_rot);
    mesh_box(4);
    glPopMatrix();
    glPushMatrix();
    _transform(-5.0, 6.0, 0.0, x_rot, y_rot);
    mesh_hemisphere(3);
    glPopMatrix();
    glPushMatrix();
    _transform(-2.0, 6.0, 0.0, x_rot, y_rot);
    mesh_cylinder(30);
    glPopMatrix();
    glPushMatrix();
    _transform(1.0, 6.0, 0.0, x_rot, y_rot);
    mesh_square(4);
    glPopMatrix();
    SDL_GL_SwapBuffers();
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_MOUSEMOTION:
	x_rot += event.motion.xrel;
	y_rot += event.motion.yrel;
	break;
      case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_ESCAPE)
	  loop = 0;
	else if (event.key.keysym.sym == SDLK_F1)
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (event.key.keysym.sym == SDLK_F2)
	  glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	else if (event.key.keysym.sym == SDLK_F3)
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	break;
      case SDL_QUIT:
	loop = 0;
	break;
      }
    }
  }
  SDL_Quit();
  return 0;
}
