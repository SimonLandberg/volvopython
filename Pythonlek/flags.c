
#include <flags.h>
#include <mw_types.h>
#include <tmr.h>
#include <task.h>

void flags_set (flags_t * flags, flags_mask_t mask) {

}

void flags_clr (flags_t * flags, flags_mask_t mask) {

}

flags_t * flags_create (flags_value_t value) {
    return 0;
}

void flags_wait_any (flags_t * flags, flags_mask_t mask, flags_value_t * value) {

}




tick_t tick_from_ms (uint32_t ms) {
    return 0;
}

tmr_t * tmr_create (tick_t timeout, void (*callback)(tmr_t *,void *), void * arg, uint32_t mode) {
    return 0;
}

void task_start (task_t * task) {

}

void tmr_start (tmr_t * timer) {

}



void ASSERT(void) {

}

void BIT(void) {

}

task_t * task_create (const char * name, void (*entry)(void *), pri_t priority, size_t stack_size, void * arg) {

}
