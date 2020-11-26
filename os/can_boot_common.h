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
 * \addtogroup can_boot_common CAN boot common
 * \{
 * Common CAN loader functions used in bootloader and application.
 *
 * Contains functions for boot control and CAN loader file transfers.
 */

#ifndef _CAN_BOOT_COMMON_H_
#define _CAN_BOOT_COMMON_H_

#include <stdio.h>
#include <stdbool.h>

/** CAN loader commands */
typedef enum
{
   PU_CMD_RESET = 1,
   PU_CMD_FILE_SAVED = 2,
   PU_CMD_FILE_STARTED = 3,
   PU_CMD_REMAIN_IN_BOOT = 4,
   PU_CMD_GET_VERSION = 5,
   PU_CMD_DATA_RECEIVED = 6,
} can_boot_common_cmd_t;

/** CAN loader file type */
typedef enum
{
   PU_FILE_FIRMWARE = 1,
   PU_FILE_DATASET = 2,
   PU_FILE_BOOT = 3,
} can_boot_common_file_type_t;

/** CAN loader command reply */
typedef struct __attribute__((__packed__))
{
   uint8_t  cmd;              /**< CAN loader reply command */
   uint32_t data;             /**< CAN loader reply data */
} can_boot_common_cmd_reply_t;

void can_boot_common_delete_file (char * filename);

void can_boot_common_append_file (char * filename, uint8_t * write_data, uint32_t write_size);

void can_boot_common_write_file_crc (char * filename, uint32_t crc32);

/**
 * Calculates CRC32 checksum for given filename.
 *
 * \param filename      Name of file to calculate checksum for.
 */
uint32_t can_boot_common_crc_file (char * filename);

/**
 * Checks if a file exist in the file system.
 *
 * \param filename      Name of file to check.
 *
 * \return true = file exist, false = file does not exist.
 */
bool can_boot_common_file_exists (char * filename);

/**
 * Get status for CAN loader remain in boot command.
 *
 * \return true = remain in boot command received,
 *         false = remain in boot command not received.
 */
bool can_boot_common_remain_in_boot (void);

/**
 * Handle received CAN loader start write command.
 *
 * \param type          Type of file.
 * \param file_size     Size of file.
 * \param crc32         File CRC32 checksum.
 */
void can_boot_common_start_write (can_boot_common_file_type_t type,
      uint32_t file_size, uint32_t crc32);

/**
 * Handle received CAN loader command.
 *
 * \param cmd        CAN loader command received.
 */
void can_boot_common_cmd (can_boot_common_cmd_t cmd);

/**
 * Handle received CAN loader write data command.
 *
 * This function is used to write data to either a firmware file or to a dataset file.
 * Dataset files that should be written must match the software running otherwise the
 * dataset file will not be written.
 *
 * There is a checksum check for both dataset and firmware downloaded and if this
 * check fails the dataset or firmware file will not be written.
 *
 * If a failure occurs then there will be no CAN loader reply command send and the
 * CAN loader will eventually time out.
 *
 * \param data                   Pointer to data to be written.
 * \param length                 Length of data to be written.
 * \param rev                    Revision of running software.
 */
void can_boot_common_write_data (uint8_t * data, uint8_t length, char * rev);

/**
 * Finds the first firmware in file system with a valid CRC file.
 *
 * Checking firmware 1 to 5 and returns the crc and filename of the
 * first valid firmware found.
 *
 * \param crc        Pointer to where crc of found firmware should be stored.
 * \param filename   Pointer to where filename of found firmware should be stored.
 *
 * \return true if a valid firmware is found.
 */
bool can_boot_common_find_fw (uint32_t * crc, char * filename);

/**
 * Check if dataset stored in flash has the same main revision as the
 * software currently executing.
 *
 * \param filename   Name of dataset file to compare revision to.
 * \param main_rev   Main revision of software executing.
 *
 * \return true if dataset stored in flash belongs to software running.
 */
bool can_boot_common_check_dataset_revision (char * filename, char * main_rev);

#endif /* _CAN_BOOT_COMMON_H_ */

/**
 * \}
 */
