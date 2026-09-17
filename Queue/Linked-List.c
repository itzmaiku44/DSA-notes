#include <stdio.h>
#include <stdlib.h>
#define PRINT printf


typedef struct{
    int x;
    int y;
} Coordinate;

typedef struct Node{
    Coordinate data;
    struct Node *next;
} NodeQ;

typedef struct Queue{
    NodeQ *front;
    NodeQ *rear;
} Q;

void _init_(Q *q){
    q->front = NULL;
    q->rear = NULL;
}

void enqueue(Q *q, Coordinate c){
    NodeQ *temp = malloc(sizeof(struct Node));

    if(temp == NULL){
        PRINT("FAILED TO ALLOCATE MEMORY!\n");
        return;
    }

    temp->data.x = c.x;
    temp->data.y = c.y;
    temp->next = NULL;

    if(q->rear == NULL){
        q->front = temp;
        q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }

    PRINT("Coordinate (%d,%d) is inserted\n",c.x,c.y);
}


void dequeue(Q *q){
    if(q->front == NULL){
        PRINT("QUEUE IS EMPTY!\n");
        return;
    }

    NodeQ *temp = q->front;

    q->front = q->front->next;
    if(q->front == NULL){
        q->rear = NULL;
    }

    
    PRINT("Coordinate (%d,%d) is deleted\n", temp->data.x,temp->data.y);
    free(temp);
}

void peek(Q *q){
    if(q->front == NULL){
        PRINT("QUEUE IS EMPTY!\n");
        return;
    }

    PRINT("PEEKING AT COORDINATE (%d,%d)\n",
         q->front->data.x,
          q->front->data.y
         );
}

void display(Q *q){
    NodeQ *temp = q->front;

    if(!temp){
        PRINT("QUEUE IS EMPTY!\n");
        return;
    }

    //int i = 1;
    PRINT("\nQUEUE: ");
    while(temp){
        PRINT("(%d,%d)",
              temp->data.x,
              temp->data.y
             );
        if(temp->next != NULL){
            PRINT(", ");
        }
        //i++;
        temp = temp->next;
    }
    PRINT("\n\n");
}



int main() {

    Q q;
    _init_(&q);
    Coordinate c;
    
    int num;
    PRINT("Enter the number of Coordinates: ");
    scanf("%d", &num);

    for(int i = 0; i < num; ++i){
        PRINT("[%d]Coordinate:\n", i+1);
        PRINT("X: ");
        scanf("%d", &c.x);
        PRINT("Y: ");
        scanf("%d", &c.y);
        enqueue(&q,c);
    }

    

    display(&q);

    dequeue(&q);
    peek(&q);
    dequeue(&q);
    display(&q);
    peek(&q);
    
    return 0;
}



