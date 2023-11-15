#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"
#include <stdlib.h>
#include <time.h>
#include "Mission.h"

struct Temperature *creatTemperature (int hours, int minutes, int second, double temperature) {
    struct Temperature * Node = NULL;
    Node = calloc (1, sizeof *Node);
    if(Node == NULL){
        printf("Out of Memory! Temperature\n");
        return NULL;
    }
    Node->hours   = hours;
    Node->minutes = minutes;
    Node->seconds = second;
    Node->temperature = temperature;
    return Node;
}

struct LinkedList *creatLinked(int store,
                            int years, int months, int days,
                                int hours, int minutes, int second,
                                    double temperature, Temperature * max, Temperature * min) {

    struct LinkedList *node = NULL;
    node = (LinkedList* )calloc (1, sizeof(LinkedList));

    if(node == NULL){
        printf("Out of Memory! Linked\n");
        return NULL;
    }

    node->store = store;
    node->years = years;
    node->months = months;
    node->days = days;
    node->hours = hours;
    node->minutes = minutes;
    node->seconds = second;
    node->sensorData = temperature;
    node->max = max;
    node->min = min;
    node->next = NULL;
    return node;
}

struct List * create () {
    List * list = NULL;
    list = calloc (1, sizeof *list);
    if (NULL == list) printf ("EXIT_FAILURE List");
    list->size = 0;
    return list;
}

void append (struct List * list, int store,
                          int years, int months, int days,
                          int hours, int minutes, int second,
                          double temperature, Temperature * max, Temperature * min) {

    struct LinkedList * lister = creatLinked( store,
                                       years,months, days,
                                       hours,  minutes, second,
                                       temperature , max, min);

    if (lister == NULL){
        printf ("EXIT_FAILURE LinkedList");
        free(max);
        free(min);
        deleteNode(list, list->head);
        return;
    }

    if (list->head == NULL) {
        list->head = lister;
        list->tail = lister;
    }
    else {
        list->tail->next = lister;
        list->tail = lister;
    }
    list->size++;
}

void deleteNode(struct List *list, struct LinkedList *Node) {
    struct LinkedList *prev = list->head;
    if (Node == NULL) {
        return;
    }

    free(Node->max);
    free(Node->min);
    if (Node == list->head) {
        list->head = Node->next;
    } else {
        while (prev != NULL && prev->next != Node) {
            prev = prev->next;
        }
        if (prev != NULL) {
            prev->next = Node->next;
        }
    }
    if (Node == list->tail) {
        list->tail = prev;
    }
    free(Node);
    list->size--;
}

void insertFirst (struct LinkedList **first, struct LinkedList *el){
    if(*first==NULL){
        *first = el;
        return;
    }

    el->next = *first;
    *first = el;
}

int SizeOfList(struct LinkedList** first){
    struct LinkedList* list = *first;
    int size = 1;
    if (list == NULL){
        return size = 0;
    }

    while (list->next != NULL){
        size++;
        list = list->next;
    }
    return size;
}

int isMember (struct LinkedList **first, struct LinkedList *el) {
    struct LinkedList *temp = NULL;
    temp = *first;
    if (*first == NULL) {
        return FALSE ;
    } else
        if (temp == el) {
        return TRUE; //For faster loop
    }
    //Checking the list
    while (temp != NULL) {
        if (temp == el) {
            return TRUE;
        }
        temp = temp->next;
    }
    return FALSE;
}

int isLast(struct LinkedList **first, struct LinkedList *el){
    struct LinkedList *temp = NULL;
    if (*first == NULL || !isMember(first,el)) {
        return FALSE;
    }
    temp = *first;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (temp == el){
        return TRUE;
    }
    return FALSE;
}

