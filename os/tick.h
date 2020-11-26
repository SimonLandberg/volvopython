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
 * \addtogroup Tick
 * \{ 
 */

#ifndef TICK_H
#define TICK_H

#include <types.h>

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * Returns the current tick.
 *
 * \return The current tick
 */
tick_t tick_get (void);

/**
 * Sets the current tick. Application code should not normally call
 * this function, however it may be useful for testing purposes.
 *
 * \param tick          The new current tick
 */
void tick_set (tick_t tick);

/**
 * Converts the given number of ticks to milliseconds.
 *
 * \param tick          ticks
 *
 * \return The number of milliseconds corresponding to the given
 * number of ticks.
 */
uint32_t tick_to_ms (tick_t tick);

/**
 * Converts the given number of milliseconds to ticks.
 *
 * \param ms            milliseconds
 *
 * \return The number of ticks corresponding to the given number of
 * milliseconds.
 */
tick_t tick_from_ms (uint32_t ms);

/**
 * Returns a value to be used for timestamping purposes. The values
 * returned are increasing and may wrap. The default implementation of
 * this function is identical to tick_get(). The default
 * implementation may be overriden by the BSP to provide better
 * accuracy.
 *
 * \return The current timestamp value.
 */
uint32_t timestamp_get (void);

/**
 * Delays the caller for at least the number of microseconds given by
 * \a us. The default implementation of this function calls
 * task_delay() to do the delay. The default implementation may be
 * overriden by the BSP to provide better accuracy. Note that it is
 * expected that implementations may use busy loops instead of
 * blocking calls.
 *
 * This function is intended to be used by drivers as a last resort
 * when there is no other way to synchronise with hardware. The delays
 * are expected to be short.
 *
 * \param us            Delay at least this many microseconds
 */
void udelay (uint32_t us);

/**
 * \internal
 *
 * This function is called by the timer interrupt service routine to
 * inform the kernel that a new tick has happened.
 */
void tick (void);

#ifdef __cplusplus
}
#endif

#endif /* TICK_H */

/**
 * \} 
 */

