/*
 * All.h
 *
 *  Created on: 12.04.2019
 *      Author: Igor
 */

#ifndef TASKS_ALL_H_
#define TASKS_ALL_H_

#ifdef __cplusplus
extern "C"{
#endif



#include "cmsis_os.h"

void All_begin(void);


//extern osThreadId PozyxTaskHandle;
extern xTaskHandle  PozyxTaskHandle;


#ifdef __cplusplus
}
#endif


#endif /* TASKS_ALL_H_ */
