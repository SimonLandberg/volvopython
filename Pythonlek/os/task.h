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
 * \addtogroup Tasks
 * \{ 
 */

#ifndef TASK_H
#define TASK_H

#include <types.h>
#include <list.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct ksig ksig_t;
typedef struct task
{
   uint32_t        magic;
   const char *    name;
   void *          entry;
   stack_t *       stack;
   stack_t *       stack_top;
   stack_t *       stack_ptr;
   stack_t *       sentinel;
   void *          arg;
   list_t *        block_list;
   list_item_t     priority;
   list_item_t     tick;
   list_item_t     chain;
   uint16_t        state;
   int8_t          start;
   uint8_t         trace_handle;
   ksig_t *        sig_head; 
   ksig_t *        sig_tail;
   uint32_t        flags_mask;
   struct _reent * reent;
   void *          extend;
} task_t;

#define TASK_GET_TRACE_HANDLE(t) (((task_t *)(t))->trace_handle)

/* Signals are defined here as they are used in the task_t struct */
struct ksig
{
   uint32_t magic;
   ksig_t * next;
   task_t * owner;
   task_t * sender;
   signo_t  signo;
};

#define ST_DEAD     (1 << 0)    /* Task is waiting to be deleted */
#define ST_WAIT     (1 << 1)    /* Task is blocked: */
#define ST_SEM      (1 << 2)    /*  on semaphore */
#define ST_MTX      (1 << 3)    /*  on mutex */
#define ST_SIG      (1 << 4)    /*  on signal */
#define ST_DLY      (1 << 5)    /*  on timer */
#define ST_FLAG     (1 << 6)    /*  on flag */
#define ST_FLAG_ALL (1 << 7)    /*  on flag and flag mode is "ALL" */
#define ST_MBOX     (1 << 8)    /*  on mailbox */
#define ST_STP      (1 << 9)    /*  self stopped */
#define ST_SUSPEND  (1 << 10)   /* Task is suspended */
#define ST_TT       (1 << 11)   /* Time triggered task */
#define ST_TT_YIELD (1 << 12)   /* Time triggered task that yields */
#define ST_CREATE   (1 << 13)   /* Task was created by task_create() */

void task_exit (void);

/**
 * Initialises a task handle. This function must be called before
 * calling any other task function. The task_create() function calls
 * this function automatically.
 *
 * The stack and task handle is supplied by the caller and can be
 * declared statically. It is strongly recommended that they are not
 * allocated on the stack of another task, as they may then go out of
 * scope if the declaring stack frame exits.
 *
 * The task is initialised to the WAITING state, as if task_stop() had
 * been called. task_start() will start the task.
 *
 * See task_spawn() for further details.
 *
 * \code
 * task_t t1;
 * stack_t t1_stack[256];
 * 
 * void t1_entry (void * arg)
 * {
 *    for (;;)
 *   {
 *      // task main loop
 *   }
 * }
 * 
 * int main (void)
 * {
 *    task_init (&t1, "t1", t1_entry, 5, t1_stack, sizeof(t1_stack), NULL);
 *    task_start (&t1);
 *    return 0;
 * }
 * \endcode
 *
 * \param task          Handle of task to initialise
 * \param name          String describing task
 * \param entry         Entry function of the task
 * \param priority      Priority of the task
 * \param stack         Pointer to start of stack for task
 * \param stack_size    Size of the stack (number of bytes)
 * \param arg           Sent as argument to task
 *
 */
void task_init (task_t * task, const char * name,
                void (*entry)(void *), pri_t priority,
                stack_t * stack, size_t stack_size, void * arg);

/**
 * Allocates and initialises a task handle as well as stack space for
 * the task. This function must be called before calling any other
 * task function. The task_spawn() function calls this function
 * automatically. See task_spawn() for further details.
 *
 * The task is initialised to the WAITING state, as if task_stop() had
 * been called. task_start() will start the task.
 *
 * \param name          String describing task
 * \param entry         The entry function of the task
 * \param priority      The priority of the task
 * \param stack_size    The size of the stack (number of bytes)
 * \param arg           Sent as argument to task
 *
 * \return The task handle to be used in all subsequent operations on
 * the task
 */
task_t * task_create (const char * name, void (*entry)(void *), pri_t priority,
                      size_t stack_size, void * arg);

/**
 * Delays the calling task until the specified amount of ticks have
 * occurred. Note that the next tick may occur soon after calling this
 * function. In other words, if a delay of at least t ticks is
 * required, call task_delay(t + 1).
 *
 * Calling task_delay() with \a time set to 0 is equivalent to
 * yielding the processor to another task of the same priority. The
 * task will be swapped out if another task of the same priority is
 * ready to execute.
 *
 * \param time          The amount of ticks to delay the task
 */
void task_delay (tick_t time);

/**
 * Finds the task with the given name. If more than one task has the
 * same name, only the first one encountered will be returned.
 *
 * \param name          String to search for
 */
task_t * task_find (const char * name);

/**
 * Makes a task ready for execution. After calling this function the
 * task will be scheduled for execution as appropriate. This function
 * is called automatically by task_spawn().
 *
 * This function is deprecated and will be removed in a future
 * release, call task_start() instead.
 *
 * \param task          Task handle
 */
//CC_ATTRIBUTE_DEPRECATED void task_run (task_t * task);

/**
 * Returns the task handle of the calling task.
 *
 * \return Handle of the calling task.
 */
task_t * task_self (void);

/**
 * Allocates and starts a task in one go. Equivalent to calling
 * task_create() followed by task_start().
 *
 * \param name          String describing task
 * \param entry         Entry function of the task
 * \param priority      Priority of the task
 * \param stack_size    Size of the stack (number of bytes)
 * \param arg           Sent as argument to task
 *
 * \return              Task handle
 *
 * Note that \a name must be a pointer to a static memory area. In
 * order to save memory, rt-kernel does not make a local copy of the
 * name.
 *
 * The \a priority of the task is used when more than one task is
 * ready to execute. The task with the highest priority will always be
 * scheduled for execution first. The priority is a number between 0
 * and 31; higher numbers indicate higher priorities. In other words,
 * 0 is the lowest priority and 31 is the highest. Note that priority
 * level 0 is reserved for the idle task. Priority level 31 is
 * reserved for time-triggered tasks and should not be used if such
 * tasks exist in the system.
 *
 * The \a stack_size parameter indicates the number of bytes available
 * for the task stack. All variables and data with local scope are
 * stored on the stack. Making the stack too small is a common source
 * of hard to find bugs in real-time systems. rt-kernel is able to
 * detect some stack overflows; if the stack has overflown when the
 * task calls a kernel service that causes it to be swapped out then a
 * system error function is called. Likewise, the kernel will call the
 * system error function if the task is swapped out because another
 * higher priority task becomes ready. rt-kernel does not detect 
 * temporary overflow of the stack in between such events.
 * See \ref Error.
 *
 * The \a arg parameter is sent as argument to the task entry
 * function. It can be used to identify different instances of tasks
 * sharing the same code. The argument should be cast as a void
 * pointer, but can be any parameter. If more than one parameter is
 * needed a struct can be used:
 *
 * \code
 * struct myParams {
 *   int a;
 *   char * b;
 * };
 *
 * void myTaskEntry (void * arg) {
 *   struct myParams * param = (struct myParams *)arg;
 *
 *   for (;;)
 *   {
 *      // task main loop
 *   }
 * }
 *
 * void foo() {
 *   static struct myParams myParams1 = { 1, "1" };
 *   static struct myParams myParams2 = { 2, "2" };
 *   task_t * myFirstTask;
 *   task_t * mySecondTask;
 *
 *   myFirstTask = task_spawn ("myFirstTask", myTaskEntry, 10, 1024,
 *                             (void *)&myParams1);
 *   mySecondTask = task_spawn ("mySecondTask", myTaskEntry, 10, 1024,
 *                              (void *)&myParams2);
 * }
 * \endcode
 *
 */
task_t * task_spawn (const char * name, void (*entry)(void *), pri_t priority,
                     size_t stack_size, void * arg);

/**
 * Delete a task. The task will never resume execution.
 *
 * This is a potentially unsafe operation. The task to be deleted
 * may own resources that other tasks in the system depend
 * upon.
 *
 * It is not possible to delete the idle task or any time-triggered
 * task. The calling task is not allowed to delete itself.
 *
 * The task resources that were allocated if the task was created by
 * task_create() are released. Any resource that was allocated by the
 * task itself is not released.
 *
 * \param task          Handle of the task to delete.
 */
void task_delete (task_t * task);

/**
 * Puts another task in the READY state. Together with task_stop(),
 * this function can be used to synchronise a task in response to
 * external events. The effect is similar to using a semaphore but
 * these functions do not require memory for keeping track of the
 * synchronisation object (e.g. a semaphore handle).
 *
 * Note that the task is not made READY if the number of calls to
 * task_start() is not equal to the number of calls to task_stop().
 *
 * A potential usage of task_start() is to signal a task from an ISR:
 *
 * \code
 * void myISR()
 * {
 *    // Clear interrupt source
 *    ....
 *
 *    // Notify task that interrupt occurred
 *    task_start (theTask);
 * }
 * \endcode
 *
 * \param task          Handle of the task to be made READY.
 */
void task_start (task_t * task);

/**
 * Puts the calling task in the WAITING state. Together with task_start(),
 * this function can be used to synchronise a task in response to
 * external events. The effect is similar to using a semaphore but
 * these functions do not require memory for keeping track of the
 * synchronisation object (e.g. a semaphore handle).
 *
 * Note that the task is not made WAITING if task_start() has been
 * called more times than task_stop().
 *
 * A potential usage of task_start() is to synchronise with an ISR:
 *
 * \code
 * void myTask (void * arg)
 * {
 *    for (;;)
 *    {
 *       // Wait for interrupt
 *       task_stop();
 *
 *       // Handle interrupt at task level
 *       ...
 *    }
 * }
 * \endcode
 */
void task_stop (void);

/**
 * Suspend a task. The task will not execute until task_resume() is
 * called.
 *
 * A suspended task that is delayed or waiting for a resource will
 * leave the WAITING state when the delay expires or the resource
 * becomes available, and will become READY once task_resume() is
 * called.
 
 * This is a potentially unsafe operation. The task to be suspended
 * may own resources that other tasks in the system depend
 * upon. Suspension is primarily intended for debugging.
 *
 * It is not possible to suspend the idle task or any time-triggered
 * task.
 *
 * \param task          Handle of the task to suspend.
 */
void task_suspend (task_t * task);

/**
 * Resume a task that was previously suspended by a call to
 * task_suspend().
 *
 * \param task          Handle of the task to resume.
 */
void task_resume (task_t * task);

/**
 * Set the priority of the calling task.
 *
 * \param priority      New priority
 */
void task_priority_set (pri_t priority);

/**
 * Get the priority of the calling task.
 *
 * \return              Priority of the calling task.
 */
pri_t task_priority_get (void);

/**
 * Get the name of a task.
 *
 * \param task          Handle of the task.
 *
 * \return              The name of the task.
 */
const char * task_name_get (task_t * task);

/**
 * Prints the task state to stdout using rprintp(). This may prove
 * useful for debugging purposes. This function should not be called
 * from application code, but may be called from e.g. uerror() or an
 * exception handler.
 *
 */
void task_show (void);

/**
 * Same as task_show(), but using supplied function for formatted
 * output.
 *
 * \param fn            Function for formatted output
 */
void task_show_with_fmt_fn (fmt_fn_t fn);

#ifdef __cplusplus
}
#endif

#endif /* TASK_H */


/**
 * \} 
 */


