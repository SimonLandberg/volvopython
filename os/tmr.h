/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * http://www.rt-labs.com
 * Copyright 2007 rt-labs AB, Sweden.
 * See LICENSE file in the project root for full license information.
 ********************************************************************/

/**
 * \addtogroup Timers
 * \{
 */

#ifndef TMR_H
#define TMR_H

#include <types.h>
#include <list.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct tmr
{
   kobj_t       obj;
   tick_t       timeout;
   list_item_t  tick;
   void         (*callback)(struct tmr *, void *);
   void         * arg;
   uint32_t     mode;
} tmr_t;

#define TMR_RUN        (1 << 16)   /* Timer running */

/* Executes the callback */
void tmr_expired (tmr_t * timer);

#define TMR_ONCE              0     /* Timer one shot */
#define TMR_CYCL        (1 << 0)    /* Timer cyclical */
 
/**
 * Initialises a timer handle. The \a timeout parameter specifies the
 * number of ticks between the timer is started and it expires.  When
 * it expires the function \a callback will be called with \a arg as
 * parameter. Timers are run in one-shot or cyclical mode as specified
 * by the \a mode parameter.
 *
 * The callback is called from interrupt context, and is therefore
 * subject to the same restrictions as interrupt service
 * routines. Callbacks should be short, and they must not block. See
 * \ref interrupt.
 *
 * This function must not be called with a handle that was returned by
 * tmr_create().
 *
 * \param timer          Timer handle
 * \param timeout        Ticks between timer is started and it expires
 * \param callback       Callback function to call when timer expires
 * \param arg            Parameter sent to callback
 * \param mode           Defines timer type, one-shot TMR_ONCE, or cyclical TMR_CYCL
 */
void tmr_init (tmr_t * timer, tick_t timeout,
               void (*callback)(tmr_t *, void *),
               void * arg, uint32_t mode);

/**
 * Deinitialises the timer handle. The timer must not be in use when
 * this function is called (the timer can't be started and queued up).
 *
 * This function must not be called with a handle that was returned by
 * tmr_create(). See tmr_destroy().
 *
 * \param timer          Timer handle
 */
void tmr_deinit (tmr_t * timer);

/**
 * Allocates and initialises a timer handle. See tmr_init() for
 * further details.
 *
 * \param timeout        Ticks between timer is started and it expires
 * \param callback       Callback function to call when timer expires
 * \param arg            Parameter sent to callback
 * \param mode           Defines timer type, one-shot TMR_ONCE, or cyclical TMR_CYCL
 * 
 * \return The timer handle to be used in all subsequent operations
 * on the timer.
 */
tmr_t * tmr_create (tick_t timeout, void (*callback)(tmr_t *,void *),
                    void * arg, uint32_t mode);

/**
 * Frees the resources allocated by the timer. The timer must not be
 * in use when this function is called (the timer can't be started and
 * queued up).
 *
 * This function must only be called with a handle that was returned
 * by tmr_create().
 *
 * \param timer          Timer handle
 */
void tmr_destroy (tmr_t * timer);

/**
 * Reconfigures the timer. The timer must be stopped when this function is
 * called. If there are consecutive calls of tmr_set, the last value is used.
 *
 * \param timer          Timer handle
 * \param timeout        Reconfigure timer timeout value
 */ 
void tmr_set (tmr_t * timer, tick_t timeout);

 /**
 * Starts the timer. The timer must not already have been started when
 * this function is called.
 *
 * \param timer          Timer handle
 */
void tmr_start (tmr_t * timer);

/**
 * Stops the timer. When a timer has been stopped it can be reconfigured or
 * started again.
 *
 * \param timer          Timer handle
 */
void tmr_stop (tmr_t * timer);

/**
 * Sets the name of the timer.
 *
 * This function is only used for debugging purposes, where a kernel-aware
 * debugger may present this name to the user.
 *
 * The name will be stored in a separate table for kernel objects.
 * If the name could not be set, the error is silently ignored.
 *
 * \param tmr            Timer handle
 * \param name           String describing timer
 */
void tmr_set_name (tmr_t * tmr, const char * name);

/**
 * Prints all registered timers to stdout using rprintp(). This may prove
 * useful for debugging purposes. This function should not be called
 * from application code, but may be called from e.g. uerror() or an
 * exception handler.
 */
void tmr_show (void);

/**
 * Same as tmr_show(), but using supplied function for formatted
 * output.
 *
 * \param fn            Function for formatted output
 */
void tmr_show_with_fmt_fn (fmt_fn_t fn);

#ifdef __cplusplus
}
#endif

#endif /*TMR_H*/

/**
 * \} 
 */
