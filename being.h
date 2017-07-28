/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#ifndef _BEING_H
#define _BEING_H

/* defines */
#define BEING_MOVE_FORWARD	1
#define BEING_MOVE_BACK		2
#define BEING_MOVE_LEFT		3
#define BEING_MOVE_RIGHT	4
#define BEING_FACE_LEFT		1
#define BEING_FACE_RIGHT	2

/* typedefs */
typedef struct _Being Being;

/* functions */
extern Being *being_create(void);
extern void being_update(Being *, int);
extern void being_set_position(Being *, int, int, int);
extern void being_get_position(Being *, float *, float *, float *);
extern void being_apply_translation(Being *);
extern void being_apply_rotation(Being *);
extern void being_move(Being *, int);
extern void being_face(Being *, int);
extern void being_rotate(Being *, int);

#endif /* _BEING_H */
