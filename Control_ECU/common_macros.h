/*******************************************************************************
 * Module: Common - Macros
 *
 * File Name: common_macros.h
 *
 * Description: Header file for commonly used macros
 *
 * Author: Reem Mohy
 *******************************************************************************/


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*Set a certain bit in any register*/
#define SET_BIT(REG,BIT_NUM) ((REG) |= (1<<(BIT_NUM)))

/*Clear a certain bit in any register*/
#define CLEAR_BIT(REG,BIT_NUM) ((REG) &= ~(1<<(BIT_NUM)))

/*Toggle a certain bit in any register*/
#define TOGGLE_BIT(REG,BIT_NUM) ((REG) ^= (1<<(BIT_NUM)))

/*Rotate right the register value with certain number of rotations*/
#define ROR(REG,NUM_ROT) ((REG) = ((REG)>>(NUM_ROT)) | ((REG)<<(8*sizeof(REG)-(NUM_ROT))) )

/*Rotate left the register value with certain number of rotations*/
#define ROL(REG,NUM_ROT) ((REG) =  ((REG)<<(NUM_ROT)) | ((REG)>>(8*sizeof(REG)-(NUM_ROT))) )

/*Check if certain bit is set in any register*/
#define BIT_IS_SET(REG,BIT_NUM) ((REG) & (1<<(BIT_NUM)))

/*Check if certain bit is cleared in any register*/
#define BIT_IS_CLEAR(REG,BIT_NUM) (!((REG) & (1<<(BIT_NUM))))

/*Get the value of a certain bit in any register*/
#define GET_BIT(REG,BIT_NUM) (((REG) & (1<<(BIT_NUM))) >>(BIT_NUM))

#endif /* COMMON_MACROS_H_ */
