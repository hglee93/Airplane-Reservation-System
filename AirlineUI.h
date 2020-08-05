#pragma once
#include "rbtree.h"
#include "CommonType.h"

// Page ID
#define MENU 0
#define RESERVATION 1
#define FLIGHT_LIST 2
#define SEAT_INFO 3
#define RESERVATION_COMPLETE 4
#define RESERVATION_CANCLE 5
#define RESERVATION_SEARCH 6

#define FLIGHT_LIST_COL_LEN 8

// UI Message(like intent in Android Framework)
typedef struct {
	client client_info;
	int nextPage;
}Message;

// Time Convert Functions
int ConvertTimeStringToMinute(char* timeString);
int ConvertMinuteToTimeString(char* timeString, int minutes);

void CalTableWidthAndRowNum(/*input*/ int numSeats, int columnNum, int cellSize, /*output*/ int* tableWidth, int* rowNum, int* colNum);

// Print Stage
void PrintStage(char* stageName);

// Print Client infomation
void PrintReservationInfo(client cnt);

// Print seat table
void PrintSeats(int seatLevel, int* startSeatNum);

// Initialize Function
// Initialize Shortest path Structure, Database(Red-Black Tree)
void Initialize();

// UI Main function.
int MainFunction();

// Clear Input Buffer
void ClearInputBuffer();

// View Pages
Message MenuPage(Message input);
Message ReservationPage(Message input);
Message ReservationCanclePage(Message input);
Message ReservationCompletedPage(Message input);
Message FlightListPage(Message input);
Message SeatInfoPage(Message input);
Message SelectByReservationId(Message input);

typedef struct {
	void(*Run)();
}AirlineReservationSystem;