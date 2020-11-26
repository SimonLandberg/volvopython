/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * http://www.rt-labs.com
 * Copyright 2010 rt-labs AB, Sweden.
 * See LICENSE file in the project root for full license information.
 ********************************************************************/

/**
 * \defgroup can CAN (Controller Area Network) Driver API
 * \{ 
 *
 * The following example first configures a CAN node and then attempts to
 * send and receive CAN frames.
 * \code
 * int node;
 * const can_cfg_t bus_configuration =
 * {
 *    .baudrate = 500000,
 *    .bs1 = 6,
 *    .bs2 = 2,
 *    .sjw = 2 ,
 *    .silent = false,
 * };
 * const can_filter_t pass_all =
 * {
 *    .id = 0,
 *    .mask = 0,
 * };
 * const can_frame_t sent =
 * {
 *    .id = 42,
 *    .dlc = 8,
 *    .data = {1, 2, 3, 4, 5, 6, 7, 8},
 * };
 * can_frame_t received;
 * int error;
 * can_status_t status;
 *
 * // Get file descriptor
 * node = open ("/can1", O_RDWR);
 * if (node < 0)
 * {
 *    // Could not allocate file descriptor (wrong driver name?)
 * }
 *
 * // Set bus configuration
 * can_set_cfg (node, &bus_configuration);
 *
 * // Set up acceptance filter for received frames
 * error = can_filter (node, &pass_all);
 * if (error)
 * {
 *    // Could not install filter (no free filter slot available)
 * }
 *
 * // Connect node to CAN bus, enabling frames to be sent/received
 * can_bus_on (node);
 *
 * // Wait for node to go on bus
 * do
 * {
 *    can_get_status (node, &status);
 * } while (status.flags != CAN_STATUS_ERROR_ACTIVE);
 *
 * // Start transmitting a frame
 * error = can_transmit (node, &sent);
 * if (error == ETIMEDOUT)
 * {
 *    // Could not transmit frame (no free buffer available)
 * }
 *
 * // Wait until frame is sent
 * do
 * {
 *    can_get_status (node, &status);
 * } while (status.flags & CAN_STATUS_TX_PENDING);
 *
 * // Wait until a frame is received in Rx FIFO
 * do
 * {
 *    can_get_status (node, &status);
 * } while ((status.flags & CAN_STATUS_RX_PENDING) == 0);
 *
 * // Read frame from Rx FIFO, if available
 * error = can_receive (node, &received);
 * if (error == ENODATA)
 * {
 *    // No frame received
 * }
 * \endcode
 */

#ifndef CAN_H
#define CAN_H

#include <types.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** Configuration of CAN node */
typedef struct can_cfg
{
   uint32_t baudrate;           /** Baudrate [bps] */
   uint8_t  bs1;                /** Bit segment 1 (PROP_SEG + PHASE_SEG1) */
   uint8_t  bs2;                /** Bit segment 2 (PHASE_SEG2) */
   uint8_t  sjw;                /** Resynchronisation jump width */
   uint8_t  silent;             /** Silent mode:
                                 ** If 1, node will never write any frame
                                 ** to bus nor ACK any received frames.
                                 ** If 0, node will participate in bus traffic
                                 ** as normal.
                                 **/
} can_cfg_t;

#define CAN_ID_EXT BIT (31)     /** Extended 29-bit ID */
#define CAN_ID_RTR BIT (30)     /** Remote transmission request */
#define CAN_ID_MASK 0x1FFFFFFF  /** Mask out flags */

typedef uint32_t can_id_t;       /** CAN ID */

/** CAN frame */
typedef struct can_frame
{
   can_id_t id;                  /** ID with combination of CAN_ID flags */
   uint8_t  data[8];             /** Data with size given as MIN(dlc, 8) */
   uint8_t  dlc;                 /** Valid values: 0 - 15 */
   uint8_t  pad[3];
} __attribute__((packed)) can_frame_t;

/** CAN reception filter */
typedef struct can_filter
{
   can_id_t id;                 /** Filter identifier */
   can_id_t mask;               /** Filter mask */
} can_filter_t;

/** Status of CAN node */
typedef struct can_status
{
   uint32_t tx_error;           /** Number of Tx errors */
   uint32_t rx_error;           /** Number of Rx errors */
   uint32_t overrun;            /** Number of Rx overrun errors */
   uint16_t flags;              /** Combination of CAN_STATUS flags */
} can_status_t;

