#include "headers.h"

Node* head = NULL;

int main(void) {
	bool restart_to_update = false;
	int count = 0;
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(866);
	FILE* fp;
	if ((fp = fopen("file.bin", "ab")) == NULL) {
		puts(NaF);
		exit(-1);
	}
	readFromFileAndCreateList(fp);
	fclose(fp);
	int choice = 0;
	while (1) {
		system("cls");
		system("color 0f");
		puts("������� ����: ");
		puts("�����  ����� 1-5 ��� ������ �������.");
		puts("1. ���������� ������ � ������ � ����.");
		puts("2. ����� ����������� �����.");
		puts("3. ��������� ������ � ������.");
		puts("4. ����� �� ���������������� ������.");
		puts("5. �������� ������ �� ������.");
		puts("6. �������������� �������� ���� ��� �����, ������� �����������.");
		puts("7. ����� �� ���������.");
		cin >> choice;
		cin.ignore();
		switch (choice) {
		case 1: {
			system("cls");
			restart_to_update = addToFile(fp);
			system("cls");
			if (restart_to_update) {
				puts("���������� ���� ������� �������. ��� ���������� �� ���������, ���� ������������� ��������.");
				puts(Press);
				getche();
				return 0;
			}
			break;
		}
		case 2: {
			system("cls");
			system("color 3f");
			print(head);
			puts(Press);
			getche();
			system("cls");
			system("color 0f");
			break;
		}
		case 3: {
			while (1) {
				system("cls");
				system("color 8f");
				print(head);
				puts("������ � ����� ���� ����� ������� ��������?");
				puts("����� �� �����:");
				puts("��� -1 ��� �������� � ����.");
				int n;
				cin >> n;
				cin.ignore();
				if (n == -1) {
					break;
				}
				if (n <= 0 || n >= countNodes(head) + 1) {
					system("color 9f");
					puts(Bounds);
					puts(Press);
					getche();
					continue;
				}
				Shoe* change = (Shoe*)malloc(sizeof(Shoe*));
				Node* toBeChanged = getNth(head, n);
				puts("-------------------------------------------------");
				printf("|������� ���� ����� ��� ������� %d.\n", n);
				printf("|��������������� �����: %s.\n", toBeChanged->Shoe.name);
				printf("|�������: %d. �������: %d. ��������: %d.\n", toBeChanged->Shoe.bought, toBeChanged->Shoe.sold, toBeChanged->Shoe.left);
				printf("|����: %.2f.\n", toBeChanged->Shoe.price);
				puts("-------------------------------------------------");
				puts("����� ����� ������.");
				puts("����� ��������������� �����: ");
				gets_s(change->name, 31);

				if (!strcmp(change->name, "\0")) {
					puts(Quit);
					break;
				}
				puts("����� ���������� ���������: ");
				cin >> change->bought;
				cin.ignore();
				if (change->bought == -1) {
					puts(Quit);
					break;
				}
				puts("����� ���������� ���������: ");
				cin >> change->sold;
				cin.ignore();
				if (change->sold == -1) {
					puts(Quit);
					break;
				}
				else if (change->sold > change->bought) {
					system("color 9f");
					puts("������� ������ ��� �������?? �������� ��� ���!");
					getche();
					continue;
				}
				change->left = change->bought - change->sold;
				puts("����� ����: ");
				cin >> change->price;
				cin.ignore();
				if (change->price == -1) {
					puts(Quit);
					break;
				}
				toBeChanged->Shoe = *change;
				overwrite(fp, head);
				getchar();
			}
			break;
		}
		case 4: {

			break;
		}
		case 5: {
			system("color 6f");
			int n;
			while (1) {
				system("cls");
				print(head);
				puts("����� ����� ���� ����� ���� ������� ��\n��� -1 ��� ������ � �������� � ����.");
				cin >> n;
				cin.ignore();
				if (n == -1) {
					puts(Quit);
					break;
				}
				if (n > countNodes(head) || n < 0) {
					system("color 9f");
					puts("Out of bounds!!!");
					puts(Press);
					getche();
					system("color 6f");
					continue;
				}
				if (n == 1) {
					popHead(&head);
				}
				else if (n > 1) {
					delNth(&head, n);
				}
			}
			overwrite(fp, head);
			system("color 0f");
			break;
		}
		case 6: {
			system("color 9f");
			puts("��������: ����� �������� ��� ���� �����, ������� ����������� � ������.");
			puts("������ �������� ����������.");
			puts("��� �������� ������ �� 1.");
			puts("��� ������ � �������� � ���� ������ �� 0.");
			int del;
			cin >> del;
			cin.ignore();
			if (del) {
				puts("��������:");
				delZeros(fp, &head);
			}
			else {
				puts(Quit);
				break;
			}
			return 0;
		}
		case 7: {
			puts(Quit);
			printf("����� �����: %d.\n", countNodes(head));
			return 0;
		}
		case EOF: {
			puts(Quit);
			return 0;
		}
		default: {
			puts("������ ����� �� ������������!");
			getchar();
			system("cls");
			break;
		}
		}
	}

}

