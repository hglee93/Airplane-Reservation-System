#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rbtree.h"

client* newpsg(int data) {
	client* temp = (client*)malloc(sizeof(client));
	
	//이름
	int i;
	printf("name: ");
	char name[20];
	scanf("%s", name);
	for (i = 0; name[i] != '\0'; i++) {
		temp->name[i] = name[i];
	}
	temp->name[i + 1] = '\0';
	
	/*
	//source
	char source;
	printf("출발지: ");
	scanf("%c", &source);
	temp->source = source;

	//destination
	printf("목적지: ");
	char destination;
	scanf("%c", &destination);
	temp->destination = destination;

	//date
	int date = 0;
	printf("출발 날짜: ");
	scanf("%d", &date);
	temp->date = date;

	//stime
	int stime = 0;
	printf("출발 예상 시간: ");
	scanf("%d", &stime);
	temp->stime = stime;

	//etime, time
	int etime = 600;
	temp->etime = 600;

	temp->time = (etime-stime);
	*/

	//자리 지정
	/*printf("seat number>> type 1: random, type 2: select\n");
	int num;
	scanf("%d", &num);
	srand((int)time(NULL));
	if (num == 1) {
		temp->seat = rand() % 50 + 1;
	}
	else if (num == 2) {
		printf("what number do you want?(1~50)\n");
		int seatnum;
		scanf("%d", &seatnum);
		temp->seat = seatnum;
	}

	temp->source = 'a';
	temp->destination = 'z';
	temp->date = 3;
	temp->stime = 200;
	temp->etime = 600;
	temp->time = (temp->etime) - (temp->stime);*/
	return temp;
}

node* newNode(int data, client cntInfo) { //data==예약 번호

	node* temp = (node*)malloc(sizeof(node));
	if (temp == NULL) return -1;
	temp->data = data;
	temp->color = RED;
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	temp->passenger = (client*)malloc(sizeof(client));
	memcpy(temp->passenger, &cntInfo, sizeof(client));

	return temp;
}

void rotateLeft(node** root, node* x) {
	node* y = x->right;
	x->right = y->left;

	if (y->left != T_NIL) y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == T_NIL) *root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void rotateRight(node** root, node* y) {
	node *x = y->left;
	y->left = x->right;

	if (x->right != T_NIL) x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == T_NIL) *root = x;
	else if (y == y->parent->right) y->parent->right = x;
	else y->parent->left = x;
	x->right = y;
	y->parent = x;
}

void InsertFixup(node** root, node* new) {
	node *temp;
	while (new->parent->color == RED) {
		if (new->parent == new->parent->parent->left) {
			temp = new->parent->parent->right;
			if (temp->color == RED) {
				new->parent->color = BLACK;
				temp->color = BLACK;
				new->parent->parent->color = RED;
				new = new->parent->parent;
			}
			else {
				if (new == new->parent->right) {
					new = new->parent;
					rotateLeft(root, new);
				}
				new->parent->color = BLACK;
				new->parent->parent->color = RED;
				rotateRight(root, new->parent->parent);
			}
		}
		else {
			temp = new->parent->parent->left;
			if (temp->color == RED) {
				new->parent->color = BLACK;
				temp->color = BLACK;
				new->parent->parent->color = RED;
				new = new->parent->parent;
			}
			else {
				if (new == new->parent->left) {
					new = new->parent;
					rotateRight(root, new);
				}
				new->parent->color = BLACK;
				new->parent->parent->color = RED;
				rotateLeft(root, new->parent->parent);
			}
		}
	}
	root[0]->color = BLACK;
}

void* RB_INSERT(node** root, int data, client clientInfo) {

	node* new = newNode(data, clientInfo);
	node* y = T_NIL;
	node* x = *root;

	while (x != T_NIL) {
		y = x;
		if ((new->data) < (x->data)) x = x->left;
		else x = x->right;
	}

	new->parent = y;

	if (y == T_NIL) {
		*root = new;
	}
	else if ((new->data) < (y->data)) {
		y->left = new;
	}
	else {
		y->right = new;
	}

	new->left = T_NIL;
	new->right = T_NIL;
	new->color = RED;

	InsertFixup(root, new);
}

void Tree_Transplant(node** root, node* t, node* c) {
	if (t->parent == T_NIL) *root = c;
	else if (t == t->parent->left) (t->parent)->left = c;
	else (t->parent)->right = c;
	c->parent = t->parent;
}

