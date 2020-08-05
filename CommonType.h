#pragma once
#include "graph.h"

typedef struct client {
	char name[50]; //�̸�
	char source; //�����
	char destination; //������
	int sdate; // ��߳�¥(1~31)
	int adate; // ������¥(1~31)
	int seat; //�¼���ȣ(1~50) 1~5, 6~15, 16~50
	int stime; //��� �ð�(0~1440)
	int etime; //���� �ð�(0~1440)
	int time; //���� �ð�(0~1440 ������ ����)
	int price; // Ƽ�� ����(100km �� 6����, 100km �� 3����, 100km �� 1����)
	Routing routeInfo;	// ���� ��� ����
}client;