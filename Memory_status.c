#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_X 5
#define BUFFER_SIZE 20

char memory_check[BUFFER_SIZE];
int temp = 0, lowest = 9999, temp2 = 0;

typedef struct ListNode
{
	char data;
	struct ListNode* prev;
	struct ListNode* next;
} ListNode;

ListNode* head;   //��� ���̳��
ListNode* tail;   //������ ���̳��

//������ Ÿ�� ����
ListNode* insertNodeNext(ListNode* node, char s);
ListNode* deleteNode(ListNode* node, int num);
ListNode* BEST_FIT_ALLOCATION(ListNode* node, char text, int num);
ListNode* BEST_FIT_FREE(ListNode* node, char text, int num);
void initList();
void changeToPrev(ListNode* node, char data);
void changeToNext(ListNode* node, char data);
void printList(ListNode* node);
void memoryFlag(ListNode* node, char* memory_check_input);
void memoryManagementFromStart(ListNode* node);
void memoryManagementFromEnd(ListNode* node);
int WORST_FIT_ALLOCATION(ListNode* node, char data, char data_size);
int WORST_FIT_FREE(ListNode* node, char data_index, char data_size);


int main()
{
	srand(time(NULL));
	initList();
	ListNode* p = head;

	//�ʱ�ȭ
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		p->next = insertNodeNext(p, '.');
	}
	printList(head);

	//�������� �ټ��� �޸� ����
	for (int j = 0; j < NUM_X; j++)
	{
		if (deleteNode(head, rand() % 20) == 0)
			j--;
	}
	printList(head);
	memoryFlag(head->next, memory_check);
	/*for (int k = 0; k < BUFFER_SIZE; k++)
	{
	   printf("%d : %d\n", k, memory_check[k]);
	}*/
	printf("\n*****BEST FIT ALLOCATION*****\n");
	BEST_FIT_ALLOCATION(head->next, 'B', 3);
	printList(head);

	printf("\n*****BEST FIT FREE*****\n");
	BEST_FIT_FREE(head->next, '.', 3);
	printList(head);

	printf("\n*****WORST FIT ALLOCATION*****\n");
	int cnt = WORST_FIT_ALLOCATION(head->next, 'W', 3);
	printList(head);

	printf("\n*****WORST FIT ALLOCATION*****\n");
	WORST_FIT_FREE(head->next, cnt, 3);
	printList(head);

	printf("\n*****MEMORY MANAGEMENT FROM START*****\n");
	BEST_FIT_ALLOCATION(head->next, 'B', 3);
	WORST_FIT_ALLOCATION(head->next, 'W', 3);
	printList(head);
	memoryManagementFromStart(head->next);
	printList(head);

	printf("\n*****MEMORY MANAGEMENT FROM END*****\n");
	memoryManagementFromEnd(tail->prev);
	printList(head);

	return 0;
}

//����Ʈ �ʱ�ȭ
void initList()
{
	head = (ListNode*)malloc(sizeof(ListNode));
	tail = (ListNode*)malloc(sizeof(ListNode));
	head->prev = NULL;
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;
}

//node�� ���� ��忡 ������ s ����
ListNode* insertNodeNext(ListNode * node, char s)
{
	ListNode* new;
	new = (ListNode*)malloc(sizeof(ListNode));
	new->data = s;
	node->next->prev = new;
	new->next = node->next;
	node->next = new;
	new->prev = node;

	return new;
}

//������ŭ ��� ����
ListNode* deleteNode(ListNode * node, int num)
{
	// i=1 ���� ù��° ��尡 �ٲ����ϴµ� 2��° ��尡 �ٲ�°� �����ϱ�����
	for (int i = 1; i < num; i++) {
		node = node->next;
	}
	if (node->data == 'X')
		return 0;
	node->data = 'X';
	return node;
}

//data ��ġ �����ϰ� ���� ����� data ����
void changeToPrev(ListNode * node, char data) {
	if (node->prev != NULL) {
		node->prev->data = node->data;
		node->data = data;
	}
	else {
		printf("CHANGE DATA ERROR");
	}
}

