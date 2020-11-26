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
 * \addtogroup pf Platform defines
 * \{
 * Platform defines specifying filename macros for dataset and
 * string helper functions.
 */

#ifndef PF_H
#define PF_H

/** \name String helper functions
 * \{
 */
#define JOIN(x, y, z, w)  #x#y#z#w
#define CONC(x, y) x##y
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
/**
 * \}
 */

#define MAKE_FW_CONFIG_FILENAME(x) CONC(x,_fw_config)

/** Help function for creating dataset filename from PRODUCT and REVISION */
#define MAKE_DATASET_FILENAME(x, y) JOIN(x,_dst_r, y, .ini)
/** Dataset filename on disk */
#define DATASET_FILENAME_DISK       STR(/disk1/dataset.ini)
/** Dataset checksum filename on disk */
#define DATASET_CRC_FILENAME_DISK   STR(/disk1/dataset.crc)

#define DATASET_FILENAME         MAKE_DATASET_FILENAME(PRODUCT, REVISION)
#define FW_DATA_FILENAME         STR(PRODUCT.bin)
#define FW_CONFIG_FILENAME       STR(MAKE_FW_CONFIG_FILENAME(PRODUCT).bin)

#define FW_CONFIG_MAX_SIZE_BYTES (20)
#define FW_DATA_MAX_SIZE_BYTES   (2 * 1024 * 1024)
#define DATASET_MAX_SIZE_BYTES   (30 * 1024)

#define FILENAME_DATASET_NEW     "/disk1/dataset.new"
#define FILENAME_FIRMWARE_BASE   "/disk1/firmware"
#define FILENAME_FIRMWARE_NEW    "/disk1/firmware.new"
#define FILENAME_BOOT_NEW        "/disk1/boot.new"

#define PN_MAX_LENGTH            (12)
typedef enum { HW_PN, HW_SN, STM8_PN, BOOT_PN, MSW_PN, DST_PN } part_number_t;
typedef enum { CMD_REPLY, DATA1_REPLY, DATA2_REPLY } diag_reply_t;

#endif /* PF_H */

/**
 * \}
 */
