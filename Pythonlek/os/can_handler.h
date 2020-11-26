/********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * http://www.rt-labs.com
 * Copyright 2018 rt-labs AB, Sweden.
 * See LICENSE file in the project root for full license information.
 ********************************************************************/

/**
 * \addtogroup can_handler CAN handler
 * \{
 * CAN handler for receiving and transmitting CAN frames.
 *
 * This module contains the CAN receive task used for handling
 * CAN frames that are received via different CAN networks.
 * When a CAN frame is received the CAN rx callback function signals
 * the CAN handler receive task that there is a received CAN frame
 * available on a specific CAN network.
 *
 * The CAN handler receive task takes an empty CAN message from
 * the message pool and fetch the received CAN frame and stores it
 * in the CAN message. The CAN message is then posted to
 * the CAN worker task.
 *
 * The CAN worker task waits for received CAN messages being posted
 * from the receive task and then handles them one by one by calling
 * the CAN interface handler.
 */

#ifndef CAN_HANDLER_H
#define CAN_HANDLER_H

#include <can/can.h>

#define CAN_NR_OF_DEVICES     10

/**
 * Sends CAN frame on a given network.
 *
 * \param network    Network that the CAN frame should be send on.
 * \param tx_frame   CAN frame to be transmitted.
 *
 * \return 0 = ok, -1 = send timed out, -2 = transmission disabled.
 */
int can_handler_tx (uint8_t network, can_frame_t * tx_frame);

/**
 * Enable CAN transmission on a given network.
 *
 * \param network    Network that the CAN transmission should be enabled for.
 *
 * \return           0 = ok, -1 = incorrect network, -2 = uninitialised network.
 */
int can_handler_tx_enable (uint8_t network);

/**
 * Disable CAN transmission on a given network.
 *
 * \param network    Network that the CAN transmission should be disabled for.
 *
 * \return           0 = ok, -1 = incorrect network, -2 = uninitialised network.
 */
int can_handler_tx_disable (uint8_t network);

/**
 * Initialize CAN handler and starts the CAN receive task and
 * CAN worker task.
 *
 * \param priority_worker_task      Task priority for CAN worker task.
 * \param priority_rx_task          Task priority for CAN receive task.
 * \param stack_size_worker_task    Stack size for CAN worker task.
 * \param stack_size_rx_task        Stack size for CAN receive task.
 *
 * \note Should be called only once at startup.
 */
void can_handler_init (pri_t priority_worker_task, pri_t priority_rx_task,
      size_t stack_size_worker_task, size_t stack_size_rx_task);

#endif /* CAN_HANDLER_H */

/**
 * \}
 */
