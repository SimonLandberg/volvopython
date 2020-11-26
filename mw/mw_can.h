
/* Copyright (C) 2020 - AB Volvo
 *
 *
 * Middleware interface to CAN.
 *
 * @file mw_can.h
 *
 */

#ifndef MW_CAN_H
#define MW_CAN_H

/*************************************** Include *****************************************************/

/* C standard */
#include <sys/_stdint.h>

/* Platform */
#include <can/can.h>

/* Subsystem internal */

/* Subsystem external */

/*************************************** Macro definitions *******************************************/


/*************************************** Type definitions ********************************************/


/*************************************** Variable declarations ***************************************/


/*************************************** Function declarations ***************************************/

void mw_can_init(void);

void mw_can_timeout_timers_start(void);
void mw_can_timeout_timers_stop(void);
void mw_can_transmit_timers_start(void);
void mw_can_transmit_timers_stop(void);

/* Functions required by platform */
void can_interface_init(void);
void can_interface_filter(int can_fd, uint8_t can_id, uint8_t net);
can_cfg_t * can_interface_baudrate(uint8_t net, can_cfg_t * can_cfg);
void can_interface_handler(uint8_t net, can_frame_t * rx_frame);

#endif /* MW_CAN_H */