bool addToFile(FILE * fp) {
	bool restart_to_update = false;
	bool indicator = false; //checks whether an item already exists in the file

	Shoe* object0 = (Shoe*)malloc(sizeof(Shoe)); //object0 is being written to the file
	Shoe* object1 = (Shoe*)malloc(sizeof(Shoe)); //object1 is being passed to the alreadyAdded function

	vector<string> occurences;
	string dup;
	int c = 0; //number for indexing items added to the file


	while (1) {
		system("color 3f");
		if ((fp = fopen("file.bin", "ab+")) == NULL) {
			puts(NaF);
			exit(-1);
		}


		printf("���������� �� ����� ��� ������� �%d ����� �������� � ����.\n", ++c);
		printf("����� ��������������� ����� ���� �%d?\n", c);
		puts("(����� �� ENTER ���� ���������� ���� ���������� � ��������� � ����)");


		gets_s(object0->name, 31);
		dup = object0->name;
		vector<string>::iterator it;
		if ((it = std::find(occurences.begin(), occurences.end(), dup)) != occurences.end()) {
			--c;
			system("color 9f");
			puts("���� � ����� ��������������� ������� ��� ����������� � ������!");
			puts(Press);
			getche();
			continue;
		}
		else {
			occurences.push_back(dup);
		}

		if (!(strcmp(object0->name, "\0"))) {
			puts(Quit);
			break;
		}

		*object1 = *object0; //assign objects oneanother to pass object1 to the latter function
		//fclose //constant file opening and closing is required due to the change of modes


		if (indicator = alreadyThere(fp, object0)) { // intentional, we're not comparing bool to a function
			system("color 9f");
			puts("������ ���� ��� �������� � �����, ���� ������ �������� ���������� ���������/��������� ���, ������� � ���� � ������ �������, ������� �������� ���� ������� ���.");
			puts("� ���� ������ ����� ���������� � ������ ����.");
			--c;
			puts(Press);
			getche();
			system("color 0f");
			continue;
		}


		puts("������� ��� �������?");
		puts("����� -1 ��� ���� ����� ��������� � ������� ����.");

		cin >> object0->bought;
		cin.ignore();

		if (object0->bought == -1) {
			puts(Quit);
			break;
		}

		puts("������� ��� �������?");
		puts("����� -1 ��� ���� ����� ��������� � ������� ����.");

		cin >> object0->sold;
		cin.ignore();

		if (object0->sold == -1) {
			puts(Quit);
			break;
		}

		if (object0->sold > object0->bought) {
			system("color 9f");
			puts("������� ������ ��� �������?! �������� ��� ���.");
			--c;
			puts(Press);
			getche();
			continue;
		}
		object0->left = object0->bought - object0->sold;

		puts("������� ����� ��� ����?");
		puts("����� -1 ��� ���� ����� ��������� � ������� ����.");

		cin >> object0->price;
		cin.ignore();

		if (object0->price == -1) {
			puts(Quit);
			break;
		}

		if (fwrite(object0, sizeof(Shoe), 1, fp) != 1) {
			puts(IO);
			exit(-2);
		}
		restart_to_update = true;

	}
	fclose(fp);
	return restart_to_update;
}

