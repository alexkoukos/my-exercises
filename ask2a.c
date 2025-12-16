#include <stdio.h>
#include <stdlib.h>



int* arrayInit(int);
void arrayPush(int*,int ,int*,int);
int arrayPop(int*,int*);


typedef struct node{
    int data;
    struct node* next;
} node;

typedef struct linkedstack{
    node* head;
} linkedstack;


linkedstack* listInit();
void listPush(linkedstack*,int);
int listPop(linkedstack*);

typedef struct linkedqueue{
    node* front;
    node* rear;
} linkedqueue;


linkedqueue* listqInit();
void listEnqueue(linkedqueue*,int);
int listDequeue(linkedqueue*);

void freeListStack(linkedstack*);
void freeLinkedQueue(linkedqueue*);

void freeListStack(linkedstack* s) {
    if (s == NULL) return;
    node* current = s->head;
    node* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(s);
    printf("Stack memory freed successfully.\n");
}

void freeLinkedQueue(linkedqueue* q) {
    if (q == NULL) return;
    node* current = q->front;
    node* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(q);
    printf("Queue memory freed successfully.\n");
}

linkedqueue* listqInit(){
    linkedqueue* q=(linkedqueue*)malloc(sizeof(linkedqueue));
    if(q!=NULL){
        q->front=NULL;
        q->rear=NULL;
    }else{
        printf("Failed to allocate memory\n");
    }
    return q;
}

void listEnqueue(linkedqueue* queue,int value){
    node* newnode=(node*)malloc(sizeof(node));
    if(newnode==NULL){
    printf("Out of memory\n");
    }
    newnode->data=value;
    newnode->next=NULL;
    if(queue->rear==NULL){
    queue->front=newnode;
    queue->rear=newnode;
    }else{
        queue->rear->next =newnode;
        queue->rear=newnode;
    }
}

int listDequeue(linkedqueue* queue){
    if(queue->front==NULL){
    printf("The queue is empty\n");
    return -1;
    }else{
        node* tmp=queue->front;
        int x=tmp->data;
        queue->front= queue->front->next;
        free(tmp);
        return x;
    }
}


linkedstack* listInit(){
    linkedstack* s = (linkedstack*) malloc (sizeof(linkedstack));
    if(s!=NULL){
        s->head=NULL;
    }else{
        printf("Memory allocation failed \n");
    }
    return s;
}


void listPush(linkedstack* stack,int value){
    node* newnode = (node*)malloc(sizeof(node));
    if(newnode==NULL){
        printf("Out of memory\n");
    }
    newnode->data=value;
    newnode->next=stack->head;
    stack->head=newnode;
}


int listPop(linkedstack* stack){
    if (stack->head == NULL){
        printf("The stack is empty\n");
    }else{
        node* tmp=stack->head;
        int x = tmp->data;
        stack->head=stack->head->next;
        free(tmp);
        return x;
    }
}


int* arrayInit(int N){
    int* arrstack = malloc(N*sizeof(int));
    if (arrstack==NULL){
        printf("There was a problem initializing the stack\n");
        return NULL;
    }else{
        printf("Stack was initialized with %d size\n",N);
        return arrstack;
    }
}




void arrayPush(int* arrstack,int x,int* cnt,int N){
    if (*cnt<N){
        arrstack[*cnt]=x;
        (*cnt)++;
        printf("Element %d succesfuly added to the stack\n",x);
    }
    else{
        printf("Stack is full\n");
    }
}

int arrayPop(int* arrstack,int* cnt){
    if(*cnt>0){
          (*cnt)--;
        int x=arrstack[*cnt];
        printf("Element %d returned\n",x);
        return x;
    }else{
        printf("The stack is empty\n");
        return -1;
    }
}


int main(){
    int N,y,z,k,cnt;
    cnt=0;
    y=1;
    z=6;
    k=9;
    printf("Give size for the stack\n");
    scanf("%d",&N);
    int* myarrstack=arrayInit(N);
    arrayPush(myarrstack,y,&cnt,N);
    arrayPush(myarrstack,z,&cnt,N);
    arrayPop(myarrstack,&cnt);
    arrayPush(myarrstack,k,&cnt,N);
    arrayPush(myarrstack,y,&cnt,N);
    linkedstack* myStack = listInit();
    if(myStack==NULL){
        printf("There was an error initializing list stack\n");
        return -1;
    }
    for(int i=1;i<1252;i=3*i){
        listPush(myStack,i);
        printf("Item %d was pushed to list stack.\n",i);
    }
    for(int i=1;i<124;i=5*i){
        int pop=listPop(myStack);
        printf("Item %d was popped from list stack.\n",i);
    }
    free(myarrstack);
    linkedqueue* myQueue = listqInit();
    if(myQueue==NULL){
    printf("There was an error initializing list stack.\n");
        return -1;
    }
       for(int i=1;i<1252;i=3*i+2){
        listEnqueue(myQueue,i);
        printf("Item %d was enqueued to list queue.\n",i);
    }
    for(int i=1;i<124;i=5*i-1){
        int dq=listDequeue(myQueue);
        printf("Item %d was dequeued from list queue.\n",i);
    }
    freeListStack(myStack);
    freeLinkedQueue(myQueue);
    return 0;
}
