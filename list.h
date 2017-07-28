/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#ifndef _LIST_H
#define _LIST_H

/* structs */
typedef struct _List List;

/* functions */
List *list_create(void);
void list_insert_last(List *, void *);
void list_insert_copy_last(List *, void *, int);
void *list_get_first(List *);
void list_remove_first(List *);
void list_remove(List *, void *);
void *list_get(List *);
void list_next(List *);
void list_reset(List *);
int list_size(List *);

#endif /* _LIST_H */
