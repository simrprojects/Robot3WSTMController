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
sensor_raw_t sensor_raw;
int16_t acceleration[3];
uint32_t press;

device_range_t range;
device_range_t range2;
//uint16_t destinationid1 = 0x6716 ;
//uint16_t destinationid2 = 0x6e3d ;
uint32_t d;
uint32_t d2;

void All_begin(void){
	 xTaskCreate(PozyxTask,"pozyx", 200,0, 1, &PozyxTaskHandle);
}

 void PozyxTask(void * argument){

	 Pozyx.begin(false, MODE_INTERRUPT, POZYX_INT_MASK_POS, POZYX_INT_PIN1);
	 Pozyx.getRawSensorData(&sensor_raw);

	  while(1){
		  //////////////////////////////////////////////////////////
		  Pozyx.getRawSensorData(&sensor_raw);
		  acceleration[0] = sensor_raw.acceleration[0];
		  acceleration[1] = sensor_raw.acceleration[1];
		  acceleration[2] = sensor_raw.acceleration[2];
		  press = sensor_raw.pressure;
		  ///////////////////////////////////////////////////////////
		  ///// TEST MIERZENIA ODLEG£OSCI

		  if(Pozyx.doRanging(POZYX_ANCHOR_ADDRESS_1, &range)){
			  d = range.distance;
			  Pozyx.setLed(3,1);
		  }
		  else Pozyx.setLed(3,0);

		  if(Pozyx.doRemoteRanging(POZYX_ANCHOR_ADDRESS_1,POZYX_ANCHOR_ADDRESS_2, &range2)){
			  d2 = range2.distance;
			  Pozyx.setLed(4,1);
		  }
		  else Pozyx.setLed(4,0);
		  //////////////////////////////////////////////////////////////




		  vTaskDelay(100);
	  	  }
 }






