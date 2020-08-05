#include "calendar.h"
#include <stdio.h>
#include <time.h>

#define DAYS 31
#define FLIGHT_CAPACITY 180

#define TRUE 1
#define FALSE 0

static Calendar FlightSchedule;

void initCalendar() {

	srand(time(NULL));

	for (int day = 1; day < DAYS + 1; day++) {

		for (int start = 0; start < 26; start++) {
			for (int dest = 0; dest < 26; dest++) {

				// when start is equal to dest, continue
				if (start == dest) {
					continue;
				}

				FlightSchedule[day][start][dest].departureTime = rand() % 1440;
				FlightSchedule[day][start][dest].cntReservedSeat = 0;
				FlightSchedule[day][start][dest].cntTotalSeat = FLIGHT_CAPACITY;
			}
		}
	}
}

int ValidateSelectFlight(int day, char source, char destination) {

	if (day < 1 || day > 31) {
		return FALSE;
	}

	if (source < 'a' || source > 'z' || destination < 'a' || destination > 'z') {
		return FALSE;
	}

	if (source == destination) {
		return FALSE;
	}

	return TRUE;
}

int GetDepartureTime(int day, char source, char destination) {
	
	if (ValidateSelectFlight(day, source, destination) == FALSE) {
		return FALSE;
	}

	return FlightSchedule[day][source][destination].departureTime;
}

int GetCountReservedSeat(int day, char source, char destination) {

	if (ValidateSelectFlight(day, source, destination) == FALSE) {
		return FALSE;
	}

	return FlightSchedule[day][source][destination].cntReservedSeat;
}

int GetCountFlightCapacity(int day, char source, char destination) {

	if (ValidateSelectFlight(day, source, destination) == FALSE) {
		return FALSE;
	}

	return FlightSchedule[day][source][destination].cntTotalSeat;
}

int GetStatusSeat(int day, char source, char destination, int seatNum) {

	if (ValidateSelectFlight(day, source, destination) == FALSE) {
		return FALSE;
	}

	return FlightSchedule[day][source][destination].statusSeats[seatNum];
}

int SetCountReservedSeat(int day, char source, char destination, int value) {

	if (ValidateSelectFlight(day, source, destination) == FALSE) {
		return FALSE;
	}

	FlightSchedule[day][source][destination].cntReservedSeat = value;
	return TRUE;
}

int SetStatusOfSeat(int day, char source, char destination, int seatNum, int value) {

	if (ValidateSelectFlight(day, source, destination) == FALSE) {
		return FALSE;
	}

	FlightSchedule[day][source][destination].statusSeats[seatNum] = value;
	return TRUE;
}