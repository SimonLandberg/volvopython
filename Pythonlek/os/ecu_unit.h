#ifndef ECU_UNIT_H
#define ECU_UNIT_H

/** ECU unit source address */
typedef enum can_ecu_id
{
   CAN_ECU_ID_VCM1 = 0xF0,
   CAN_ECU_ID_VCM2 = 0xF1,
   CAN_ECU_ID_CPU = 0xF2,
   CAN_ECU_ID_FPU = 0xF3,
   CAN_ECU_ID_EPU = 0xF4,
   CAN_ECU_ID_APU = 0xF5,
} can_ecu_id_t;

#endif /* ECU_UNIT_H */