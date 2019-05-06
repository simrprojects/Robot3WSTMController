/*
 * All.cpp
 *
 *  Created on: 12.04.2019
 *      Author: Igor
 */



#include "All.h"
#include "main.h"
#include "FreeRTOSConfig.h"
extern "C"{
#include "gpio.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
}

#include "Pozyx.hpp"

void PozyxTask(void* argument);

xTaskHandle  PozyxTaskHandle;

uint8_t regs[3],selftest; //test

void All_begin(void){
	 xTaskCreate(PozyxTask,"pozyx", 200,0, 1, &PozyxTaskHandle);
}

 void PozyxTask(void * argument){

	  Pozyx.Init();


	  while(1){
		  if(Pozyx.waitOnINT(1000)){
			  Pozyx.setLed(4,1);
		  }
	  }
 }

/*
osThreadId PozyxTaskHandle;

void StartPozyxTask(void const * argument);

void All_begin(void) {
	osThreadDef(PozyxTask, StartPozyxTask, osPriorityNormal, 0, 256);
	PozyxTaskHandle = osThreadCreate(osThread(PozyxTask), NULL);

}

void StartPozyxTask(void const * argument){

	 //if(Pozyx.begin() == POZYX_FAILURE){ // proba nawiazaia lacznosci
	if(Pozyx.begin() == POZYX_FAILURE){
		 HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
	 }
	 else {
		 HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET); // w przypadku gdyby sie nie uda³o powinna sie zapalic jedna z diod
	 }

	while(1) {
		osDelay(300);
	}

}
*/


