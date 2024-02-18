/*******************************************************************************
 * Module: common - Platform Types Abstraction
 *
 * File Name: std_types.h
 *
 * Description: Header file for common used definitions and data types for AVR
 *
 * Author: Reem Mohy
 *******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*Boolean Data Type*/
typedef unsigned char boolean;

/*Boolean Values*/
#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#define LOGIC_LOW     (0)
#define LOGIC_HIGH    (1)

/*Define the NULL pointer*/
#define NULL_PTR   ((void*)0)

/*Equivalent Data Types*/
typedef unsigned char          uint8;              /*Range 0 => 2^(n-1)*/
typedef char                   sint8;              /*Range -2^(n-1) => 2^(n-1)-1 */
typedef unsigned short         uint16;
typedef short                  sint16;
typedef unsigned long          uint32;
typedef long                   sint32;
typedef unsigned long long     uint64;
typedef long long              sint64;
typedef float                  float32;
typedef double                 float64;

#endif /* STD_TYPES_H_ */
