#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>

#include "AirlineUI.h"
#include "graph.h"
#include "calendar.h"

#define PRESTIGE_SEAT 0
#define BUSINESS_SEAT 1
#define ECONOMY_SEAT 2

// Time Convert Function(String -> int)
int ConvertTimeStringToMinute(char* timeString) {

	if (strlen(timeString) != 5) {
		return -1;
	}

	char* header = timeString;

	while (*header != '\0' && *header != ':') {
		header++;
	}

	if (*header == '\0') {
		return -1;
	}

	int hour = 0, minutes = 0;

	hour += (*(header - 2) - '0') * 10;
	hour += (*(header - 1) - '0');

	minutes += (*(header + 1) - '0') * 10;
	minutes += (*(header + 2) - '0');

	return (hour * 60) + minutes;
}

// Time Convert Function(int -> String)
int ConvertMinuteToTimeString(char* timeString, int minutes) {

	if (minutes < 0 || minutes > 1440) {
		return 0;
	}

	int hh = minutes / 60;
	int mm = minutes % 60;

	timeString[0] = hh / 10 + '0';
	timeString[1] = hh % 10 + '0';
	timeString[2] = ':';
	timeString[3] = mm / 10 + '0';
	timeString[4] = mm % 10 + '0';
	timeString[5] = '\0';

	return 1;
}

// Print Stage
void PrintStage(char* stageName) {
	int strLen = strlen(stageName);
	for (int i = 0; i < strLen + 4; i++) { printf("*"); }
	printf("\n* %s *\n", stageName);
	for (int i = 0; i < strLen + 4; i++) { printf("*"); }
	printf("\n");
}

// Print Client infomation
void PrintReservationInfo(client cnt) {

	printf("\n< Reservation Infomation >\n");

	if (cnt.name[0] != 0) {
		printf("Name : %s\n", cnt.name);
	}
	if (cnt.source != 0) {
		printf("Source : %c\n", cnt.source);
	}

	if (cnt.destination != 0) {
		printf("Destination : %c\n", cnt.destination);
	}

	if (cnt.sdate != 0 && cnt.stime != 0) {
		char timeString[6] = { 0, };
		ConvertMinuteToTimeString(timeString, cnt.stime);
		printf("Departure time : Day %d %s\n", cnt.sdate, timeString);
	} else if (cnt.sdate != 0) {
		printf("Departure Day : %d\n", cnt.sdate);
	}

	if (cnt.adate != 0 && cnt.etime != 0) {
		char timeString[6] = { 0, };
		ConvertMinuteToTimeString(timeString, cnt.etime);
		printf("Arrive time : Day %d %s\n", cnt.adate, timeString);
	} else if (cnt.adate != 0) {
		printf("Arrive Day : %d\n", cnt.adate);
	}

	if (cnt.time != 0) {
		char timeString[6] = { 0, };
		ConvertMinuteToTimeString(timeString, cnt.time);
		printf("Flight Time : %s\n", timeString);
	}

	if (cnt.seat != 0) {
		printf("Seat : %d\n", cnt.seat);
	}

	if (cnt.price != 0) {
		printf("Price : %d만원\n", cnt.price / 10000);
	}

	if (cnt.routeInfo.top != 0) {
		printf("Route : ");
		for (int i = cnt.routeInfo.top; i >= 0; i--) {
			printf(" %c ", 'a' + cnt.routeInfo.path[i]);
			if (i != 0) {
				printf("->");
			}
		}
		printf("\n");
	}

	printf("\n");
}

