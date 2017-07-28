/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "video.h"
#include "camera.h"
#include "level.h"
#include "being.h"
#include "gui.h"
#include "timer.h"

int main(void)
{
  int loop = 1, elapsed_time = 0, frames = 0, time_stamp = 0, time_now = 0;
  float constant = 0.0, linear = 0.05, quadratic = 0.0008;
  SDL_Event event;
  Being *player;
  Timer *timer;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_GrabInput(SDL_GRAB_ON);
  video_init(640, 480, "test level");
  player = being_create();
  if (level_load("dummy.lvl", player) < 0)
    exit(1);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constant);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linear);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadratic);
  timer = timer_create();
  timer_reset(timer);
  while (loop) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	case SDLK_w:
	  being_move(player, BEING_MOVE_FORWARD);
	  break;
	case SDLK_s:
	  being_move(player, BEING_MOVE_BACK);
	  break;
	case SDLK_a:
	  being_move(player, BEING_MOVE_LEFT);
	  break;
	case SDLK_d:
	  being_move(player, BEING_MOVE_RIGHT);
	  break;
	case SDLK_q:
	  being_face(player, BEING_FACE_LEFT);
	  break;
	case SDLK_e:
	  being_face(player, BEING_FACE_RIGHT);
	  break;
	case SDLK_ESCAPE:
	  loop = 0;
	  break;
	case SDLK_F1:
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	  glDisable(GL_LIGHTING);
	  glDisable(GL_TEXTURE_2D);
	  break;
	case SDLK_F2:
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	  glEnable(GL_LIGHTING);
	  glEnable(GL_TEXTURE_2D);
	  break;
	default:
	  break;
	}
	break;
      case SDL_QUIT:
	loop = 0;
	break;
      }
    }
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    being_update(player, elapsed_time);
    level_update(elapsed_time);
    elapsed_time = timer_reset(timer);
    gui_draw();
    SDL_GL_SwapBuffers();
    if (frames++ == 50) {
      time_now = SDL_GetTicks();
      fprintf(stderr, "\rFPS : %.1f", 50000.0 / (time_now - time_stamp));
      time_stamp = time_now;
      frames = 0;
    }
  }
  fprintf(stderr, "\n");
  SDL_Quit();
  return 0;
}