void DeleteFixup(node** root, node* x) {
	node* sibling = NULL;
	while ((x != *root) && (x->color == BLACK)) {
		if (x == x->parent->left) {
			sibling = x->parent->right;

			//case 1: x's sibling is red
			if (sibling->color == RED) {
				sibling->color = BLACK;
				(x->parent)->color = RED;
				rotateLeft(root, x->parent);
				sibling = (x->parent)->right;
			}

			//case2: x's sibling is black, and both of sibling's children are black
			if ((sibling->left->color == BLACK) && (sibling->right->color == BLACK)) {
				sibling->color = RED;
				x = x->parent;
			}

			//case3: x's sibling is black, sibling's left childe is red, another is black.
			else if (((sibling->left)->color == RED) && ((sibling->right)->color == BLACK)) {
				sibling->color = RED;
				(sibling->left)->color = BLACK;
				rotateRight(root, sibling);
				sibling = (x->parent)->right;
			}

			//case4: x's sibling is black, sibling's right child is red.
			else if ((sibling->right)->color == RED) {
				sibling->color = (x->parent)->color;
				(sibling->right)->color = BLACK;
				(x->parent)->color = BLACK;
				rotateLeft(root, x->parent);
				x = *root;
			}
		}

		else {
			sibling = x->parent->left;

			//case1: x's sibling is red
			if (sibling->color == RED) {
				sibling->color = BLACK;
				x->parent->color = RED;
				rotateRight(root, x->parent);
				sibling = x->parent->left;
			}

			//case2: x's sibling is black, and both of sibling children is black.
			if (((sibling->left)->color == BLACK) && ((sibling->right)->color == BLACK)) {
				sibling->color = RED;
				x = x->parent;
			}

			//case3: x's sibling is black, sibling is right child is red, another is black.
			else if ((sibling->right->color == RED) && (sibling->left->color == BLACK)) {
				sibling->color = RED;
				sibling->right->color = BLACK;
				rotateLeft(root, sibling);
				sibling = x->parent->left;
			}

			//case4: x's sibling is black, sibling's left child is red
			if (sibling->left->color == RED) {
				sibling->color = (x->parent)->color;
				(sibling->left)->color = BLACK;
				(x->parent)->color = BLACK;
				rotateRight(root, x->parent);

				x = *root;
			}
		}
	}
	x->color = BLACK;
}

void* RB_DELETE(node** root, int data) {
	node* target = *root; //삭제하고 싶은 노드
	node* temp = NULL; //삭제된 노드
	node* x = NULL; //원래 위치
	char t_clr; //temp의 색
	while (data != target->data) {
		if ((target->data) > data) target = target->left;
		else target = target->right;
	}
	//TARGET에는 삭제하고 싶은 노드 저장
	t_clr = target->color;

	if (target->left == T_NIL) {
		x = target->right;
		Tree_Transplant(root, target, target->right);
	}
	else if (target->right == T_NIL) {
		x = target->left;
		Tree_Transplant(root, target, target->left);
	}
	else {
		temp = target->right;

		while (temp->left != T_NIL) temp = temp->left;
		t_clr = temp->color;
		x = temp->right;

		Tree_Transplant(root, temp, temp->right);
		temp->right = target->right;
		temp->right->parent = temp;

		Tree_Transplant(root, target, temp);
		temp->left = target->left;
		temp->left->parent = temp;
		temp->color = target->color;
	}
	if (t_clr == BLACK) DeleteFixup(root, x);

	free(target);
}

void print2DUtil(node* root, int space)
{
	// Base case
	int COUNT = 10;

	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->right, space);

	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->data);

	// Process left child
	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void bst_print(node* root)
{
	// Pass initial space count as 0
	print2DUtil(root, 0);
}

//search함수 구현
void PRINT_INFO(node** root, int data) {
	node* target = *root;
	while (data != target->data) {
		if ((target->data) > data) target = target->left;
		else target = target->right;
	}

	printf("name: ");
	for (int i = 0; target->passenger->name[i] != '\0'; i++) {
		printf("%c", target->passenger->name[i]);
	}
	printf("\n");
	printf("start city: %c\n", target->passenger->source);
	printf("destination city: %c\n", target->passenger->destination);
	printf("date: %d\n", target->passenger->sdate);
	printf("departure time: %d\n", target->passenger->stime);
	printf("arrival time: %d\n", target->passenger->etime);
	printf("flight time: %d\n", target->passenger->time);
	printf("seat number: %d\n", target->passenger->seat);
	printf("price: %d won\n", target->passenger->price);
}
