#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "types.h"

typedef struct _Node {

    int key;
    struct _Node* next;

} Node, * NodePtr;

typedef struct {

    NodePtr front;
    NodePtr back;

} Queue, * QueuePtr;

// Creates a node holding the value of the key
// Private function of the queue data structure
NodePtr __create_node(uint8 key);

// Creates an empty queue
QueuePtr create_empty_queue();

// Enqueues the key to the queue of choice
void enqueue(QueuePtr queue, uint8 key);

// Dequeues the key from the queue of choice
void dequeue(QueuePtr queue);

// Return the value of the front of the queue (WITHOUT DEQUEUEING)
uint8 front(QueuePtr queue);

// Inquire if queue is empty or not
uint8 is_empty(QueuePtr queue);

// Clears the queue
void clear_queue(QueuePtr queue);

#endif /* QUEUE_H */