// Print Seat table
void PrintSeats(int seatLevel, int* startSeatNum, client cnt) {

	const int COLUMN_NUM = 20;
	const int CELL_SIZE = 6;

	int cntTotalSeat = 0;

	switch (seatLevel) {
	case PRESTIGE_SEAT:
		cntTotalSeat = 4;
		printf("\n");
		printf("[Prestige]");
		printf("\n");
		break;
	case BUSINESS_SEAT:
		cntTotalSeat = 16;
		printf("\n");
		printf("[Business]");
		printf("\n");
		break;
	case ECONOMY_SEAT:
		cntTotalSeat = 160;
		printf("\n");
		printf("[Economy]");
		printf("\n");
		break;
	}

	int rowNum = 0;
	int colNum = 0;
	int tableWidth = 0;

	// Calculate table widht and row count.
	CalTableWidthAndRowNum(cntTotalSeat, COLUMN_NUM, CELL_SIZE, &tableWidth, &rowNum, &colNum);

	// Print seats
	for (int i = 0; i < tableWidth; i++) { printf("-"); }
	printf("\n");

	for (int r = 0; r < rowNum; r++) {
		printf("|");
		for (int i = 0; i < colNum; i++) {
			printf(" %3d |", (*startSeatNum)++);
		}
		printf("\n");

		printf("|");
		for (int i = 0; i < colNum; i++) {
			int status = GetStatusSeat(cnt.sdate, cnt.source, cnt.destination, (*startSeatNum) - colNum + i);
			if (status == 0) {
				printf("( E )|");
			}
			else {
				printf("     |");
			}
		}
		printf("\n");

		// Print below line.
		for (int i = 0; i < tableWidth; i++) { printf("-"); }
		printf("\n");
	}
}

// Initailize Graph, RB Tree
void Initialize() {

	// ReservationRecords Initialize.
	ReservationRecords = T_NIL;
	T_NIL->color = BLACK;

	// Graph Initialize
	InitGraph();

	// Initialize Calendar
	initCalendar();
}

// UI Main function.
int MainFunction() {

	system("mode con cols=150 lines=50");
	system("cls");

	// Red-Black Tree, Graph Initialize
	Initialize();

	Message clientAction;
	memset(&clientAction, 0x00, sizeof(Message));

	while (1) {
		switch (clientAction.nextPage) {
		case MENU:
			clientAction = MenuPage(clientAction);
			break;
		case RESERVATION:
			clientAction = ReservationPage(clientAction);
			break;
		case FLIGHT_LIST:
			clientAction = FlightListPage(clientAction);
			break;
		case SEAT_INFO:
			clientAction = SeatInfoPage(clientAction);
			break;
		case RESERVATION_COMPLETE:
			clientAction = ReservationCompletedPage(clientAction);
			break;
		case RESERVATION_CANCLE:
			clientAction = ReservationCanclePage(clientAction);
			break;
		case RESERVATION_SEARCH:
			clientAction = SelectByReservationId(clientAction);
			break;
		}

	}

	return 0;
}

void CalTableWidthAndRowNum(/*input*/ int numSeats, int columnNum, int cellSize, /*output*/ int* tableWidth, int* rowNum, int* colNum) {

	// case 1. the number of seats is less than column count.
	if (numSeats / columnNum == 0) {
		*rowNum = 1;
		*tableWidth = (numSeats % columnNum) * cellSize;
		*colNum = numSeats;
	}
	// case 2. the number of seats is larger than column count.
	else {
		*rowNum = numSeats / columnNum;
		*tableWidth = columnNum * cellSize;
		*colNum = columnNum;
	}
}

// Clear Input Buffer
// this function solves newline character remained problem
// whenever user inserts infomation.
void ClearInputBuffer() {
	int c;
	while (!((c = getchar()) == '\n')) {}
}

// 메뉴 화면
Message MenuPage(Message input) {

	int command = 0;

	Message output;
	memcpy(&output, &input, sizeof(Message));

	system("cls");
	PrintStage("MENU");
	printf("[1] 항공권 예약\n");
	printf("[2] 항공권 예약 취소\n");
	printf("[3] 항공권 조회\n");
	printf("입력 : ");
	scanf("%d", &command);

	if (command == 1) {
		output.nextPage = RESERVATION;
	}
	else if(command == 2){
		output.nextPage = RESERVATION_CANCLE;
	}
	else {
		output.nextPage = RESERVATION_SEARCH;
	}

	return output;
}

