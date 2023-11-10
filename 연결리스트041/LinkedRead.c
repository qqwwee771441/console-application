#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node* next;
} Node;

int main() {
	Node* head = NULL;
	Node* tail = NULL;
	Node* cur = NULL;
	
	Node* newNode = NULL;
	int readData;
	
	/* Dummy Node */
	head = (Node*)malloc(sizeof(Node));
	tail = head;
	/*
	newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	head = newNode;
	tail = newNode;
	*/
	
	/* Input Data */
	while(1) {
		printf("Input Natural Number: ");
		scanf("%d", &readData);
		if(readData < 1) break;
		
		newNode = (Node*)malloc(sizeof(Node));
		newNode->data = readData;
		newNode->next = NULL;
		
		tail->next = newNode;
		tail = newNode;
		
		/* // 04-1 answer
		if(head == NULL) {
			head = newNode;
			tail = newNode;
		} else {
			newNode->next = head;
			head = newNode;
		}
		*/
		/*
		if(head == NULL) head = newNode;
		else tail->next = newNode;
		tail = newNode;
		*/
		/*
		newNode = (Node*)malloc(sizeof(Node));
		newNode->data = readData;
		newNode->next = head;
		if(head == NULL) tail = newNode;
		head = newNode;
		*/
	} printf("\n");
	
	/* Output Data */
	printf("Output All Data! \n");
	/*
	cur = head->next;
	printf("%d ", cur->data);
	
	while(cur->next != NULL) {
		cur = cur->next;
		printf("%d ", cur->data);
	} printf("\n\n");
	*/
	if(head == tail) {
		printf("No Data..");
	} else {
		cur = head;
		// printf("%d ", cur->data); // print first data
		
		while(cur->next != NULL) { // print datas after first
			cur = cur->next;
			printf("%d ", cur->data);
		}
	} printf("\n\n");
	
	/* Free Memory */
	/*
	Node* delNode = head->next;
	Node* delNextNode = delNode->next;
	
	printf("delete %d. \n", delNode->data);
	free(delNode);
	
	while(delNextNode != NULL) {
		delNode = delNextNode;
		delNextNode = delNextNode->next;
		
		printf("delete %d. \n", delNode->data);
		free(delNode);
	}
	*/
	if(head == tail) {
		return 0;
	} else {
		Node* delNode = head;
		Node* delNextNode = head->next;
		
		// printf("delete %d. \n", delNode->data);
		// free(delNode); // delete first node
		
		while(delNextNode != NULL) { // delete nodes after first
			delNode = delNextNode;
			delNextNode = delNextNode->next;
			
			printf("delete %d. \n", delNode->data);
			free(delNode);
		}
	}
	
	return 0;
}

