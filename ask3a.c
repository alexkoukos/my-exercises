#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct node{
    char am[10];
    char name[50];
    int semester;
    struct node* next;
    struct node* prev;
} node;


typedef struct mylist{
    struct node* head;
    struct node* tail;
    int size;
} mylist;


mylist initList();
void insertStudent(mylist*,char*,char*,int);
node* searchStudentByAm(mylist*,char*);
node* searchStudentByName(mylist*,char*);
void deleteStudent(mylist*,char*);
void diasxisi(mylist*);

mylist initList(){
    mylist* l = (mylist*)malloc(sizeof(mylist));
    if(l==NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    l->head=NULL;
    l->tail=NULL;
    return l;
}

void insertStudent(mylist* list,char* am,char* name,int semester){
    node* newnode=(node*)malloc(sizeof(node));
    if(newnode==NULL){
    printf("Out of memory\n");
    return;
    }
    strcpy(newnode->am,am);
    strcpy(newnode->name,name);
    newnode->semester=semester;
    newnode->next=NULL;
    newnode->prev=NULL;
    if(list->head==NULL){
        list->tail=newnode;
        list->head=newnode;
    }else{
        newnode->prev=list->tail;
        l->tail->next=newnode;
        l->tail=newnode;
    }
}


node* searchStudentByAm(mylist* list,char* targetAm){
    node* curr = list->head;
    while(curr!=NULL){
        if (strcmp(curr->am,targetAm)==0){
            return curr;
        }
        curr = curr -> next;
    }
    return NULL;
}


node* searchStudentByName(mylist* list,char* targetName){
    node* curr = list->head;
    while(curr!=NULL){
        if (strcmp(curr->am,targetName)==0){
            return curr;
        }
        curr = curr -> next;
    }
    return NULL;
}

void deleteStudent(mylist* list,char* targetAm){
    node* targetNode = searchStudentByAm(list,targetAm);
    if(targetNode==NULL){
        printf("Student not found\n");
        return;
    }
    if(targetNode->prev !=NULL){
        targetNode->prev->next = targetNode->next;
    }else{
        list->head= targetNode-> next;
    }
    if(targetNode->next!=NULL){
        targetNode->next->prev = targetNode->prev;
    }else{
        list->tail= targetNode-> prev;
    }
    if(list->head==NULL){
        list->tail=NULL;
    }
    free(targetNode);
}

void printAllStudents(mylist* list) {
    node* current = list->head;
    printf("\n--- STUDENT LIST ---\n");
    if (current == NULL) {
        printf("The list is empty.\n");
        return;
    }
    while (current != NULL) {
        printf("AM: %s | Name: %s | Semester: %d\n", current->am, current->name, current->term);
        current = current->next;
    }
    printf("----------------------\n");
}

void printStudentsBySemester(mylist* list, int targetSemester) {
    node* current = list->head;
    int found = 0;
    printf("\n--- STUDENTS OF SEMESTER %d ---\n", targetSemester);
    while (current != NULL) {
        if (current->term == targetSemester) {
            printf("AM: %s | Name: %s\n", current->am, current->name);
            found++;
        }
        current = current->next;
    }
    if (found == 0) {
        printf("No students found in semester %d.\n", targetSemester);
    }
    printf("-----------------------------\n");
}












