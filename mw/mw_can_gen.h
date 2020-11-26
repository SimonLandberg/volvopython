/* Copyright (C) 2020 - AB Volvo
 *
 *
 * Middleware interface to CAN, generated part.
 *
 * @file mw_can_gen.h
 *
 */

/*[[[cog
  # Create global configuration data used by all cog snippets
  import avcmpy.codegen.can
  avcmpy.codegen.can.can_create_global_conf(net)
  ]]]*/
/*[[[end]]]*/

#ifndef MW_CAN_GEN_H
#define MW_CAN_GEN_H

/*************************************** Include *****************************************************/

/* C standard */
#ifndef NATIVE_COMPILE
#include <sys/_stdint.h>
#else
#include <stdint.h>
#endif

/* Platform */

/* Manager internal */

/* Manager external */
#include "mw_types.h"

/*************************************** Macro definitions *******************************************/


/*************************************** Type definitions ********************************************/


/*************************************** Variable declarations ***************************************/


/*************************************** Function declarations ***************************************/

/*[[[cog
  # Generate function declarations for get RX signals
  avcmpy.codegen.can.cog_app_get_declarations()
  ]]]*/
/* <-------------- Generated Code Start (Do not edit!) --------------> */
/*! Returns physical value of WheelBasedVehicleSpeed in message CCVS, unit [km/h] */
tF32S can_app_get_can1_ccvs_wheelbasedvehiclespeed (void);

/*! Returns physical value of FunctionId in message Debug7_FAS_Chassi_ExtReq_Recv, unit [-] */
tU08S can_app_get_can1_debug7_fas_chassi_extreq_recv_functionid (void);
/*! Returns physical value of DeltaTorque in message Debug7_FAS_Chassi_ExtReq_Recv, unit [Nm] */
tF32S can_app_get_can1_debug7_fas_chassi_extreq_recv_deltatorque (void);
/*! Returns physical value of RoadWheelAngle in message Debug7_FAS_Chassi_ExtReq_Recv, unit [rad] */
tF32S can_app_get_can1_debug7_fas_chassi_extreq_recv_roadwheelangle (void);
/*! Returns physical value of HaptFeedback in message Debug7_FAS_Chassi_ExtReq_Recv, unit [-] */
tU08S can_app_get_can1_debug7_fas_chassi_extreq_recv_haptfeedback (void);
/*! Returns physical value of Reserved_ExtRequest in message Debug7_FAS_Chassi_ExtReq_Recv, unit [-] */
tU16S can_app_get_can1_debug7_fas_chassi_extreq_recv_reserved_extrequest (void);

/*! Returns physical value of PoweredVehicleWeight in message CVW_X_EBS, unit [kg] */
tF32S can_app_get_can2_cvw_x_ebs_poweredvehicleweight (void);
/*! Returns physical value of GrossCombinationVehicleWeight in message CVW_X_EBS, unit [kg] */
tF32S can_app_get_can2_cvw_x_ebs_grosscombinationvehicleweight (void);

/*! Returns physical value of ASRBrakeControlActive in message EBC1_X_EBS, unit [] */
tU08S can_app_get_can3_ebc1_x_ebs_asrbrakecontrolactive (void);
/*! Returns physical value of ASREngineControlActive in message EBC1_X_EBS, unit [] */
tU08S can_app_get_can3_ebc1_x_ebs_asrenginecontrolactive (void);
/*! Returns physical value of AntiLockBrakingActive in message EBC1_X_EBS, unit [] */
tU08S can_app_get_can3_ebc1_x_ebs_antilockbrakingactive (void);
/*! Returns physical value of ABSFullyOperational in message EBC1_X_EBS, unit [] */
tU08S can_app_get_can3_ebc1_x_ebs_absfullyoperational (void);

/*! Returns physical value of XBRSystemState in message EBC5, unit [] */
tU08S can_app_get_can4_ebc5_xbrsystemstate (void);
/*! Returns physical value of XBRActiveControlMode in message EBC5, unit [] */
tU08S can_app_get_can4_ebc5_xbractivecontrolmode (void);

/*! Returns physical value of EngineTorqueMode in message EEC1_X_EMS, unit [-] */
tU08S can_app_get_can5_eec1_x_ems_enginetorquemode (void);
/*! Returns physical value of ActualEnginePercentTorque in message EEC1_X_EMS, unit [percent] */
tF32S can_app_get_can5_eec1_x_ems_actualenginepercenttorque (void);
/*! Returns physical value of EngineSpeed in message EEC1_X_EMS, unit [rpm] */
tF32S can_app_get_can5_eec1_x_ems_enginespeed (void);

