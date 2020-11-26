#include <flags.h>
#include <mw_can.h>
#include <mw_can_gen.h>
#include <mw_types.h>
#include <sys/_stdint.h>
#include <task.h>
#include <tick.h>
#include <tmr.h>

#define TASK_PRIORITY_EXAMPLE_TASK     (7)
#define TASK_STACK_SIZE_EXAMPLE_TASK   (4 * 1024)
#define EXAMPLE_TASK_PERIOD_MS         (10)

#define TASK_FLAG  BIT(0)

static flags_t * task_flag;


/*
 * Timer callback.
 *
 * @param tmr       - timer object, required by platform but not used
 * @param arg       - argument provided by platform, sets the bit in the flag object our task is waiting for
 *
 */
static void task_timer_entry(tmr_t * tmr, void *arg)
{
    (void) tmr;
    flags_set(task_flag, (uint32_t) arg);
}
int multiplyme(int a, int b)
{
    return (a * b);
}
int addme(int a, int b)
{
    return (a + b);
}

void skrivut()
{
    printf("test123");
}

/*
 * Handler for the example task.
 *
 * @param arg       - argument from platform, not used
 *
 */
static void task_entry(void *arg)
{
    (void) arg;
    flags_mask_t flag_mask = TASK_FLAG;
    flags_value_t flag_value;
    task_flag = flags_create(0);
	tF32S temp_F32S;
    float can_can1CcvsWheelSpeed_F32;

    while (1) {

        /* Will wait here until our timer has set the flag, i.e. when it is time for another execution tick. When
         * the flag is set, our task will execute if there are no other tasks with higher prio executing (or waiting to be executed)
         */
        flags_wait_any(task_flag, flag_mask, &flag_value);
        flags_clr(task_flag, flag_value);

        /* Read input */
		temp_F32S = can_app_get_can1_ccvs_wheelbasedvehiclespeed();
		if (can_app_get_timeout_can1_ccvs() == false && temp_F32S.status_B == true)
		{
			can_can1CcvsWheelSpeed_F32 = temp_F32S.data_F32;
		}


        /* Write output */
		can_app_set_can1_debug7_fas_chassi_extreq_functionid(1);
		can_app_write_can1_debug7_fas_chassi_extreq(true);
    }
}

/*void example_init(void)
{
    tmr_t * appTimer;
    task_t * appTask;

    /* Create the task 
    appTask = task_create("example",
                          task_entry,
                          TASK_PRIORITY_EXAMPLE_TASK,
                          TASK_STACK_SIZE_EXAMPLE_TASK,
                          (void *) 0);
    ASSERT(appTask != NULL);

    /* Create the timer that will trigger the task every EXAMPLE_TASK_PERIOD, using TASK_FLAG bit value in the flag object 
    appTimer = tmr_create(tick_from_ms(EXAMPLE_TASK_PERIOD_MS),
                          task_timer_entry,
                          (void *) TASK_FLAG,
                          TMR_CYCL);
    ASSERT(appTimer != NULL);

    /* Start tasks and timers 
    task_start(appTask);
    tmr_start(appTimer);
}*/

int main()
{
    skrivut();

    mw_can_init();

    //example_init();

    mw_can_transmit_timers_start();
    mw_can_timeout_timers_start();
    return 0;
}
