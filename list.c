/* Copyright (C) 2002 Jacob Kroon, see COPYING for details */

#include <stdlib.h>
#include <string.h>
#include "list.h"

/* structs */
typedef struct _Node {
  void *data;
  int allocated;
  struct _Node *next;
} Node;

struct _List {
  Node *head;
  Node *last;
  Node *node;
  int size;
};

/* functions */
List *list_create(void)
{
  List *list;

  list = malloc(sizeof(List));
  list->head = NULL;
  list->last = NULL;
  list->node = NULL;
  list->size = 0;
  return list;
}

void list_insert_last(List * list, void *data)
{
  Node *node;

  node = malloc(sizeof(Node));
  node->data = data;
  node->allocated = 0;
  node->next = NULL;
  if (list->last == NULL) {
    list->last = node;
    list->head = node;
    list->node = node;
  } else {
    list->last->next = node;
    list->last = node;
  }
  list->size++;
}

void list_insert_copy_last(List * list, void *data, int size)
{
  void *copy;
  Node *node;

  copy = malloc(size);
  memcpy(copy, data, size);
  node = malloc(sizeof(Node));
  node->data = copy;
  node->allocated = 1;
  node->next = NULL;
  if (list->last == NULL) {
    list->last = node;
    list->head = node;
    list->node = node;
  } else {
    list->last->next = node;
    list->last = node;
  }
  list->size++;
}

void *list_get_first(List * list)
{
  if (list->head != NULL)
    return list->head->data;
  else
    return NULL;
}

void list_remove_first(List * list)
{
  Node *head;

  if (list->head == NULL)
    return;
  else {
    head = list->head;
    if (head == list->node)
      list->node = head->next;
    list->head = list->head->next;
    if (list->head == NULL)
      list->last = NULL;
    if (head->allocated)
      free(head->data);
    free(head);
  }
  list->size--;
}

void list_remove(List * list, void *data)
{
  Node *node, *prev = NULL, *next;

  node = list->head;
  while (node != NULL) {
    if (node->data == data) {
      next = node->next;
      if (prev)
	prev->next = next;
      else
	list->head = next;
      if (next == NULL)
	list->last = NULL;
      if (node->allocated)
	free(node->data);
      free(node);
      node = next;
      list->size--;
    } else {
      prev = node;
      node = node->next;
    }
  }
}

void list_reset(List * list)
{
  list->node = list->head;
}

void *list_get(List * list)
{
  if (list->node == NULL)
    return NULL;
  else
    return list->node->data;
}

void list_next(List * list)
{
  if (list->node != NULL)
    list->node = list->node->next;
}

int list_size(List * list)
{
  return list->size;
}
