/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#ifndef _SQUARE_H
#define _SQUARE_H

/* includes */
#include "being.h"
#include "entity.h"

/* defines */
#define SQUARE_EMPTY		' '
#define SQUARE_SOLID		'#'
#define SQUARE_ROTATE_LEFT	'L'
#define SQUARE_ROTATE_RIGHT	'R'
#define SQUARE_ROTATE_BACK	'B'
#define SQUARE_ROTATOR		'0'
#define SQUARE_FAKE_SOLID	'*'

/* typedefs */
typedef union _Square Square;

/* functions */
Square *square_create_solid(void);
Square *square_create_fake_solid(void);
Square *square_create_empty(void);
Square *square_create_rotator(int);
void square_update(Square *);
void square_enter(Square *, Being *);
void square_leave(Square *, Being *);
void square_place(Square *, Entity *);
void square_remove(Square *, Entity *);
char square_type(Square *);
void square_draw(Square *, int, int);

#endif /* _SQUARE_H */