/*! Returns physical value of ActualEngineRetarderPercentTrq in message ERC1_X_EMSRet, unit [percent] */
tF32S can_app_get_can6_erc1_x_emsret_actualengineretarderpercenttrq (void);

/*! Returns physical value of TransmissionSelectedGear in message ETC2_X_TECU, unit [-] */
tF32S can_app_get_can7_etc2_x_tecu_transmissionselectedgear (void);
/*! Returns physical value of TransmissionCurrentGear in message ETC2_X_TECU, unit [-] */
tF32S can_app_get_can7_etc2_x_tecu_transmissioncurrentgear (void);

/*! Returns physical value of TPCM_ControlByte_EMS in message TPCM_X_EMS, unit [] */
tU08S can_app_get_can8_tpcm_x_ems_tpcm_controlbyte_ems (void);
/*! Returns physical value of TPCM_EMS_MsgLen in message TPCM_X_EMS, unit [] */
tU16S can_app_get_can8_tpcm_x_ems_tpcm_ems_msglen (void);
/*! Returns physical value of TPCM_EMS_NbrOfPackets in message TPCM_X_EMS, unit [] */
tU08S can_app_get_can8_tpcm_x_ems_tpcm_ems_nbrofpackets (void);
/*! Returns physical value of TPCM_EMS_Reserved in message TPCM_X_EMS, unit [] */
tU08S can_app_get_can8_tpcm_x_ems_tpcm_ems_reserved (void);
/*! Returns physical value of TPCM_EMS_PGN in message TPCM_X_EMS, unit [] */
tU32S can_app_get_can8_tpcm_x_ems_tpcm_ems_pgn (void);

/*! Returns physical value of SteeringWheelAngle in message VDC2_X_EBS, unit [rad] */
tF32S can_app_get_can9_vdc2_x_ebs_steeringwheelangle (void);

/*! Returns physical value of VehicleMode in message VMCU_BB1_01P, unit [] */
tU08S can_app_get_can10_vmcu_bb1_01p_vehiclemode (void);
/*! Returns physical value of VehicleMode_UB in message VMCU_BB1_01P, unit [] */
tU08S can_app_get_can10_vmcu_bb1_01p_vehiclemode_ub (void);

/* <-------------- Generated Code Stop (Do not edit!) --------------> */
/*[[[end]]]*/

/*[[[cog
  # Generate function declarations for get RX timeout info
  avcmpy.codegen.can.cog_app_timeout_declarations()
  ]]]*/
/* <-------------- Generated Code Start (Do not edit!) --------------> */
bool can_app_get_timeout_can1_ccvs (void);
bool can_app_get_timeout_can1_debug7_fas_chassi_extreq_recv (void);

bool can_app_get_timeout_can2_cvw_x_ebs (void);

bool can_app_get_timeout_can3_ebc1_x_ebs (void);

bool can_app_get_timeout_can4_ebc5 (void);

bool can_app_get_timeout_can5_eec1_x_ems (void);

bool can_app_get_timeout_can6_erc1_x_emsret (void);

bool can_app_get_timeout_can7_etc2_x_tecu (void);

bool can_app_get_timeout_can8_tpcm_x_ems (void);

bool can_app_get_timeout_can9_vdc2_x_ebs (void);

bool can_app_get_timeout_can10_vmcu_bb1_01p (void);

/* <-------------- Generated Code Stop (Do not edit!) --------------> */
/*[[[end]]]*/

/*[[[cog
  # Generate function declarations for set TX signals
  # TODO: Should be written as mw_can_set...
  avcmpy.codegen.can.cog_app_set_declarations()
  ]]]*/
/* <-------------- Generated Code Start (Do not edit!) --------------> */
/*! Set physical value of ParkAndTrailerAirPressure in message AIR1_X_VMCU, unit [kPa] */
void can_app_set_can1_air1_x_vmcu_parkandtrailerairpressure (float_t value);
/*! Set physical value of ServiceBrakeAirPrsCircuit1 in message AIR1_X_VMCU, unit [kPa] */
void can_app_set_can1_air1_x_vmcu_servicebrakeairprscircuit1 (float_t value);
/*! Set physical value of ServiceBrakeAirPrsCircuit2 in message AIR1_X_VMCU, unit [kPa] */
void can_app_set_can1_air1_x_vmcu_servicebrakeairprscircuit2 (float_t value);
/*! Write message AIR1_X_VMCU to platform, will be sent on CAN if active */
void can_app_write_can1_air1_x_vmcu (bool active);

