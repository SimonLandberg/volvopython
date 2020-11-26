/* Copyright (C) 2020 - AB Volvo
 *
 *
 * Middleware specific datatypes.
 *
 * @file mw_types.h
 *
 */

#ifndef MW_TYPES_H
#define MW_TYPES_H

/*************************************** Include *****************************************************/

/* C standard */
#include <math.h>
typedef unsigned long long uint64_t ;
typedef signed long long int64_t ;

#ifndef NATIVE_COMPILE
//#include <sys/_stdint.h>
#else
#include <stdint.h>
#endif

#include <stdbool.h>

/* Platform */

/* Subsystem internal */

/* Subsystem external */

/*************************************** Macro definitions *******************************************/

/*! Macro to be used as a special qualifier for signals in C code that are logged by ECU external tools */
#define MW_TYPES_LOG_SIGNAL

/*! Macro to be used as a special qualifier for signals in C code that are possible to change with ECU external tools */
#define MW_TYPES_PARAMETER const volatile

/*************************************** Type definitions ********************************************/

/*! Bool with status */
typedef struct
{
    bool        data_B;     //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tBS;

/*! Unsigned 8 bit with status */
typedef struct
{
    uint8_t     data_U08;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tU08S;

/*! Signed 8 bit with status */
typedef struct
{
    int8_t      data_S08;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tS08S;

/*! Unsigned 16 bit with status */
typedef struct
{
    uint16_t    data_U16;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tU16S;

/*! Signed 16 bit with status */
typedef struct
{
    int16_t     data_S16;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tS16S;

/*! Unsigned 32 bit with status */
typedef struct
{
    uint32_t    data_U32;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tU32S;

/*! Signed 32 bit with status */
typedef struct
{
    int32_t     data_S32;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tS32S;

/*! Unsigned 64 bit with status */
typedef struct
{
    uint64_t    data_U64;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tU64S;

/*! Signed 64 bit with status */
typedef struct
{
    int64_t     data_S64;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tS64S;

/*! Float 32 bit with status */
typedef struct
{
    float_t     data_F32;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tF32S;

/*! Float 64 bit with status */
typedef struct
{
    double_t    data_F64;   //!< Data
    bool        status_B;   //!< true = data can be used, false = some error found with data
} tF64S;

/*************************************** Variable declarations ***************************************/


/*************************************** Function declarations ***************************************/


#endif /* MW_TYPES_H */
