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

/**
 * \addtogroup Mutexes
 * \{ 
 */

#ifndef MTX_H
#define MTX_H

#include <types.h>
#include <task.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mtx
{
   kobj_t   obj;
   uint32_t nest;
   pri_t    owner_priority;
   task_t * owner;
   list_t   list;
} mtx_t;

/**
 * Initialises a mutex handle. The mutex is unlocked when created.
 *
 * This function must not be called with a handle that was returned by
 * mtx_create().
 *
 * \param mtx           Mutex handle
 */
void mtx_init (mtx_t * mtx);

/**
 * Deinitialises a mutex handle. The mutex must not be in use when
 * this function is called (no task can be waiting for the mutex, nor
 * can they do so at any time after calling this function).
 *
 * This function must not be called with a handle that was returned by
 * mtx_create(). See mtx_destroy().
 *
 * \param mtx           Mutex handle
 */
void mtx_deinit (mtx_t * mtx);

/**
 * Allocates and initialises a mutex handle. See mtx_init() for
 * further details.
 *
 * \return The mutex handle to be used in all subsequent operations on
 * the mutex.
 */
mtx_t * mtx_create (void);

/**
 * Frees the resources allocated by the mutex. The mutex must not be
 * in use when this function is called (no task can be waiting for the
 * mutex, nor can they do so at any time after calling this function).
 *
 * This function must only be called with a handle that was returned
 * by mtx_create().
 *
 * \param mtx           Mutex handle
 */
void mtx_destroy (mtx_t * mtx);

/**
 * Locks the mutex. If the mutex is available the function will return
 * immediately. If it is not available, the calling task will be put
 * in the WAITING state until the mutex becomes available.
 *
 * Additionally, if the mutex is not available, and it is currently
 * locked by a task with a lower priority than the calling task, then
 * the priority of that task will be raised to the priority of the
 * calling task. The priority is restored when the mutex is unlocked.
 * This is known as the \a priority \a inheritance \a protocol and is
 * used to overcome the priority inversion problem.
 *
 * Mutexes can be locked recursively. Recursive locking occurs when a
 * task locks a mutex more than once. In this case the task is not
 * blocked. rt-kernel keeps track of the recursive lock count on the
 * mutex so that the mutex is only unlocked when the lock count
 * reaches zero. In other words, the mutex is unlocked when the number
 * of calls to mtx_unlock() is equal to the number of calls to
 * mtx_lock().
 *
 * \param mtx           Mutex handle
 */
void mtx_lock (mtx_t * mtx);

/**
 * Analogous to mtx_lock(), but a maximum time to wait can be
 * specified. If the mutex is not available, the calling task will
 * wait until the mutex becomes available, or the number of ticks
 * given by \a time expires.
 *
 * \param mtx           Mutex handle
 * \param time          Number of ticks to wait
 *
 * \return 0 if the mutex was acquired successfully, 1 if the
 * service timed out.
 */
int mtx_lock_tmo (mtx_t * mtx, tick_t time);

/**
 * Unlocks the mutex. The call will reduce the recursive lock count
 * and return immediately if the calling task has locked the mutex
 * more than once. Otherwise, the first task that was waiting on the
 * mutex (if any) will be put in the READY state.
 *
 * The priority of the task will be restored to its original state if
 * it had been increased due to the priority inheritance protocol.
 *
 * \param mtx           Mutex handle
*/
void mtx_unlock (mtx_t * mtx);

/**
 * Sets the name of the mutex.
 *
 * This function is only used for debugging purposes, where a kernel-aware
 * debugger may present this name to the user.
 *
 * The name will be stored in a separate table for kernel objects.
 * If the name could not be set, the error is silently ignored.
 *
 * \param mtx           Mutex handle
 * \param name          String describing mutex
 */
void mtx_set_name (mtx_t * mtx, const char * name);

/**
 * Prints all allocated mutexes to stdout using rprintp(). This may prove
 * useful for debugging purposes. This function should not be called
 * from application code, but may be called from e.g. uerror() or an
 * exception handler.
 *
 */
void mtx_show (void);

/**
 * Same as mtx_show(), but using supplied function for formatted
 * output.
 *
 * \param fn            Function for formatted output
 */
void mtx_show_with_fmt_fn (fmt_fn_t fn);

#ifdef __cplusplus
}
#endif

#endif /* MTX_H */


/**
 * \} 
 */
