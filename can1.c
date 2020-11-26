#include <flags.h>
#include <mtx.h>
#include <can_diag_handler.h>
#include <can/can.h>
void mtx_unlock (mtx_t * mtx)
{

}
void mtx_lock (mtx_t * mtx)
{

}
mtx_t * mtx_create (void)
{

}
void mtx_init (mtx_t * mtx)
{

}
void can_diag_set_reply_callback
   (void (*callback)(can_ecu_id_t can_id, diag_reply_t diag_reply, void * data))
{

}

void can_boot_common_write_data (uint8_t * data, uint8_t length, char * rev)
{

}

void can_boot_common_read_data(void)
{

}

void can_diag_handler (can_diag_cmd_req_t req)
{

}

void can_boot_common_start_write(void)
{

}

void can_boot_common_cmd(void)
{

}

int can_filter (int fd, const can_filter_t * filter)
{

}

void can_handler_tx(uint8_t network, can_frame_t * tx_frame)
{

}

void crcInit(void)
{

}

void vgtt_crc_add(void)
{

}

void tmr_stop(void)
{

}

void can_handler_init(pri_t priority_worker_task, pri_t priority_rx_task, size_t stack_size_worker_task, size_t stack_size_rx_task)
{

  printf("%d\n", priority_worker_task);
  printf("%d\n", priority_rx_task);
  printf("%d\n", stack_size_worker_task);
  printf("%d\n", stack_size_rx_task);
  can_interface_init();
  struct can_cfg a;
  a.baudrate = 5;
}
