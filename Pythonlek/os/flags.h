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
 * \addtogroup Flags
 * \{ 
 */

#ifndef FLAGS_H
#define FLAGS_H

#include <types.h>
#include <list.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef uint32_t flags_mask_t;
typedef flags_mask_t flags_value_t;

typedef struct flags
{
   kobj_t   obj;
   uint32_t values;
   list_t   list;    /* Blocked tasks */
} flags_t;

/**
 * Initialises a flags handle. The flag register is initialised to \a
 * value.
 *
 * This function must not be called with a handle that was returned by
 * flags_create().
 *
 * \param flags         Flags handle
 * \param value         Initial value of flags
 */
void flags_init (flags_t * flags, flags_value_t value);

/**
 * Deinitialises the flags handle. The flags must not be in use when
 * this function is called (no task can be waiting on the flag, nor
 * can they do so at any time after calling this function).
 *
 * This function must not be called with a handle that was returned by
 * flags_create(). See flags_destroy().
 *
 * \param flags         Flags handle
 */
void flags_deinit (flags_t * flags);

/**
 * Clears the flag. Bits that are set to one in the mask are cleared
 * in the flag register. Bits that are set to zero in the mask are left unmodified.
 *
 * \param flags         Flags handle
 * \param mask          Mask value
 */
void flags_clr (flags_t * flags, flags_mask_t mask);

/**
 * Allocates and initialises a flags handle. See flags_init() for
 * further details.
 *
 * \param value         Initial value of flags
 *
 * \return The flags handle to be used in all subsequent operations
 * on the flag.
 */
flags_t * flags_create (flags_value_t value);

/**
 * Frees the resources allocated by the flags. The flags must not be in
 * use when this function is called (no task can be waiting on the
 * flag, nor can they do so at any time after calling this function).
 *
 * This function must only be called with a handle that was returned
 * by flags_create().
 *
 * \param flags         Flags handle
 */
void flags_destroy (flags_t * flags);

/**
 * Gets the value in the flag register.
 *
 * \param flags         Flags handle
 *
 * \return The value in the flag register.
 */
flags_value_t flags_get (flags_t * flags);

/**
 * Sets the flag. Bits that are set to one in the mask are set in the
 * flag register. Bits that are set to zero in the mask are left unmodified.
 *
 * If any tasks were waiting on any of the bits that were modified,
 * they will be put in the READY state.
 *
 * \param flags         Flags handle
 * \param mask          Mask value
 */
void flags_set (flags_t * flags, flags_mask_t mask);

/**
 * Waits for all of the requested bits in the flag register to be set.
 *
 * If all of the bits that are set to one in the mask are also set to
 * one in the flag, then the function will return immediately. If any
 * of the bits that are set to one in the mask are not set in the
 * flag, then the calling task is put in the WAITING state.
 *
 * \param flags         Flags handle
 * \param mask          Mask value
 * \param value         Updated with value of flags after waiting
 */
void flags_wait_all (flags_t * flags, flags_mask_t mask, flags_value_t * value);

/**
 * Analogous to flags_wait_all(), but a maximum time to wait can be
 * specified. If any of the requested bits are not set, the calling
 * task will wait until all of the requested bits become set, or the
 * number of ticks given by \a time expires.
 *
 * \param flags         Flags handle
 * \param mask          Mask value
 * \param time          Number of ticks to wait
 * \param value         Updated with value of flags after waiting
 *
 * \return 0 if all of the requested bits are set, 1 if the service
 * timed out.
 */
int flags_wait_all_tmo (flags_t *flags, flags_mask_t mask, tick_t time,
				flags_mask_t * value);

/**
 * Waits for any of the requested bits in the flag register to be set.
 *
 * If any of the bits that are set to one in the mask are also set to
 * one in the flag, then the function will return immediately. If none
 * of the bits that are set to one in the mask are set in the flag,
 * then the calling task is put in the WAITING state.
 *
 * \param flags         Flags handle
 * \param mask          Mask value
 * \param value         Updated with value of flag register after waiting
 *
 */
void flags_wait_any (flags_t * flags, flags_mask_t mask, flags_value_t * value);

/**
 * Analogous to flags_wait_any(), but a maximum time to wait can be
 * specified. If none of the requested bits are set, the calling task
 * will wait until any of the requested bits become set, or the number
 * of ticks given by \a time expires.
 *
 * \param flags         Flags handle
 * \param mask          Mask value
 * \param time          Number of ticks to wait
 * \param value         Updated with value of flag register after waiting
 *
 * \return 0 if any of the requested bits are set, 1 if the service
 * timed out.
 */
int flags_wait_any_tmo (flags_t * flags, flags_mask_t mask, tick_t time,
				flags_value_t * value);

/**
 * Sets the name of the flag.
 *
 * This function is only used for debugging purposes, where a kernel-aware
 * debugger may present this name to the user.
 *
 * The name will be stored in a separate table for kernel objects.
 * If the name could not be set, the error is silently ignored.
 *
 * \param flags         Flags handle
 * \param name          String describing flag
 */
void flags_set_name (flags_t * flags, const char * name);

/**
 * Prints all registered flags to stdout using rprintp(). This may prove
 * useful for debugging purposes. This function should not be called
 * from application code, but may be called from e.g. uerror() or an
 * exception handler.
 */
void flags_show (void);

/**
 * Same as flags_show(), but using supplied function for formatted
 * output.
 *
 * \param fn            Function for formatted output
 */
void flags_show_with_fmt_fn (fmt_fn_t fn);

#ifdef __cplusplus
}
#endif

#endif /* FLAGS_H */

/**
 * \} 
 */
