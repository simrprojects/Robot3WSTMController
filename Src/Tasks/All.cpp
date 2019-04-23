/*
 * All.cpp
 *
 *  Created on: 12.04.2019
 *      Author: Igor
 */


#include "cmsis_os.h"
#include "All.h"
#include "main.h"
#include "FreeRTOSConfig.h"
extern "C"{
#include "gpio.h"
#include "FreeRTOS.h"

}

#include "Pozyx.hpp"

void PozyxTask(void* argument);

xTaskHandle  PozyxTaskHandle;

uint8_t regs[3],selftest; //test

void All_begin(void){
	 xTaskCreate(PozyxTask,"pozyx", 200,0, 1, &PozyxTaskHandle);
}

 void PozyxTask(void * argument){

	 // Pozyx.Init();

	 	 if(Pozyx.regRead(POZYX_WHO_AM_I, regs, 3) == POZYX_FAILURE){
	     //if(Pozyx.regRead(POZYX_ST_RESULT, &selftest, 1) == POZYX_FAILURE){
	 	 //if(Pozyx.begin(false, MODE_INTERRUPT, POZYX_INT_MASK_IMU,POZYX_INT_PIN0 ) == POZYX_FAILURE){
			 HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET); //czerwona

		 }
		 else {
			 if(regs[0] == (0x43>>1)){
			 HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET); // w przypadku gdyby sie nie uda³o powinna sie zapalic jedna z diod
			 }
			 else if (regs[0] == 0x00){
				 for(int i=0;i<10;i++){
					 HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
					 HAL_Delay(100);
					 HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_RESET);
					 HAL_Delay(100);
				 }
			 }
			else{
				for(int i=0;i<10;i++){
					HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(100);
					HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(100);
				}
		    }
		 }

	  while(1){
		  Pozyx.setLed(4,1);
		  vTaskDelay(100);
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


