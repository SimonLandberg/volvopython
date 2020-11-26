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
 * \addtogroup vgtt_crc VGTT CRC/Counter
 * \{
 * Module implementing VGTT CRC/Counter algorithm for message counter
 * and CRC in CAN messages.
 *
 * Contains functions for checking message counter and CRC in a CAN frame
 * and adding a message counter and CRC to a CAN frame.
 */

#ifndef _VGTT_CRC_H_
#define _VGTT_CRC_H_

#include <can/can.h>

/**
 * Check message counter and CRC in byte[7] of a CAN frame.
 *
 * \param frame         Pointer to CAN frame to be checked.
 * \param msg_counter   Pointer to variable holding the message counter.
 *
 * \return -1 = Wrong DLC. -2 = Wrong message count, -3 = CRC mismatch. 0 = ok.
 */
int vgtt_crc_check (can_frame_t * frame, uint8_t * msg_counter);

/**
 * Add message counter and CRC to byte[7] of a CAN frame.
 *
 * \param frame         Pointer to CAN frame to be changed.
 * \param msg_counter   Pointer to variable holding the message counter.
 *
 * \return -1 = Wrong DLC. 0 = ok.
 */
int vgtt_crc_add (can_frame_t * frame, uint8_t * msg_counter);

#endif /* VGTT_CRC_H_ */

/**
 * \}
 */
