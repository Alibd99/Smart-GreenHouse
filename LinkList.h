#ifndef UNTITLED3_LINKLIST_H
#define UNTITLED3_LINKLIST_H
/**Linked List**/
typedef struct Temperature {
    int hours;
    int minutes;
    int seconds;
    double temperature;
}Temperature;

typedef struct LinkedList {
    int store;
    int hours;
    int minutes;
    int seconds;
    int days;
    int months;
    int years;
    double sensorData;
    struct Temperature * max;
    struct Temperature * min;
    struct LinkedList *next;
} LinkedList ;


typedef struct List {
    int size;
    LinkedList * head;
    LinkedList * tail;
} List;

struct Temperature *creatTemperature (int hours, int minutes, int seconds, double temperature);

struct LinkedList *creatLinked(int store,
                        int years, int months, int days,
                        int hours, int minutes, int seconds,
                        double temperature, Temperature * max, Temperature * min);

struct List * create ();

void append (struct List * list, int store,
                          int years, int months, int days,
                          int hours, int minutes, int seconds,
                          double temperature, Temperature * max, Temperature * min);

void freeList (List * list);
void deleteNode(List *list, struct LinkedList * node);
void printList(List *list);
void freeData(Temperature ** Node);
/**Linked List**/
struct LinkedList *newNode(int id, double sensorData);

void insertFirst (struct LinkedList **first, struct LinkedList *el);

int SizeOfList(struct LinkedList** first);

int isMember (struct LinkedList **first, struct LinkedList *el);
int isLast(struct LinkedList **first, struct LinkedList *el);

void printList2(struct LinkedList *first);

void removeLast(struct LinkedList **first);
void removeMiddle(struct LinkedList**first, struct LinkedList *el);
void removes(struct LinkedList **first, struct LinkedList *el);

struct LinkedList *readSensor();

struct LinkedList *getID (struct LinkedList** first, int id);
struct LinkedList * getSmallest(struct LinkedList** first);
void sort(struct LinkedList** first);

void freeList2(LinkedList **list);
#endif //UNTITLED3_LINKLIST_H
