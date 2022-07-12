#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define BATT_ADD 0x3c
float vBat;

int main(int argc, char **argv){
	wiringPiSetupGpio();
	wiringPiI2CSetup(BATT_ADD);

	while(1){
		int r14 = wiringPiI2CRead(0x14);
		int r15 = wiringPiI2CRead(0x15);
		vBat = (((r15 << 8) | r14) & 0xFFF)*0.0012;
		printf(vBat);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

}