void readFromFileAndCreateList(FILE * fp) {
	if ((fp = fopen("file.bin", "rb")) == NULL) {
		puts(NaF);
		exit(-1);
	}
	Shoe* object0 = (Shoe*)malloc(sizeof(Shoe));
	Node* object = (Node*)malloc(sizeof(Node));
	int c = 0;
	while (1) {
		++c;
		if (fread(object0, sizeof(Shoe), 1, fp) != 1) {
			break;
		}
		object->Shoe = *object0;
		queue(&head, object);
	}
	fclose(fp);
}

Node* getLast(Node * head) {
	if (head == NULL) {
		return NULL;
	}
	while (head->next) {
		head = head->next;
	}
	return head;
}
void queue(Node * *head, Node * object) {
	Node* last = getLast((*head));
	Node* tmp = (Node*)malloc(sizeof(Node));
	*tmp = *object;
	tmp->next = NULL;
	if (last != NULL) {
		last->next = tmp;
	}
	else {
		(*head) = tmp;
	}
}

void print(const Node * head) {
	if (head == NULL) {
		puts("������ ����.");
		return;
	}
	int c = 0;
	puts("--------------------------------------------------------------------------------");
	printf("  |��������������� �����: |  ����: | ��������� � �����: | �������: | ��������: |\n");
	while (1) {
		printf("%d.|%23s|  %6.2lf| %19d| %9d| %10d|\n", ++c, head->Shoe.name, head->Shoe.price, head->Shoe.bought, head->Shoe.sold, head->Shoe.left);
		if (head->next) {
			head = head->next;
		}
		else {
			break;
		}
	}
	puts("--------------------------------------------------------------------------------");
}

bool alreadyThere(FILE * fp, Shoe * object0) {
	Shoe* object1 = (Shoe*)malloc(sizeof(Shoe));

	while (1) {
		if (fread(object1, sizeof(Shoe), 1, fp) != 1) {
			return false;
		}
		if (!(strcmp(object1->name, object0->name))) {
			return true;
		}
	}
	//free(object1);
}

int countNodes(Node * head) {
	check(head);
	Node* subHead = head;
	int nodeQuan = 0;
	while (1) {
		if (subHead->next) {
			++nodeQuan;
			subHead = subHead->next;
		}
		else {
			return ++nodeQuan;
		}
	}
}

Node* getNth(Node * head, int n) {
	check(head);
	n--;
	if (n < 0) {
		puts("������: ��� ����� ������1.");
		exit(-3);
	}
	if (n > countNodes(head)) {
		printf("������: ��� ����� ������2. n = %d | countNodes = %d\n", n, countNodes(head));
		exit(-3);
	}
	for (int i = 0; i < n; i++) {
		head = head->next;
	}
	return head;
}

void delNth(Node * *head, int n) {
	check((*head));
	Node* prev = getNth((*head), n - 1);
	Node * elm = prev->next;
	prev->next = elm->next;
	free(elm);
}

Node * popHead(Node * *head) {
	check((*head));
	Node* prev = NULL;
	prev = (*head);
	(*head) = (*head)->next;
	free(prev);
	return (*head);
}
void overwrite(FILE * fp, Node * head) {
	check(head);
	if ((fp = fopen("file.bin", "wb")) == NULL) {
		puts(NaF);
		exit(-1);
	}
	Shoe* writing = (Shoe*)malloc(sizeof(Shoe));
	while (1) {
		*writing = head->Shoe;
		if (fwrite(writing, sizeof(Shoe), 1, fp) != 1) {
			break;
		}
		if (head->next) {
			head = head->next;
		}
		else {
			break;
		}
	}
	fclose(fp);
}

void check(Node * head) {
	if (head == NULL) {
		puts(NaL);
		exit(-3);
	}
}

void delZeros(FILE * fp, Node **head) {
	check(*head);
	if (countNodes(*head) == 1) {
		*head = popHead(head);
		overwrite(fp, *head);
		return;
	}
	Node* prev = NULL;
	Node* cur = *head;
	int n = 0;
	while (cur) {
		if ((cur)->Shoe.left == 0) {
			if (cur == *head)
			{
				*head = (*head)->next;
				free(cur);
				cur = *head;
			}
			else
			{
				(prev)->next = (cur)->next;
				free(cur);
				cur = NULL;
				(cur) = (prev)->next;
			}
		}
		else {
			prev = cur;
			(cur) = (cur)->next;
		}
	}
	overwrite(fp, *head);
}


