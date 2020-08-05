#pragma once

// Initailize Calendar;
void initCalendar();

int ValidateSelectFlight(int day, char source, char destination);

int GetDepartureTime(int day, char source, char destination);

int GetCountReservedSeat(int day, char source, char destination);

int GetCountFlightCapacity(int day, char source, char destination);

int GetStatusSeat(int day, char source, char destination, int seatNum);

// return value
// - 1 is true (success)
// - 0 is false (fail)
int SetCountReservedSeat(int day, char source, char destination, int value);

typedef struct {
	int departureTime;
	int cntReservedSeat;
	int cntTotalSeat;
	int statusSeats[181];
}Flight;

typedef Flight Schedule[26][26];

typedef Schedule Calendar[32];