/*! Set physical value of FunctionId in message Debug7_FAS_Chassi_ExtReq, unit [-] */
void can_app_set_can1_debug7_fas_chassi_extreq_functionid (uint8_t value);
/*! Set physical value of DeltaTorque in message Debug7_FAS_Chassi_ExtReq, unit [Nm] */
void can_app_set_can1_debug7_fas_chassi_extreq_deltatorque (float_t value);
/*! Set physical value of RoadWheelAngle in message Debug7_FAS_Chassi_ExtReq, unit [rad] */
void can_app_set_can1_debug7_fas_chassi_extreq_roadwheelangle (float_t value);
/*! Set physical value of HaptFeedback in message Debug7_FAS_Chassi_ExtReq, unit [-] */
void can_app_set_can1_debug7_fas_chassi_extreq_haptfeedback (uint8_t value);
/*! Set physical value of Reserved_ExtRequest in message Debug7_FAS_Chassi_ExtReq, unit [-] */
void can_app_set_can1_debug7_fas_chassi_extreq_reserved_extrequest (uint16_t value);
/*! Write message Debug7_FAS_Chassi_ExtReq to platform, will be sent on CAN if active */
void can_app_write_can1_debug7_fas_chassi_extreq (bool active);

/*! Set physical value of AmbientAirTemperature in message AMB_X_VMCU, unit [DegreeC] */
void can_app_set_can2_amb_x_vmcu_ambientairtemperature (float_t value);
/*! Write message AMB_X_VMCU to platform, will be sent on CAN if active */
void can_app_write_can2_amb_x_vmcu (bool active);

/*! Set physical value of FrontAxleSpeed in message EBC2_X_EBS, unit [km_per_h] */
void can_app_set_can3_ebc2_x_ebs_frontaxlespeed (float_t value);
/*! Set physical value of FrAxleLeftWheelRelativeSpeed in message EBC2_X_EBS, unit [km_per_h] */
void can_app_set_can3_ebc2_x_ebs_fraxleleftwheelrelativespeed (float_t value);
/*! Set physical value of FrAxleRightWheelRelativeSpeed in message EBC2_X_EBS, unit [km_per_h] */
void can_app_set_can3_ebc2_x_ebs_fraxlerightwheelrelativespeed (float_t value);
/*! Set physical value of RrAxle1LeftWheelRelativeSpeed in message EBC2_X_EBS, unit [km_per_h] */
void can_app_set_can3_ebc2_x_ebs_rraxle1leftwheelrelativespeed (float_t value);
/*! Set physical value of RrAxle1RightWheelRelativeSpeed in message EBC2_X_EBS, unit [km_per_h] */
void can_app_set_can3_ebc2_x_ebs_rraxle1rightwheelrelativespeed (float_t value);
/*! Set physical value of RrAxle2LeftWheelRelativeSpeed in message EBC2_X_EBS, unit [Km_per_h] */
void can_app_set_can3_ebc2_x_ebs_rraxle2leftwheelrelativespeed (float_t value);
/*! Set physical value of RrAxle2RightWheelRelativeSpeed in message EBC2_X_EBS, unit [Km_per_h] */
void can_app_set_can3_ebc2_x_ebs_rraxle2rightwheelrelativespeed (float_t value);
/*! Write message EBC2_X_EBS to platform, will be sent on CAN if active */
void can_app_write_can3_ebc2_x_ebs (bool active);

/*! Set physical value of XBRSystemInformation in message EBS_BB1_01P, unit [] */
void can_app_set_can4_ebs_bb1_01p_xbrsysteminformation (uint8_t value);
/*! Write message EBS_BB1_01P to platform, will be sent on CAN if active */
void can_app_write_can4_ebs_bb1_01p (bool active);

/*! Set physical value of NominalFrictionPercentTorque in message EEC3_X_EMS, unit [percent] */
void can_app_set_can5_eec3_x_ems_nominalfrictionpercenttorque (float_t value);
/*! Write message EEC3_X_EMS to platform, will be sent on CAN if active */
void can_app_write_can5_eec3_x_ems (bool active);

/*! Set physical value of TransmissionDrivelineEngaged in message ETC1_X_TECU, unit [-] */
void can_app_set_can6_etc1_x_tecu_transmissiondrivelineengaged (uint8_t value);
/*! Set physical value of TransmissionShiftInProcess in message ETC1_X_TECU, unit [-] */
void can_app_set_can6_etc1_x_tecu_transmissionshiftinprocess (uint8_t value);
/*! Set physical value of TransmissionOutputShaftSpeed2 in message ETC1_X_TECU, unit [rpm] */
void can_app_set_can6_etc1_x_tecu_transmissionoutputshaftspeed2 (float_t value);
/*! Set physical value of PercentClutchSlip in message ETC1_X_TECU, unit [percent] */
void can_app_set_can6_etc1_x_tecu_percentclutchslip (float_t value);
/*! Write message ETC1_X_TECU to platform, will be sent on CAN if active */
void can_app_write_can6_etc1_x_tecu (bool active);

