/*
 * All.cpp
 *
 *  Created on: 12.04.2019
 *      Author: Igor
 */


extern "C"{
#include "gpio.h"

}
#include "Pozyx.hpp"

#include "cmsis_os.h"
#include "All.h"




osThreadId PozyxTaskHandle;

void StartPozyxTask(void const * argument);

void All_begin(void) {
	osThreadDef(PozyxTask, StartPozyxTask, osPriorityNormal, 0, 256);
	PozyxTaskHandle = osThreadCreate(osThread(PozyxTask), NULL);

}

void StartPozyxTask(void const * argument){

	 if(Pozyx.begin(false, MODE_INTERRUPT, POZYX_INT_MASK_IMU) == POZYX_FAILURE){ // proba nawiazaia lacznosci
		 HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
	 }
	 else {
		 HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET); // w przypadku gdyby sie nie uda³o powinna sie zapalic jedna z diod
	 }

	while(1) {
		osDelay(300);
	}

}


