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

//////zmiennne testowe////////////
uint8_t regs[3],selftest;
sensor_raw_t sensor_raw;
int16_t acceleration[3];
uint32_t press;

device_range_t range;
device_range_t range2;

uint32_t d;
uint32_t d2;

coordinates_t position;

int32_t x;
int32_t y;
int32_t z;

uint8_t errcode = 0;
////////


///////////////////////////////

void All_begin(void){
	xTaskCreate(PozyxTask,"pozyx", 200,0, 1, &PozyxTaskHandle);
}

void PozyxTask(void * argument){

	Pozyx.begin(false, MODE_INTERRUPT, POZYX_INT_MASK_POS, POZYX_INT_PIN1);


	/////////////POZYCJONOWANIE///////////////////
	//	const int num_tags = 3;									// w przypadku u¿ycia wielu tagów
	//	uint16_t tags[num_tags] = {0x0001, 0x0002, 0x0003};
	//	uint16_t tag = 0x0001;

	uint16_t remote_id = 0x6763;

	const uint16_t num_anchors = 3;
	uint16_t anchors[num_anchors] = {POZYX_ANCHOR_ADDRESS_1, POZYX_ANCHOR_ADDRESS_2, POZYX_ANCHOR_ADDRESS_3};
	int32_t anchors_x[num_anchors] = {-2930, 760, 0};
	int32_t anchors_y[num_anchors] = {0, 0, -2940};
	int32_t heights[num_anchors] = {0, 0, 0};


	uint8_t dimension = POZYX_2D;

	Pozyx.clearDevices(remote_id);
	Pozyx.setAnchorsManual(num_anchors,anchors ,anchors_x, anchors_y, heights, remote_id);
	Pozyx.setTagsAlgorithm(POZYX_POS_ALG_UWB_ONLY, dimension);
/////////////////////////////////////////////////////////////////////////////////////


	while(1){
		//////////////ODCZYT Z CZUJNIKÓW Z SHIELDA////////////////////////////////////////////
		Pozyx.getRawSensorData(&sensor_raw);
		acceleration[0] = sensor_raw.acceleration[0];
		acceleration[1] = sensor_raw.acceleration[1];
		acceleration[2] = sensor_raw.acceleration[2];
		press = sensor_raw.pressure;
		///////////////////////////////////////////////////////////

		///////////TEST MIERZENIA ODLEG£OSCI/////////////////////////

		if(Pozyx.doRanging(POZYX_ANCHOR_ADDRESS_1, &range)){
			d = range.distance; // odleg³osc shielda od anchor'a
			Pozyx.setLed(3,1);
		}
		else Pozyx.setLed(3,0);

		if(Pozyx.doRemoteRanging(POZYX_ANCHOR_ADDRESS_3,POZYX_ANCHOR_ADDRESS_1, &range2)){
			d2 = range2.distance; // odleg³osc jednego anchor'a od drugiego
			Pozyx.setLed(4,1);
		}
		else Pozyx.setLed(4,0);
		//////////////////////////////////////////////////////////////

		/////////////TEST POZYCJONOWANIA/////////////////////////////////

		uint8_t status = Pozyx.doPositioning(&position, dimension);

		Pozyx.getErrorCode(&errcode);
		if(status == POZYX_SUCCESS){

			HAL_GPIO_TogglePin(GPIOB,LD2_Pin);

			x = position.x;
			y = position.y;
			z = position.z;
		}
		else{
			HAL_GPIO_TogglePin(GPIOB,LD3_Pin);
		}


		vTaskDelay(10);
	}
}






