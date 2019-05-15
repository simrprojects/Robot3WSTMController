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