// 예약 화면
Message ReservationPage(Message input){

	char name[50] = { 0, };
	char start[2] = { 0, };
	char dest[2] = { 0, };
	int date = 0;

	Message output;
	memcpy(&output, &input, sizeof(Message));

	// 화면 클리어
	system("cls");
	PrintStage("항공권 조회");

	// clear Input Buffer.
	ClearInputBuffer();
	printf("[1] 이름 입력 : "); gets(name);
	printf("[2] 출발지 : "); scanf("%s", start);
	printf("[3] 도착지 : "); scanf("%s", dest);
	printf("[4] 날짜 : "); scanf("%d", &date);

	memcpy(output.client_info.name, name, strlen(name) + 1);
	output.client_info.source = start[0];
	output.client_info.destination = dest[0];
	output.client_info.sdate = date;

	output.nextPage = FLIGHT_LIST;

	return output;
}

// 예약 취소
Message ReservationCanclePage(Message input) {

	system("cls");
	PrintStage("예약 취소");

	int cmd = 0;
	printf("예약 번호 입력 : ");
	scanf("%d", &cmd);

	RB_DELETE(&ReservationRecords, cmd);

	printf("예약 취소 완료");

	int exit;
	printf("\n메뉴화면으로 돌아가기(-1 입력) ");
	scanf("%d", &exit);

	Message output;
	memset(&output, 0x00, sizeof(Message));
	output.nextPage = MENU;
	return output;
}

// 예약 완료 화면
Message ReservationCompletedPage(Message input) {

	system("cls");
	PrintStage("결과 화면");

	// Reservation Transaction.
	// 1. Insert Reservation Infomation to Red-Black Tree
	RB_INSERT(&ReservationRecords, reservationNumber++, input.client_info);

	int departureDay = input.client_info.sdate;
	char source = input.client_info.source;
	char dest = input.client_info.destination;
	
	// 2. Update Count of the reservation Seat in the Filght structure.
	int cntReservationSeat = GetCountReservedSeat(departureDay, source, dest);
	SetCountReservedSeat(departureDay, source, dest, cntReservationSeat + 1);

	// 3. Update Status of the Seat in the Filght structure.
	int seatNum = input.client_info.seat;
	SetStatusOfSeat(departureDay, source, dest, seatNum, 1);

	int exit;
	printf("\nNumber %d Reservation Complete!", reservationNumber - 1);
	
	PrintReservationInfo(input.client_info);
	printf("\n메뉴화면으로 돌아가기(-1 입력) ");
	scanf("%d", &exit);

	Message output;
	memset(&output, 0x00, sizeof(Message));

	if (exit == -1) {
		output.nextPage = MENU;
	}

	return output;
}

// 좌석 선택 화면
Message SeatInfoPage(Message input) {
	
	system("cls");
	PrintStage("좌석 선택");

	int seat = 1;

	printf("\n( E )는 빈좌석\n");

	// Prestige seat level : 4 seats (Seat 1 ~ 4)
	// Print prestige seats
	PrintSeats(PRESTIGE_SEAT, &seat, input.client_info);

	// Business seat level : 16 seats (Seat 5 ~ 20)
	// Print business seats
	PrintSeats(BUSINESS_SEAT, &seat, input.client_info);

	// Economy seat level : 180 seats (Seat 21 ~ 180)
	// Print Economy seats
	PrintSeats(ECONOMY_SEAT, &seat, input.client_info);

	// Input seat number from user.
	int seatNum = 0;
	printf("좌석 선택 입력 : ");
	scanf("%d", &seatNum);

	Message output;
	memcpy(&output, &input, sizeof(Message));

	// Set seat number
	output.client_info.seat = seatNum;

	// Set Price
	int dist = output.client_info.time / 12;
	if (seatNum >= 1 && seatNum <= 4) {
		output.client_info.price = dist * 60000;
	}
	else if (seatNum >= 5 && seatNum <= 20) {
		output.client_info.price = dist * 30000;
	}
	else {
		output.client_info.price = dist * 10000;
	}

	// Set nextPage
	output.nextPage = RESERVATION_COMPLETE;

	return output;
}