#define CAN_STATUS_ERROR_PASSIVE   BIT (8) /** The node is error passive */
#define CAN_STATUS_BUS_OFF         BIT (7) /** The node is off bus */
#define CAN_STATUS_ERROR_WARNING   BIT (6) /** At least one error counter > 96 */
#define CAN_STATUS_ERROR_ACTIVE    BIT (5) /** The node is error active */
#define CAN_STATUS_TX_PENDING      BIT (4) /** There are messages to be sent */
#define CAN_STATUS_RX_PENDING      BIT (3) /** There are message to receive */
#define CAN_STATUS_TX_ERR          BIT (2) /** There is at least one Tx error */
#define CAN_STATUS_RX_ERR          BIT (1) /** There is at least one Rx error */
#define CAN_STATUS_BUFFER_OVERFLOW BIT (0) /** There has been at least one overrun */

/** CAN event */
typedef uint16_t can_event_t;

/** CAN callback function to be called when event occurs */
typedef void (*can_callback_t)(void * arg, can_event_t event);

#define CAN_EVENT_MSG_RECEIVED     BIT(0)

/**
 * Sets the CAN baudrate and timing according to the contents of \a
 * cfg. This specifies the baudrate as well as the sampling point.
 * Prior to calling can_set_cfg the node should be deactivated by
 * calling can_bus_off.
 *
 * \param fd            CAN node file descriptor
 * \param cfg           CAN configuration parameters
 */
void can_set_cfg (int fd, const can_cfg_t * cfg);

/**
 * Activates the CAN transceiver.
 *
 * \param fd            CAN node file descriptor
 */
void can_bus_on (int fd);

/**
 * Deactivates the CAN transceiver.
 *
 * \param fd            CAN node file descriptor
 */
void can_bus_off (int fd);

/**
 * Sets a receive filter on the CAN node. More than one filter can be
 * set. The maximum number of filters is hardware dependent. Note that
 * all incoming messages must pass at least one filter.
 *
 * A filter is specified by the \a id and \a mask parameters. The \a
 * id parameter contains a CAN identifier. The \a mask parameter
 * contains the bits that must match the id for the filter to
 * pass. Use the CAN_ID_EXT bit to match extended or standard
 * identifiers.
 *
 * Thus, the filter will pass an incoming message if the
 * following holds: filter.id & filter.mask == msg.id & filter.mask.
 *
 * At least one filter must be set to receive any messages.
 *
 * \code
 * const can_filter_t pass_all = {
 *   .id   = 0,
 *   .mask = 0,
 * };
 *
 * const can_filter_t extended_only = {
 *   .id   = CAN_ID_EXT,
 *   .mask = CAN_ID_EXT,
 * };
 *
 * const can_filter_t specific_identifier = {
 *   .id   = CAN_ID_EXT | 0x1234,
 *   .mask = CAN_ID_EXT | CAN_ID_MASK,
 * };
 * \endcode
 *
 * \param fd            CAN node file descriptor
 * \param filter        CAN filter
 *
 * \return ENOENT if out of filters, 0 otherwise.
 */
int can_filter (int fd, const can_filter_t * filter);

/**
 * Receives a CAN message. The message is copied to the \a frame
 * parameter. ENODATA is returned if no CAN message was available.
 *
 * The frame 
 *
 * \param fd            CAN node file descriptor
 * \param frame         Incoming CAN frame
 *
 * \return ENODATA if no CAN message was available, 0 otherwise.
 */
int can_receive (int fd, can_frame_t * frame);

/**
 * Sends a CAN message. The caller is blocked until a free transmit
 * buffer is available, or timeout. Value for timeout is set when driver
 * is initialised.
 *
 * \param fd            CAN node file descriptor
 * \param frame         Outgoing CAN frame
 *
 * \return ETIMEDOUT if no transmit buffers were available, 0 otherwise.
 */
int can_transmit (int fd, const can_frame_t * frame);

/**
 * Gets the CAN status of node. The CAN status consists of the number of
 * transmit and receive errors, the number of overruns, and a set
 * CAN_STATUS flags. See the \a can_status_t type.
 *
 * \param fd            CAN node file descriptor
 * \param status        Current CAN status
 */
void can_get_status (int fd, can_status_t * status);

/**
 * Sets a callback, a function to be called in response to certain
 * events. There can be at most one callback per CAN node.
 *
 * The callback will be called when any event in the \a mask parameter
 * occurs. The parameter \a arg will be passed to the callback
 * function.
 *
 * Currently the only callback event is CAN_EVENT_MSG_RECEIVED.
 *
 * \param fd            CAN node file descriptor
 * \param callback      The callback function
 * \param mask          The requested set of callback events
 * \param arg           Sent as argument to function
 */
void can_set_callback (int fd, can_callback_t callback, can_event_t mask, void * arg);

#ifdef __cplusplus
}
#endif

#endif /* CAN_H */

/**
 * \} 
 */

