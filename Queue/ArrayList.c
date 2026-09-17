#include <stdio.h>
#include <stdbool.h>
#define SIZE 5

typedef struct Queue {
    int q[SIZE];
    int front;
    int rear;
} Q;

void initQueue(Q *queue){
    queue->front = -1;
    queue->rear = -1;
}

bool isFull(Q *queue){
    if(queue->rear == SIZE - 1){
        return true;
    }
    return false;
}

bool isEmpty(Q *queue){
    if(queue->front == -1 || queue->front > queue->rear){
        return true;
    }
    return false;
}

void enqueue(Q *queue ,int value) {
    if(isFull(queue)){
        printf("Queue is Full!\n");
        return;
    }

    if (queue->front == -1)
        queue->front = 0;

    queue->rear++;
    queue->q[queue->rear] = value;

    printf("%d inserted\n", value);
}

void dequeue(Q *queue) {
    if (isEmpty(queue)) {
        printf("Queue Underflow\n");
        return;
    }

    printf("%d deleted\n", queue->q[queue->front]);
    queue->front++;
}

void display(Q *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->q[i]);
    }
    printf("\n");
}

int main() {

    Q q;

    initQueue(&q);
    enqueue(&q,10);
    enqueue(&q,20);
    enqueue(&q,30);

    display(&q);

    dequeue(&q);
    display(&q);

    return 0;
}