/*! Set physical value of FrontAxleLeftWheelSpeed in message HRW_X_EBS, unit [km_per_h] */
void can_app_set_can7_hrw_x_ebs_frontaxleleftwheelspeed (float_t value);
/*! Set physical value of FrontAxleRightWheelSpeed in message HRW_X_EBS, unit [km_per_h] */
void can_app_set_can7_hrw_x_ebs_frontaxlerightwheelspeed (float_t value);
/*! Set physical value of RearAxleLeftWheelSpeed in message HRW_X_EBS, unit [km_per_h] */
void can_app_set_can7_hrw_x_ebs_rearaxleleftwheelspeed (float_t value);
/*! Set physical value of RearAxleRightWheelSpeed in message HRW_X_EBS, unit [km_per_h] */
void can_app_set_can7_hrw_x_ebs_rearaxlerightwheelspeed (float_t value);
/*! Write message HRW_X_EBS to platform, will be sent on CAN if active */
void can_app_write_can7_hrw_x_ebs (bool active);

/*! Set physical value of SecondsUTC in message TD_X_VMCU, unit [s] */
void can_app_set_can8_td_x_vmcu_secondsutc (float_t value);
/*! Set physical value of MinutesUTC in message TD_X_VMCU, unit [min] */
void can_app_set_can8_td_x_vmcu_minutesutc (uint8_t value);
/*! Set physical value of HoursUTC in message TD_X_VMCU, unit [h] */
void can_app_set_can8_td_x_vmcu_hoursutc (uint8_t value);
/*! Set physical value of MonthUTC in message TD_X_VMCU, unit [Months] */
void can_app_set_can8_td_x_vmcu_monthutc (uint8_t value);
/*! Set physical value of DayUTC in message TD_X_VMCU, unit [Days] */
void can_app_set_can8_td_x_vmcu_dayutc (float_t value);
/*! Set physical value of YearUTC in message TD_X_VMCU, unit [Years] */
void can_app_set_can8_td_x_vmcu_yearutc (float_t value);
/*! Write message TD_X_VMCU to platform, will be sent on CAN if active */
void can_app_write_can8_td_x_vmcu (bool active);

/*! Set physical value of TSC1ER_V_EnOvrdCtrlM in message TSC1_EMSRet_VMCU, unit [] */
void can_app_set_can9_tsc1_emsret_vmcu_tsc1er_v_enovrdctrlm (uint8_t value);
/*! Set physical value of TSC1ER_V_EnRSpdCtrlC in message TSC1_EMSRet_VMCU, unit [] */
void can_app_set_can9_tsc1_emsret_vmcu_tsc1er_v_enrspdctrlc (uint8_t value);
/*! Set physical value of TSC1ER_V_OvrdCtrlMPr in message TSC1_EMSRet_VMCU, unit [] */
void can_app_set_can9_tsc1_emsret_vmcu_tsc1er_v_ovrdctrlmpr (uint8_t value);
/*! Set physical value of TSC1ER_V_EnRSpdSpdLm in message TSC1_EMSRet_VMCU, unit [rpm] */
void can_app_set_can9_tsc1_emsret_vmcu_tsc1er_v_enrspdspdlm (float_t value);
/*! Set physical value of TSC1ER_V_EnRTrqTrqLm in message TSC1_EMSRet_VMCU, unit [percent] */
void can_app_set_can9_tsc1_emsret_vmcu_tsc1er_v_enrtrqtrqlm (float_t value);
/*! Write message TSC1_EMSRet_VMCU to platform, will be sent on CAN if active */
void can_app_write_can9_tsc1_emsret_vmcu (bool active);

/*! Set physical value of TotalVehicleDistanceHighRes in message VDHR_X_VMCU, unit [m] */
void can_app_set_can10_vdhr_x_vmcu_totalvehicledistancehighres (float_t value);
/*! Write message VDHR_X_VMCU to platform, will be sent on CAN if active */
void can_app_write_can10_vdhr_x_vmcu (bool active);

/* <-------------- Generated Code Stop (Do not edit!) --------------> */
/*[[[end]]]*/

#endif /* MW_CAN_GEN_H */
