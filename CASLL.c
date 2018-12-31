/* 
Afreen Hameed CS288 HW2 
Making a SLL(Singly Linked List) into a Linked list of arrays to increase spatial locality and hence data access 
in the data structure.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* self-referential structure */
struct Node {
	int *item;
	struct Node *next;
};

struct List {
	struct Node *head;
	struct Node *tail;
	int nodeC;
	int headCount;
	int tailCount;
};


struct List SLL_new(int nodecap) {
	/* construct an empty list */
	struct List list;
	list.head = NULL;
	list.tail = NULL;
	list.nodeC=nodecap;
	list.headCount=0;
	list.tailCount=0;

	return list;
}

int SLL_length(struct List *list) {
	/* return the number of items in the list */
	struct Node *p;

	int n = 0;
	for (p = list->head; p != NULL; p = p->next) {
		++n;
	}

	if(list->head!=NULL){
		if(list->head==list->tail) n=list->headCount;
		else n=(n-2)*list->nodeC+list->headCount+list->tailCount;
	}
	return n;
}

int SLL_empty(struct List *list) {
	/* return true if the list contains no items */
	return list->head == NULL;
}

int SLL_pop(struct List *list) {
	/* remove and return the first item of the list */
	if(SLL_empty(list)){ /*error check*/
		printf("Error: List is already empty");
		exit(0);
	}
	struct Node *node = list->head;
	int item = node->item[--(list->headCount)];

	if(list->headCount==0){ /*head empty*/
		list->head = node->next;
		if(list->head==list->tail){/* 1 item */
			list->headCount=list->tailCount;
		}
		else if(SLL_empty(list)){
			list->tail=NULL;
			list->headCount=0;
			list->tailCount=0;
		}
		else{
			list->headCount=list->nodeC;
		}
	}
	/*free(node); maybe freed already?*/
	return item;
}

void SLL_clear(struct List *list) {
	/* remove all the items from the list */
	while (!SLL_empty(list)) {
		SLL_pop(list);
	}
}

void SLL_push(struct List *list, int item) {
	/* insert the item at the front of the list */
	if(list->headCount==list->nodeC || SLL_empty(list)){ /*head is full or not declared*/
		struct Node *node = malloc(sizeof(struct Node)); /*create new node*/
		if(node!=NULL) node->item = calloc(list->nodeC,sizeof(int));
		else printf("Error:Out of memory\n");
		if(node->item!=NULL){
			node->item[0]=item;
			list->headCount=1;
		}
		else(printf("Error:Out of memory\n"));
		node->next = list->head;	
		if(SLL_empty(list)){
			list->tail=node;
			list->tailCount=list->headCount;
		}
		list->head=node;	
	}
	else{/*head is partially full*/
		(list->head)->item[list->headCount]=item;
		list->headCount++;
		if(list->head==list->tail){
			list->tailCount++;
		}
	}
}

void SLL_append(struct List *list, int item) {
	/* append the item to the end of the list */
	if (SLL_empty(list)) {
		SLL_push(list, item);
	}
	else if(list->tailCount==list->nodeC){ /*tail is full*/
		struct Node *node = malloc(sizeof(struct Node));
		if(node!=NULL) node->item = calloc(list->nodeC,sizeof(int));
		else printf("Error:Out of memory\n");
		if(node->item!=NULL){
			node->item[0]=item;
			list->tailCount=1;
		}
		node->next = NULL;
		list->tail->next = node;
		list->tail = node;
	}
	else { /*tail not full*/
		int i;
		for(i=list->tailCount++;i>0;i--){
			(list->tail)->item[i]=(list->tail)->item[i-1];
		}
		(list->tail)->item[0]=item;
		if(list->tail==list->head){
			list->headCount=list->tailCount;
		}
	}
}


int main(int argc, char** argv) {
	int n,i,j, nodecap; 
	if (argc>2) j=*argv[2];   /*j is the number of walks for each node capacity chosen*/
	if(argc>1) nodecap=*argv[1];  /*number of items in each node*/

	if(argc<2){              /*in case of insufficient commnad line arguments*/
		j=10000000;
		nodecap=1;
	}
	else if(argc<3){
		j=10000000;
	}

	clock_t start, end;
    double cpu_time_used;


	for(n=1;n<1000;n=2*n){
	    start = clock();/*____________________________________________START SPEED TEST*/

		struct List list = SLL_new(n);
		for (i = 0; i < j; ++i) {
			/*if(SLL_empty(&list)) printf("List is empty\n");
			printf("List length: %d\n",SLL_length(&list));
			printf("%d loop\n",i);
			SLL_append(&list, i);*/
			SLL_push(&list, i);

		}
		struct Node*node=list.head;

		while (!SLL_empty(&list)) {
			/*printf("item: %d popped\n", SLL_pop(&list));*/
			SLL_pop(&list);
		}
		free(node);

	    end = clock();/*________________________________________________END SPEED TEST*/
	    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; /*taken from internet*/
	    printf("Node Capacity=%d CPU time=%f\n",n,cpu_time_used);
	}





	return 0;
}

     
     
     
     
