#include <stdio.h>
#include "AirlineUI.h"

int main() {
	AirlineReservationSystem ars;
	ars.Run = MainFunction();
	ars.Run();
	return 0;
}