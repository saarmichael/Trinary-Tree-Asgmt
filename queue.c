
/*******************************************************
* Michael Saar
* 315240937
* 01
* Ex6
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*************************
 * This is a generic Queue module. (linked-list type)
 * Queues are a linked list that has pointers to the first element and to the last element.
 * Queues work in FIFO method
 * Inserting new Node to Queue happens by adding a new node to the end of the queue
 * Deleting a node happens from the front of the queue
 *
 * This Module contains the following functions:
    * createQueue
    * enQueue - appending new QNode to rear of Queue
    * deQueue - deleting the front of Queue
    * isEmpty - checking if Queue is empty
    * destroyQueue
 * Note that this Queue Module can be implemented to any type of values and Structs!
 ************************/

/***********************************************************************************
* Function name: createQueue
* Input: no input
* Output: a pointer to the new Queue (NULL if malloc fails)
* Function Operation: the function creates a new Queue and initialize it
* Note: if malloc fails, the functions that is calling this function will run exit procedure
***********************************************************************************/
Queue* createQueue(){
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

/***********************************************************************************
* Function name: enQueue
* Input: Queue* q, void* k
* Output: 1 if adding new QNode was successful, else returns 0
* Function Operation: the function creates a new QNode and appends it to the rear of the Queue
***********************************************************************************/
int enQueue(Queue* q, void* k){
    //create new QNode and check if malloc was successful
    QNode* node = (QNode*) malloc(sizeof(QNode));
    if (node == NULL){
        return 0;
    }
    node->key = k;
    //if there is no element in Queue, point rear and front to the new node
    if (q->front == NULL){
        q->front = node;
        q->rear = node;
        q->front->next = NULL;
        q->rear->next = NULL;
        //successfully done
        return 1;
    }
    //there are elements in q, add node to rear,and point rear->next to NULL
    q->rear->next = node;
    q->rear = node;
    q->rear->next = NULL;
    return 1;
}

/***********************************************************************************
* Function name: deQueue
* Input: Queue* q
* Output: no return
* Function Operation: the function creates a new QNode and appends it to the rear of the Queue
***********************************************************************************/
void deQueue(Queue* q){
    //if q is empty, do nothing
    if (q->front == NULL){
        return;
    }
    //point temp at front, move second in queue to front and free temp (which was the first in queue)
    QNode* temp = q->front;
    q->front = q->front->next;
    free(temp);
}

/***********************************************************************************
* Function name: isEmpty
* Input: Queue* q
* Output: 1 if Queue is empty, 0 if not
* Function Operation: the function creates a new QNode and appends it to the rear of the Queue
***********************************************************************************/
int isEmpty(Queue* q){
    //if queue is empty, return 1
    if (q->front == NULL){
        return 1;
    }
    //if queue is not empty, return 0
    return 0;
}

/***********************************************************************************
* Function name: destroyQueue
* Input: Queue* q
* Output: no return
* Function Operation: the function destroys the Queue and frees it
***********************************************************************************/
void destroyQueue(Queue* q){
    //delete all QNodes of Queue
    while (q->front != NULL){
        deQueue(q);
    }
    //free the queue
    free(q);
}