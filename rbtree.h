#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "CommonType.h"

#define RED      'R'
#define BLACK   'B'

#define RANDOM_SEAT   1
#define SELECT_SEAT   2

typedef struct node {
	int data; //예약번호
	char color;
	struct node* left, *right, *parent;
	client *passenger;
	//key에 해당하는 client struct 추가 생성
}node;

struct node T_NIL_NODE;
static node* T_NIL = &T_NIL_NODE;
static node* ReservationRecords = NULL;
static int reservationNumber = 1;