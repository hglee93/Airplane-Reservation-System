#pragma once
#include "graph.h"

typedef struct client {
	char name[50]; //이름
	char source; //출발지
	char destination; //목적지
	int sdate; // 출발날짜(1~31)
	int adate; // 도착날짜(1~31)
	int seat; //좌석번호(1~50) 1~5, 6~15, 16~50
	int stime; //출발 시간(0~1440)
	int etime; //도착 시간(0~1440)
	int time; //비행 시간(0~1440 분으로 저장)
	int price; // 티켓 가격(100km 당 6만원, 100km 당 3만원, 100km 당 1만원)
	Routing routeInfo;	// 비행 경로 저장
}client;