#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

int calArriveTime(char source, char dest, int startTime, /*OUT*/ Routing* routeInfo) {

	int srcNum = source - 'a';
	int destNum = dest - 'a';

	Routing log = Path(&graph, srcNum, destNum);

	// 항공 경로 저장
	routeInfo->path = log.path;
	routeInfo->top = log.top;

	return FlightTime(startTime, dist[destNum]);
}

void InitGraph() {
	CreateGraph(&graph);
}

void CreateGraph(Graph* pgraph) {
	int cnt_path = 0;
	srand(time(NULL));

	pgraph->num = city_num; // from a to z
	pgraph->heads = (City**)malloc(sizeof(City*)*city_num);

	for (int i = 0; i < city_num; i++) { // create Cities
		pgraph->heads[i] = (City*)malloc(sizeof(City));
		pgraph->heads[i]->c = 'a' + i;
		pgraph->heads[i]->next = NULL;
		pgraph->heads[i]->x = rand() % 6001 - 3000; // the range of x is from 0 to E3000km or W3000km -> E:(+), W:(-) 
		pgraph->heads[i]->y = rand() % 6001 - 3000; // the range of y is from 0 to N3000km or S3000km -> N:(+), S:(-)
	}

	for (int i = 0; i < city_num; i++) { // initialize the distance matrix of cities
		for (int j = 0; j < city_num; j++) {
			if (i != j)
				city_matrix[i][j] = 0;
			else
				city_matrix[i][j] = -1;
		}
	}

	while (cnt_path < 100) { // There is 100 direct paths between two cities
		int s = -1, d = -1;
		while (s == d) {
			s = rand() % 26;
			d = rand() % 26;
		}

		if (city_matrix[s][d] == 0) { // Not connected
			double dis;

			int dif_x, dif_y, tmp;
			dif_x = (pgraph->heads[s]->x) - (pgraph->heads[d]->x);
			dif_y = (pgraph->heads[s]->y) - (pgraph->heads[d]->y);
			dis = dif_x * dif_x + dif_y * dif_y;
			dis = pow(dis, 0.5);

			city_matrix[s][d] = (int)dis;
			city_matrix[d][s] = (int)dis;

			Connect(pgraph, s, d); //Let's connect
			cnt_path++;
		}

	}
	/*
	for (int i = 0; i < city_num; i++) {
		for (int j = 0; j < city_num; j++)
			printf("%d ", city_matrix[i][j]);

		puts("");
	}
	*/
	for (int i = 0; i < city_num; i++) {
		for (int j = 0; j < city_num; j++) {
			switch (city_matrix[i][j]) {
			case 0:
				city_matrix[i][j] = INF; break;
			case -1:
				city_matrix[i][j] = 0; break;
			}
		}
	}
}

void Connect(Graph* pgraph, char src, char dest) {
	City* node1, *node2;
	node1 = (City*)malloc(sizeof(City));
	node1->c = dest;
	node1->next = NULL;
	City* cur = pgraph->heads[src];

	while (cur->next != NULL)
		cur = cur->next;
	cur->next = node1;

	node2 = (City*)malloc(sizeof(City));
	node2->c = src;
	node2->next = NULL;
	cur = pgraph->heads[dest];

	while (cur->next != NULL)
		cur = cur->next;
	cur->next = node2;
}

void PrintGraph(Graph* pgraph) {
	char city;
	City* cur;
	for (int i = 0; i < city_num; i++) {
		cur = pgraph->heads[i];
		printf("City %c is connected ... \n%c ", 'a' + i, 'a' + i);
		while (cur->next != NULL) {
			printf("-> %c ", cur->next->c + 'a');
			cur = cur->next;
		}
		puts("");
	}
}

Routing Path(Graph* pgraph, char src, char dest) {
	int i, j;

	int q[city_num], size = city_num;
	int p[city_num];

	for (i = 0; i < city_num; i++) { //initialize
		dist[i] = INF;
		q[i] = 0;
		p[i] = 0;
	}

	dist[src] = 0;
	int u = 0;
	while (size != 0) {
		int min_dst = INF;
		int tmp;

		for (int j = 0; j < city_num; j++) {
			if (q[j] == 0 && dist[j] < min_dst) {
				min_dst = dist[j];
				u = j;
			}
		}
		q[u] = 1;
		size--;

		for (int j = 0; j < city_num; j++) {
			if (dist[j] > dist[u] + city_matrix[u][j]) {
				dist[j] = dist[u] + city_matrix[u][j];
				p[j] = u;
			}
		}
		if (u == dest)
			break;
	}

	int top = 0, p_idx;
	int log[city_num], chk[city_num];
	Routing output;

	for (int i = 0; i < city_num; i++) {
		log[i] = 0;
	}
	for (int i = 0; i < city_num; i++) {
		for (int j = 0; j < city_num; j++)
			chk[j] = 0;
		top = 0;
		p_idx = i;
		if (p_idx != src) {
			if (q[i] > 0) {
				do {
					log[top++] = p_idx;
					p_idx = p[p_idx];
				} while (p_idx != src);

				log[top] = p_idx;
				int tmp = top;
				while (tmp >= 0) {
					chk[log[tmp]]++;
					tmp--;
				}
				if (chk[dest] != 0) {
					output.path = (int*)calloc(city_num, sizeof(int));
					output.top = top;
					while (top >= 0) {
						output.path[top] = log[top--];
					}
				}

			}
		}
	}

	return output;
}

int FlightTime(int minute, int distance) {
	//flight speed is 500km/h
	// int minute : start time
	double time = (double)distance / 500 * 60;
	return minute + (int)time;
}