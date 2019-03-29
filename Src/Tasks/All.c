/*
 * All.c
 *
 *  Created on: 27.03.2019
 *      Author: Igor
 */
//#include "iwdg.h"
//#include "wwdg.h"

#include "cmsis_os.h"
#include "All.h"
// wszystkie heddery klas

//osThreadId GyroTaskHandle;
//dodanie w¹tków ka¿dej klasy

//void StartGyroTask(void const * argument);
//dodanie wszystkich funkcji startowych do klas

void All_begin(void) {
	//osThreadDef(FutabaTask, StartFutabaTask, osPriorityHigh, 0, 256);
	//FutabaTaskHandle = osThreadCreate(osThread(FutabaTask), NULL);
	//definicja kazdego taska (do kazdej klasy)

}

/*void StartGyroTask(void const * argument){
 * futaba.Init();
	for (;;) {
		futaba.Process();
	}
	// definicja kazdej z funkcji startowych
	 * tutaj przyk³ad, ale mo¿na na wiele sposobów
 *
}
*/