// 항공편 선택
Message FlightListPage(Message input) {

	system("cls");
	PrintStage("항공편 선택");

	Message output;
	memcpy(&output, &input, sizeof(Message));

	// 항공편, 출발지, 도착지, 출발날짜, 출발시각, 도착시각, 비행시간, 좌석수
	char* head[FLIGHT_LIST_COL_LEN] = {"출발지", "도착지" , "출발날짜" , "출발시각" , "도착날짜", "도착시각" , "비행시간" , "잔여석" };
	int headWidth[FLIGHT_LIST_COL_LEN] = { 0, };

	int tableWidth = 0;
	for (int i = 0; i < FLIGHT_LIST_COL_LEN; i++) {
		headWidth[i] = strlen(head[i]);
		tableWidth += headWidth[i] + 2;
	}

	tableWidth += 9;

	for (int i = 0; i < tableWidth; i++) { printf("-"); }
	printf("\n");

	printf("|");
	for (int i = 0; i < FLIGHT_LIST_COL_LEN; i++) {
		printf(" %s |", head[i]);
	}
	printf("\n");

	for (int i = 0; i < tableWidth; i++) { printf("-"); }
	printf("\n");

	// 항공 경로 저장
	Routing routeInfo;

	int startTime = GetDepartureTime(input.client_info.sdate, input.client_info.source, input.client_info.destination);
	int arriveTime = calArriveTime(input.client_info.source, input.client_info.destination, startTime, &routeInfo);
	int flightTime = arriveTime - startTime;

	// Calculate arriveTime
	// And Update departureDate, arriveDate
	output.client_info.adate = output.client_info.sdate + (arriveTime / 1440);
	arriveTime = arriveTime % 1440;

	// 1. Print Flight list
	// Print Source, Destination
	printf("|");
	printf("    %c   |", input.client_info.source);
	printf("    %c   |", input.client_info.destination);

	// Print departure time
	char strStartTime[6] = { 0, };
	ConvertMinuteToTimeString(strStartTime, startTime);
	printf("  Day %02d  |", input.client_info.sdate);
	printf("   %s  |", strStartTime);

	// Print arrive time
	char strArriveTime[6] = { 0, };
	ConvertMinuteToTimeString(strArriveTime, arriveTime);
	printf("  Day %02d  |", output.client_info.adate);
	printf("   %s  |", strArriveTime);
	
	// Print Flight time
	char strFlightTime[6] = { 0, };
	ConvertMinuteToTimeString(strFlightTime, flightTime);
	printf("   %s  |", strFlightTime);

	// Print remained seat count.
	int cntRemainedSeat 
		= GetCountFlightCapacity(input.client_info.sdate, input.client_info.source, input.client_info.destination)
		- GetCountReservedSeat(input.client_info.sdate, input.client_info.source, input.client_info.destination);
	printf("   %d  |", cntRemainedSeat);
	printf("\n");

	for (int i = 0; i < tableWidth; i++) { printf("-"); }
	printf("\n");

	char inputTime[6] = { 0, };

	while (1) {

		// Print current reservation infomation.
		PrintReservationInfo(input.client_info);

		printf("출발시각 입력(HH:MM) : ");
		scanf_s("%s", inputTime, sizeof(inputTime));

		if (*inputTime == NULL) {
			printf("출발시각을 다시 입력하세요.");
		}
		else {
			output.client_info.stime = ConvertTimeStringToMinute(inputTime);
			output.client_info.etime = arriveTime;
			output.client_info.time = flightTime;
			output.client_info.routeInfo = routeInfo;
			output.nextPage = SEAT_INFO;
			break;
		}
	}

	return output;
}

// 항공편 조회
Message SelectByReservationId(Message input) {
	system("cls");
	PrintStage("항공편 조회");

	int reservationId = 0;
	printf("예약 번호 입력 : ");
	scanf("%d", &reservationId);

	PRINT_INFO(&ReservationRecords, reservationId);

	int exit = 0;
	printf("\n메뉴화면으로 돌아가기(-1 입력) ");
	scanf("%d", &exit);

	Message output;
	memset(&output, 0x00, sizeof(Message));

	if (exit == -1) {
		output.nextPage = MENU;
	}

	return output;
}