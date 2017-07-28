/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <stdlib.h>
#include "SDL_timer.h"
#include "timer.h"

/* structs */
struct _Timer {
  int time_stamp;
};

/* functions */
Timer *timer_create(void)
{
  Timer *timer;

  timer = malloc(sizeof(Timer));
  timer->time_stamp = SDL_GetTicks();
  return timer;
}

int timer_reset(Timer * timer)
{
  int elapsed_time, current_time;

  current_time = SDL_GetTicks();
  elapsed_time = current_time - timer->time_stamp;
  timer->time_stamp = current_time;
  return elapsed_time;
}
