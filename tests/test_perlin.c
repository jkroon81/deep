/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include "SDL.h"
#include "SDL_opengl.h"
#include "video.h"
#include "camera.h"
#include "mesh.h"
#include "perlin.h"

/* functions */
int main(void)
{
  int loop = 1;
  SDL_Event event;
  int asphalt, stone_bricks;

  SDL_Init(SDL_INIT_VIDEO);
  video_init(640, 480, "test_perlin");
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2, 2, -2, 2, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  camera_set_position(0.0, 0.0, -9.0);
  camera_update_matrix();
  asphalt = perlin_asphalt();
  stone_bricks = perlin_stone_bricks(4, 4);
  glClearColor(1.0, 0.0, 0.0, 0.0);
  while (loop) {
    glPushMatrix();
    glTranslatef(1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, asphalt);
    mesh_square(4);
    glTranslatef(-1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, stone_bricks);
    mesh_square(4);
    glPopMatrix();
    SDL_GL_SwapBuffers();
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_ESCAPE)
	  loop = 0;
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
