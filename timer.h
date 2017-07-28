/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#ifndef _TIMER_H
#define _TIMER_H

/* typedefs */
typedef struct _Timer Timer;

/* functions */
extern Timer *timer_create(void);
extern int timer_reset(Timer *);

#endif /* _TIMER_H */