void printList2(struct LinkedList *first) {
    struct LinkedList *temp = first;
    printf("\nList elements are: \n");
    if(first == NULL){
        printf("The list is empty! \n");
        return;
    }
    while (temp != NULL) {
        printf("%02d/%02d/%04d - %02d:%02d:%02d - %.2f\n",
               temp->days,temp->months,temp->years,temp->hours,temp->minutes,temp->seconds, temp->sensorData);
        temp = temp->next;
    }
    printf("\n");
}

void printList(List *list) {
    LinkedList *currNode = list->head;

    if (currNode == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("id\tDate\tTime\tSensor Data\n");
    while (currNode != NULL) {
        printf("\t%d/%d/%d\t%d:%d:%d\t%.2f\n",
               currNode->days, currNode->months, currNode->years,
               currNode->hours, currNode->minutes, currNode->seconds,
               currNode->sensorData);
        currNode = currNode->next;
    }
}

void removeLast(struct LinkedList **first) {
    if (*first == NULL) {
        return;
    }
    if ((*first)->next == NULL) {
        free(*first);
        *first = NULL;
        return;
    }
    struct LinkedList *Last = *first;
    while (Last->next->next != NULL) {
        Last = Last->next;
    }
    free(Last->next);
    Last->next = NULL;
}

void removeMiddle(struct LinkedList**first, struct LinkedList *el) {
    struct LinkedList *temp = NULL;
    temp = *first;
    while (temp->next != NULL) {
        if (temp->next == el) {
            temp->next = temp->next->next;
        }
        temp = temp->next;
    }
}

void removes(struct LinkedList **first, struct LinkedList *el){
    struct LinkedList *temp = NULL;
    temp = *first;
    if (first == NULL){
        printf("\n The list is empty \n");
        return;
    }

    if (!isMember(first,el)){
        printf("\nThe element %d doesn't exist \n", el->store);
        return;
    }

    if(temp->next == NULL && temp == el){
        *first = NULL;
        return;
    }

    if (temp == el){
        temp = temp->next;
        *first = temp;
        return;
    }

    if(!isLast(first,el)){
        removeMiddle(first,el);
        return;
    }

    removeLast(first);
}

struct LinkedList *readSensor(){
    struct LinkedList *p = NULL;
    p = (struct LinkedList*) malloc(sizeof (struct LinkedList));
    if(p==NULL){
        printf("Out of Memory!\n");
        return NULL;
    }
    p->next = NULL;
    p->sensorData = ((double)rand()) / RAND_MAX; // NOLINT(cert-msc50-cpp)
    return p;
}

struct LinkedList *getID (struct LinkedList** first, int id){
    struct LinkedList *list = *first;
    struct LinkedList *note = NULL;

    while (list != NULL) {
        if (list->store == id) {
            note = list;
        }
        list = list->next;
    }
    return note;
}

struct LinkedList * getSmallest(struct LinkedList** first){
    struct LinkedList *list = *first;
    struct LinkedList *note = *first;

    while (list != NULL) {
        if (list->sensorData < note->sensorData) {
            note = list;
        }
        list = list->next;
    }
    return note;
}

void sort(struct LinkedList** first){
    struct LinkedList *list = *first;
    struct LinkedList *sub = *first;
    struct LinkedList *penn = NULL;

    if (*first == NULL){
        return;
    }

    while (sub != NULL) {
        penn = list;
        while (list != NULL) {
            if (list->sensorData >= penn->sensorData) {
                penn = list;
            }
            list = list->next;
        }
        removes(&sub,penn);
        removes(first, penn);
        list = sub;
        insertFirst(first, penn);
    }
}

void freeList2( LinkedList **lister){
    LinkedList* current = *lister;
    LinkedList* tempp = NULL;
    if (*lister == NULL){
        // printList(*list);
    }
    while (current != NULL){
        tempp = current->next;
        free(current);
        current = tempp;
    }
    free(*lister);
}

void freeList(List *lister) {
    LinkedList *current = lister->head;
    LinkedList *tempe = NULL;
    while (current != NULL) {
        tempe = current->next;
        free(current);
        current = tempe;
    }
    free(lister);
}