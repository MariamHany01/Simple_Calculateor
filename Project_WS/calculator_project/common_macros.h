/*
 * comon_macros.h
 *
 *  Created on: 28 Sep 2023
 *      Author: maria
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(reg,bit_num) (reg|=(1<<bit_num))

#define CLEAR_BIT(reg,bit_num) (reg&=~(1<<bit_num))

#define TOGGLE_BIT(reg,bit_num) (reg^=(1<<bit_num))

/*rotate bit of the register right direction */
#define ROR(reg,num) ((reg<<((sizeof(reg)*8)-num)|(reg>>num))

/*rotate bit of the register left direction */
#define ROL(reg,num) ((reg>>((sizeof(reg)*8)-num)|(reg<<num))

#define BIT_IS_SET(reg,bit_num)  (reg&(1<<bit_num))

#define BIT_IS_CLEAR(reg,bit_num) (!(reg&(bit_num)))

#define READ_PIN(reg,pin_num)  ((reg&(1<<pin_num))>>pin_num)

#endif /* COMMON_MACROS_H_ */
