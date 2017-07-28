/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#ifndef _CAMERA_H
#define _CAMERA_H

/* functions */
extern void camera_set_position(float, float, float);
extern void camera_set_target(float, float, float);
extern void camera_set_up(float, float, float);
extern void camera_set_lens(float, float, float, float);
extern void camera_update_matrix(void);

#endif /* _CAMERA_H */