void changeToNext(ListNode * node, char data) {
	if (node->next != NULL) {
		node->next->data = node->data;
		node->data = data;
	}
	else
	{
		printf("CHANGE DATA ERROR");
	}
}

//print
void printList(ListNode * node)
{
	printf("Memory status \n");
	printf("[ ");
	for (ListNode* p = node->next; p != tail; p = p->next) {
		printf("%c ", p->data);
	}
	printf("] \n");
}

void memoryFlag(ListNode * node, char* memory_check_input)
{
	int count = 0;
	ListNode* temp = NULL;
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		count = 0;
		temp = node;
		for (int j = i; j < BUFFER_SIZE; j++)
		{
			if (temp->data == '.')
			{
				count++;
				temp = temp->next;
			}
			else {
				break;
			}
		}
		memory_check_input[i] = count;
		node = node->next;
	}
}

ListNode* BEST_FIT_ALLOCATION(ListNode * node, char text, int num)
{
	for (int i = 0; i < BUFFER_SIZE; i++) {
		if (memory_check[i] != 0) {
			for (int j = i + 1; j < BUFFER_SIZE; j++) {
				if (memory_check[j] != 0) {
					memory_check[j] = 0;
				}
				else {
					break;
				}
			}
		}
	}

	for (int i = 0; i < BUFFER_SIZE; i++) {
		if (memory_check[i] - num >= 0) {
			temp = memory_check[i] - num;
			if (temp < lowest) {
				lowest = temp;
				temp2 = i;
			}
		}
	}

	if (lowest > num) {
		return node;
	}

	for (int i = 0; i < temp2; i++) {
		node = node->next;
	}
	for (int i = 0; i < num; i++) {
		node->data = text;
		node = node->next;
	}
	return node;
}

ListNode* BEST_FIT_FREE(ListNode * node, char text, int num)
{
	if (lowest > num) {
		return node;
	}

	for (int i = 0; i < temp2; i++) {
		node = node->next;
	}
	for (int i = 0; i < num; i++) {
		node->data = text;
		node = node->next;
	}
	return node;
}

int WORST_FIT_ALLOCATION(ListNode * node, char data, char data_size) {
	int i = 0;
	int cnt = 100;
	int temp = 0;

	for (i = 0; i < BUFFER_SIZE - 1; i++) {
		if (temp < memory_check[i]) {
			temp = memory_check[i];
			cnt = i;      //index��� �� �� ����
		}
	}
	if (cnt != 100) {
		for (i = 0; i < cnt; i++) {
			node = node->next;
		}
		for (i = 0; i < data_size; i++) {
			node->data = data;
			node = node->next;
		}
		return cnt;
	}
	else {
		return 0;
	}
}

int WORST_FIT_FREE(ListNode * node, char data_index, char data_size)
{
	int i = 0;

	for (i = 0; i < data_index; i++) {
		node = node->next;
	}
	for (i = 0; i < data_size; i++) {
		node->data = '.';
		node = node->next;
	}
	return 0;
}

//���ۺ��� �޸𸮸� ä�� ����� ����
void memoryManagementFromStart(ListNode * node) {
	ListNode* temp = NULL;
	if (node != NULL)
	{
		for (int i = 1; i < BUFFER_SIZE; i++) {
			node = node->next;
			if (node->data != '.') {
				temp = node;
				for (int j = i; j > 0; j--) {
					if (temp->prev->data != '.') {
						break;
					}
					else {
						changeToPrev(temp, '.');
						memoryFlag(head->next, memory_check);
					}
					temp = temp->prev;
				}
			}
		}
	}
}

//������ �޸𸮸� ä�� ����� ����
void memoryManagementFromEnd(ListNode * node) {
	ListNode* temp = NULL;

	if (node != NULL) {
		for (int i = BUFFER_SIZE - 1; i > 0; i--) {
			node = node->prev;
			if (node->data != '.') {
				temp = node;
				for (int j = i; j < BUFFER_SIZE; j++) {
					if (temp->next->data != '.') {
						break;
					}
					else {
						changeToNext(temp, '.');
						memoryFlag(head->next, memory_check);
					}
					temp = temp->next;
				}
			}

		}
	}
}