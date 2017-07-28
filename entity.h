/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#ifndef _ENTITY_H
#define _ENTITY_H

/* typedefs */
typedef union _Entity Entity;

/* functions */
extern void entity_create_door(char *);
extern void entity_create_button(char *);
extern int entity_type(Entity *);
extern void entity_draw(Entity *);

#endif /* _ENTITY_H */
