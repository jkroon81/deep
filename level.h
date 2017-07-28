/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#ifndef _LEVEL_H
#define _LEVEL_H

/* includes */
#include "being.h"

/* defines */
#define ASPHALT_TEXTURE		0
#define STONE_BRICKS_TEXTURE	1

/* global variables */
extern int texture[256];

/* functions */
int level_load(char *, Being *);
void level_draw(void);
void *level_get_square(int, int);
void level_update(int time);
void level_set_viewer(Being *);

#endif /* _LEVEL_H */
