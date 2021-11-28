#include "queue.h"

NodePtr __create_node(uint8 key) {

    NodePtr temp = (NodePtr) malloc(sizeof(Node));
    temp->key = key;
    temp->next = NULL;
    return temp;

}

QueuePtr create_empty_queue() {

    QueuePtr queue = (QueuePtr) malloc(sizeof(Queue));
    queue->front = NULL;
    queue->back = NULL;
    return queue;

}

void enqueue(QueuePtr queue, uint8 key) {

    NodePtr new_node = __create_node(key);

    // If the queue is currently empty, the one node will be the front and back simultaneously
    if (queue->front == NULL) {

        queue->front = new_node;
        queue->back = new_node;

    } else { // Otherwise, set the enqueued node to be the new back of the queue

        queue->back->next = new_node;
        queue->back = new_node;

    }

}

void dequeue(QueuePtr queue) {

    // If queue is empty, terminate function
    if (queue->front == NULL) return;

    // Otherwise, replace front node with its next node
    NodePtr temp = queue->front;
    queue->front = queue->front->next;

    // If queue becomes empty, we need to set the back of the queue to NULL
    if (queue->front == NULL) queue->back = NULL;

    // Now that the node is no longer needed, free its previously allocated heap memory
    free(temp);

}

uint8 front(QueuePtr queue) { return queue->front->key; }

uint8 is_empty(QueuePtr queue) { return (queue->front == NULL); }

void clear_queue(QueuePtr queue) { while (!is_empty(queue)) dequeue(queue); }