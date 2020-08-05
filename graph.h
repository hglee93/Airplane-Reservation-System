#pragma once

#define city_num 26
#define INF 2100000000

typedef struct _City {
	char c;
	int x, y;
	struct _City* next;
} City;

typedef struct {
	int num;
	City** heads;
} Graph;

typedef struct {
	int* path;
	int top;
} Routing;

void CreateGraph(Graph* pgraph);
void Connect(Graph* pgraph, char src, char dest);
void InitGraph();
void PrintGraph(Graph* pgraph);
Routing Path(Graph* pgraph, char src, char dest);
int FlightTime(int minute, int distance);
int calArriveTime(char source, char dest, int startTime, /*OUT*/ Routing* routeInfo);

static int city_matrix[city_num][city_num];
static int dist[city_num];
static int visit[city_num];
static Graph graph;