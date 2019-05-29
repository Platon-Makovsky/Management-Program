#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <locale>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::vector;
using std::string;

typedef struct Shoe {
	char name[31];
	int bought, sold, left;
	float price;
}Shoe;

typedef struct Node {
	struct Shoe Shoe;
	struct Node* next;
}Node;

const char* NaF = "������ ��� �������� �����.";
const char* NaL = "������ ��� ������ �� �������.";
const char* Quit = "�� ������ �����.";
const char* IO = "������ I/O";
const char* Press = "��� ����������� ������ �� ����� ������.";
const char* Bounds = "��� ����� ������!";



bool addToFile(FILE* fp);
void readFromFileAndCreateList(FILE* fp);
Node* getLast(Node* head);
void queue(Node** head, Node* object);
void print(const Node* head);
bool alreadyThere(FILE* fp, Shoe* object0);
int countNodes(Node* head);
Node* getNth(Node* head, int n);
void delNth(Node** head, int n);
Node* popHead(Node** head);
void overwrite(FILE* fp, Node* head);
void check(Node* head);
void delZeros(FILE* fp, Node** head);
