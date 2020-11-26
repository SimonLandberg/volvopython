/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * http://www.rt-labs.com
 * Copyright 2006 rt-labs AB, Sweden.
 * See LICENSE file in the project root for full license information.
 ********************************************************************/

#ifndef LIST_H
#define LIST_H

#include "types.h"
#include <stddef.h>

#define TO_TASK(p, offset) (void *)((char *)(p) - offset)
#define TO_ITEM(p, offset) (list_item_t *)((char *)(p) + offset)

typedef struct list_item list_item_t;
struct list_item
{
  list_item_t * next;
  list_item_t * prev;
  uint32_t      value;
};

typedef struct list
{
  list_item_t * head;
  list_item_t * tail;
} list_t;

static inline void list_init (list_t * list)
{
   list->head = (list_item_t *)list;
   list->tail = (list_item_t *)list;
}

static inline int list_empty (list_t * list)
{
   return (list->head == (list_item_t *)list);
}

static inline void * list_head (list_t * list, int offset)
{
  return TO_TASK (list->head, offset);
}

static inline void * list_tail (list_t * list, int offset)
{
  return TO_TASK (list->tail, offset);
}

static inline void * list_next (list_t * list, void * task, int offset)
{
  list_item_t * item = TO_ITEM (task, offset);

  if (item->next == (list_item_t *)list)
     return NULL;
  
  return TO_TASK (item->next, offset);
}

static inline void * list_pop_head (list_t * list, int offset)
{
   list_item_t * item = list->head;

   item->prev->next = item->next;
   item->next->prev = item->prev;   
   return TO_TASK (item, offset);
}

static inline void * list_pop_tail (list_t * list, int offset)
{
   list_item_t * item = list->tail;

   item->prev->next = item->next;
   item->next->prev = item->prev;   
   return TO_TASK (item, offset);
}

static inline void list_copy (list_t * src, list_t * dst)
{
   if (list_empty (src))
   {
      list_init (dst);
   }
   else
   {
      dst->head = src->head;
      dst->tail = src->tail;
      dst->head->prev = (list_item_t *)dst;
      dst->tail->next = (list_item_t *)dst;
   }   
}

static inline void list_remove (list_t * list, void * task, int offset)
{
   (void)list;
   
   list_item_t * item = TO_ITEM (task, offset);

   item->prev->next = item->next;
   item->next->prev = item->prev;   
}

static inline void list_insert (list_t * list, void * task, int offset)
{
   list_item_t * item = TO_ITEM (task, offset);
   list_item_t * ix = (list_item_t *)list;

   do
   {
      ix = ix->next;
   } while (ix != (list_item_t *)list && ix->value >= item->value);

   item->next = ix;
   item->prev = ix->prev;
   ix->prev = item;
   item->prev->next = item;
}
      
static inline void * list_traverse (list_t * list, int (*func)(void *, void *), void * arg, int offset)
{
   list_item_t * ix = (list_item_t *)list;

   do
   {
      ix = ix->next;
   } while (ix != (list_item_t *)list && func (TO_TASK (ix, offset), arg) == 0);

   if (ix == (list_item_t *)list)
      return NULL;
   
   return TO_TASK (ix, offset);
}

#define PRIOQ_INIT(l)     list_init(l)
#define PRIOQ_EMPTY(l)    list_empty(l)
#define PRIOQ_HEAD(l)     ((task_t *)list_head(l, offsetof(task_t, priority)))
#define PRIOQ_NEXT(l,t)   ((task_t *)list_next(l, t, offsetof(task_t, priority)))
#define PRIOQ_POP(l)      ((task_t *)list_pop_head(l, offsetof(task_t, priority)))
#define PRIOQ_COPY(s,d)   list_copy(s, d)
#define PRIOQ_REMOVE(l,t) list_remove(l, t, offsetof(task_t, priority))
#define PRIOQ_INSERT(l,t) list_insert(l, t, offsetof(task_t, priority))

#define TICKQ_INIT(l)     list_init(l)
#define TICKQ_EMPTY(l)    list_empty(l)
#define TICKQ_HEAD(l)     ((task_t *)list_tail(l, offsetof(task_t, tick)))
#define TICKQ_POP(l)      ((task_t *)list_pop_tail(l, offsetof(task_t, tick)))
#define TICKQ_COPY(s,d)   list_copy(s, d)
#define TICKQ_REMOVE(l,t) list_remove(l, t, offsetof(task_t, tick))
#define TICKQ_INSERT(l,t) list_insert(l, t, offsetof(task_t, tick))

#define TIMERQ_INIT(l)     list_init(l)
#define TIMERQ_EMPTY(l)    list_empty(l)
#define TIMERQ_HEAD(l)     ((tmr_t *)list_tail(l, offsetof(tmr_t, tick)))
#define TIMERQ_POP(l)      ((tmr_t *)list_pop_tail(l, offsetof(tmr_t, tick)))
#define TIMERQ_COPY(s,d)   list_copy(s, d)
#define TIMERQ_REMOVE(l,t) list_remove(l, t, offsetof(tmr_t, tick))
#define TIMERQ_INSERT(l,t) list_insert(l, t, offsetof(tmr_t, tick))

#define CHAINQ_INIT(l)       list_init(l)
#define CHAINQ_EMPTY(l)      list_empty(l)
#define CHAINQ_HEAD(l)       ((task_t *)list_head(l, offsetof(task_t, chain)))
#define CHAINQ_POP(l)        ((task_t *)list_pop_head(l, offsetof(task_t, chain)))
#define CHAINQ_COPY(s,d)     list_copy(s, d)
#define CHAINQ_REMOVE(l,t)   list_remove(l, t, offsetof(task_t, chain))
#define CHAINQ_INSERT(l,t)   list_insert(l, t, offsetof(task_t, chain))
#define CHAINQ_TRAVERSE(l,f,a) list_traverse(l, f, a, offsetof(task_t, chain))

#endif /* LIST_H */
