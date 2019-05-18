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

void All_begin(void){
	 xTaskCreate(PozyxTask,"pozyx", 200,0, 1, &PozyxTaskHandle);
}

 void PozyxTask(void * argument){

	 Pozyx.begin(false, MODE_POLLING, POZYX_INT_MASK_IMU);
	 Pozyx.getRawSensorData(&sensor_raw);

	  while(1){
		  Pozyx.getRawSensorData(&sensor_raw);
		  acceleration[0] = sensor_raw.acceleration[0];
		  acceleration[1] = sensor_raw.acceleration[1];
		  acceleration[2] = sensor_raw.acceleration[2];
		  press = sensor_raw.pressure;
		  Pozyx.setLed(4,1);
		  Pozyx.setLed(2,1);
		  vTaskDelay(100);
	  	  }
 }




