/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * http://www.rt-labs.com
 * Copyright 2017 rt-labs AB, Sweden.
 * See LICENSE file in the project root for full license information.
 ********************************************************************/

/**
 * Kernel object table
 *
 * Keeps track of kernel objects, except tasks and signals. This is only used
 * for debugging.
 *
 * Note that the size of the table does not put a limit on the number kernel
 * objects that may be created. If no more slots are available in the table
 * when creating an object, an error counter is incremented. The objects is
 * still created, assuming available memory in the system is sufficient.
 *
 * \internal
 */

#ifndef KOBJ_H
#define KOBJ_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <types.h>

/**
 * The kernel object table.
 *
 * Contains references to all registered kernel objects in the system,
 * as well as some extra information about them.
 */
typedef struct kobj_table kobj_table_t;

/**
 * Callback function called by kobj_traverse() for each found kernel object
 * in the kernel object table whose type is the requested one.
 *
 * \param obj        Kernel object found.
 * \param name       Name of kernel object.
 * \param arg        Argument supplied when object was registered.
 * \param func_arg   Argument supplied when kobj_traverse() was called
 */
typedef void (*kobj_func_t) (kobj_t * obj, const char * name, void * arg, void * func_arg);

/**
 * Register kernel object.
 *
 * A reference to the object will be put in the kernel object table if
 * a free slot is available. An error counter will be incremented if object
 * could not be registered.
 *
 * Performance is O(N). Interrupts will be disabled while updating an element
 * in the table, but not during the entire traversal.
 *
 * \pre Interrupts are enabled.
 *
 * \param obj           Kernel object to be registered.
 * \param arg           Argument to be passed to kobj_traverse().
 */
void kobj_register (kobj_t * obj, void * arg);

/**
 * Unregister kernel object.
 *
 * If object was registered, then its spot in the kernel object table will be
 * set to NULL. If object was never registered (due to lack of space)
 * then the error is silently ignored.
 *
 * Performance is O(N). Interrupts will be disabled while updating an element
 * in the table, but not during the entire traversal.
 *
 * \pre Interrupts are enabled.
 *
 * \param obj           Kernel object to be unregistered.
 */
void kobj_unregister (kobj_t * obj);

/**
 * Set name of kernel object.
 *
 * If object was registered, then the pointer will be stored in the object's
 * spot in the kernel object table. If object was never registered (due to lack
 * of space) then the error is silently ignored.
 *
 * Performance is O(N). Interrupts will be disabled while updating an element
 * in the table, but not during the entire traversal.
 *
 * \pre Interrupts are enabled.
 *
 * \param obj           Kernel object.
 * \param name          Name to be set. The string will not be copied. The
 *                      string should be statically allocated.
 */
void kobj_set_name (kobj_t * obj, const char * name);

/**
 * Traverse the kernel object table, calling \a func(obj) for each found object
 * \a obj of type \a magic_id.
 *
 * Performance is O(N). Interrupts are not disabled while traversing the table.
 * The called function may disable interrupts while executing
 * and then re-enable them before returning.
 *
 * \pre Interrupts are enabled.
 *
 * \param magic_id      Magic number representing type of kernel object.
 * \param func          Function to be called for each object found.
 * \param arg           Opaque user argument
 * \return              An error message if some or all objects had not been
 *                      registered, NULL otherwise.
 */
const char * kobj_traverse (uint32_t magic_id, kobj_func_t func, void * arg);

/**
 * Try to create the kernel object table.
 *
 * This should only be called once.
 *
 * @return              The table if the configured size is non-zero,
 *                      NULL otherwise.
 */
kobj_table_t * kobj_init (void);

#ifdef __cplusplus
}
#endif

#endif /* KOBJ_H */
