/*
 * Callbacks.cpp
 *
 *  Created on: 19.04.2019
 *      Author: Igor
 */

#include "All.h"
#include "cmsis_os.h"

extern "C"{
#include "gpio.h"


}
#include "main.h"
#include "Pozyx.hpp"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// zmiana flagi przerwania w POZYX
	if (GPIO_Pin == POZYX_INT_1_EXTI_IRQn) {  // PF15 -> pin 2 z Arduino
		Pozyx.SendMsgFromIrq();

	}
    else if (GPIO_Pin == POZYX_INT_2_EXTI_IRQn) { // PF13 -> pin 3 z Arduino
    	Pozyx._interrupt = 1;
    	//HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
    }
}



