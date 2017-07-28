/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#ifndef _VECTOR_H
#define _VECTOR_H

/* functions */
extern void vector3f_normalize(float *, float *);
extern float vector3f_dot(float *, float *);
extern float vector2f_dot(float *, float *);
extern void vector2f_scale(float *, float, float *);
extern void vector3f_scale(float *, float, float *);
extern void vector3f_cross(float *, float *, float *);
extern void vector3f_subtract(float *, float *, float *);
extern void vector2i_add(int *, int *, int *);
extern void vector3f_add(float *, float *, float *);
extern void vector2i_set(int *, int, int);
extern void vector2f_set(float *, float, float);
extern void vector3f_set(float *, float, float, float);
extern void vector4f_set(float *, float, float, float, float);
extern void vector2i_copy(int *, int *);
extern void vector2f_copy(float *, float *);
extern void vector3f_copy(float *, float *);
extern void vector2f_swap(float *, float *);

#endif /* _VECTOR_H */
