Queue in C Programming
1. What is a Queue?

A Queue is a linear data structure that follows the FIFO principle:

FIFO = First In, First Out

The first element inserted into the queue is the first element removed.

Example
Insert:  10 → 20 → 30

Queue:

FRONT                  REAR
  ↓                      ↓
[10] → [20] → [30]


If we perform dequeue(), 10 is removed first:

FRONT            REAR
  ↓                ↓
[20] → [30]

2. Basic Queue Operations

A queue normally has two main operations:

Operation	Meaning	Location
enqueue()	Add an element	REAR
dequeue()	Remove an element	FRONT

There is also:

display() → Shows the elements in the queue.

initialize() → Sets the queue to an empty state.

Remember
ENQUEUE  → REAR
DEQUEUE  → FRONT


A simple way to remember this:

Enter at the Rear, Exit at the Front.

3. Queue Using an Array

An array queue stores the elements in a fixed-size array.

Example:

Index:    0    1    2    3    4
         +----+----+----+----+----+
Queue:   | 10 | 20 | 30 |    |    |
         +----+----+----+----+----+
           ↑              ↑
         FRONT           REAR


The array has a fixed capacity.

For example:

#define SIZE 5


means the queue can contain up to 5 positions.

4. User-Defined Struct for Array Queue

Instead of declaring the queue variables separately, we can put them inside a struct.

struct Queue {
    int items[SIZE];
    int front;
    int rear;
};


This structure contains:

items[] → stores the queue elements.

front → identifies the first element.

rear → identifies the last element.

We can then create a queue:

struct Queue q;

5. Initializing an Array Queue

An empty queue can be represented using:

q.front = -1;
q.rear = -1;


So we can create:

void initialize(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

Why -1?

Array indexes normally start at 0.

0  1  2  3  4


Therefore, -1 can represent:

"There is currently no valid element."

6. Why Use struct Queue *q?

Consider:

void enqueue(struct Queue *q, int value)


The *q means the function receives the address of the queue.

This allows the function to modify the original queue.

For example:

q->rear++;


The -> operator is used because q is a pointer to a structure.

Compare:

struct Queue q;


Accessing members:

q.front
q.rear


But if we have:

struct Queue *q;


we use:

q->front
q->rear

Easy rule
Normal struct variable  → .
Struct pointer          → ->

7. Enqueue in an Array Queue

The purpose of enqueue() is to add an element at the rear.

void enqueue(struct Queue *q, int value) {

    if (q->rear == SIZE - 1) {
        printf("Queue Overflow\n");
        return;
    }

    if (q->front == -1) {
        q->front = 0;
    }

    q->rear++;
    q->items[q->rear] = value;
}

Step-by-step

Suppose the queue is empty:

front = -1
rear  = -1


Insert 10.

First:

q->front = 0;


Then:

q->rear++;


So:

front = 0
rear  = 0


And:

q->items[q->rear] = 10;


The queue becomes:

[10]
 ↑
 F/R


Insert 20:

FRONT       REAR
  ↓           ↓
[10] → [20]

8. Queue Overflow

Overflow happens when we try to insert into a full array queue.

For a queue with:

#define SIZE 5


the last valid index is:

SIZE - 1 = 4


Therefore:

if (q->rear == SIZE - 1)


checks whether the rear has reached the end.

Remember:

Array index ends at SIZE - 1, not SIZE.

9. Dequeue in an Array Queue

dequeue() removes the element from the front.

void dequeue(struct Queue *q) {

    if (q->front == -1 || q->front > q->rear) {
        printf("Queue Underflow\n");
        return;
    }

    printf("%d deleted\n", q->items[q->front]);

    q->front++;
}


Suppose:

FRONT             REAR
  ↓                 ↓
[10] → [20] → [30]


After:

dequeue(q);


10 is removed logically:

        FRONT       REAR
          ↓           ↓
[10] → [20] → [30]
         ↑
      next item


We don't actually move all the elements.

We simply increase:

q->front++;

10. Empty Queue After Dequeue

Suppose the queue contains only:

[30]
 ↑
 F/R


After removing 30, the queue should become:

front = -1
rear = -1


Therefore:

if (q->front > q->rear) {
    q->front = -1;
    q->rear = -1;
}


This resets the queue to its original empty state.

11. Complete Array Queue Program
#include <stdio.h>

#define SIZE 5

struct Queue {
    int items[SIZE];
    int front;
    int rear;
};

void initialize(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

void enqueue(struct Queue *q, int value) {

    if (q->rear == SIZE - 1) {
        printf("Queue Overflow\n");
        return;
    }

    if (q->front == -1) {
        q->front = 0;
    }

    q->rear++;
    q->items[q->rear] = value;

    printf("%d inserted\n", value);
}

void dequeue(struct Queue *q) {

    if (q->front == -1 || q->front > q->rear) {
        printf("Queue Underflow\n");
        return;
    }

    printf("%d deleted\n", q->items[q->front]);

    q->front++;

    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
}

void display(struct Queue *q) {

    if (q->front == -1) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");

    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }

    printf("\n");
}

int main() {

    struct Queue q;

    initialize(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    display(&q);

    dequeue(&q);

    display(&q);

    return 0;
}

12. Queue Using a Linked List

Unlike an array, a linked-list queue does not have a fixed number of elements.

A node can be represented as:

struct Node {
    int data;
    struct Node *next;
};


Each node contains:

[data | next]


Example:

FRONT                         REAR
  ↓                             ↓
[10 | •] → [20 | •] → [30 | NULL]

13. User-Defined Queue Struct with Linked List

We can define another structure for the queue:

struct Queue {
    struct Node *front;
    struct Node *rear;
};


Therefore, we have two structures:

struct Node


stores an individual element.

struct Queue


keeps track of the queue.

14. Enqueue in a Linked List

First, create a new node:

struct Node *newNode =
    (struct Node *)malloc(sizeof(struct Node));


Then store the value:

newNode->data = value;


And make the new node the last node:

newNode->next = NULL;


If the queue is empty:

if (q->rear == NULL) {
    q->front = newNode;
    q->rear = newNode;
}


Otherwise:

q->rear->next = newNode;
q->rear = newNode;

Remember

When inserting into a linked-list queue:

New node goes to REAR.

15. Dequeue in a Linked List

To remove an element:

struct Node *temp = q->front;


Then move front:

q->front = q->front->next;


Finally, free the old node:

free(temp);


Example:

Before:

FRONT                  REAR
  ↓                      ↓
[10] → [20] → [30]


After dequeue:

         FRONT          REAR
           ↓              ↓
[10] → [20] → [30]
         ↑
       first


The node containing 10 is then freed.

16. Why Use free()?

When using:

malloc()


memory is dynamically allocated.

Therefore, after removing a node, we should release its memory:

free(temp);


Otherwise, the program may waste memory.

This is especially important when working with linked lists.

17. Complete Linked List Queue Program
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Queue {
    struct Node *front;
    struct Node *rear;
};

void initialize(struct Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueue(struct Queue *q, int value) {

    struct Node *newNode =
        (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    printf("%d inserted\n", value);
}

void dequeue(struct Queue *q) {

    if (q->front == NULL) {
        printf("Queue Underflow\n");
        return;
    }

    struct Node *temp = q->front;

    printf("%d deleted\n", temp->data);

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

void display(struct Queue *q) {

    struct Node *temp = q->front;

    if (temp == NULL) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main() {

    struct Queue q;

    initialize(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    display(&q);

    dequeue(&q);

    display(&q);

    return 0;
}

18. Array vs Linked List Queue
Feature	Array	Linked List
Storage	Array	Nodes
Size	Fixed	Dynamic
Memory allocation	Usually static	Dynamic
Overflow	Array becomes full	Memory becomes unavailable
Extra pointer	No	Yes
Enqueue	O(1)	O(1)
Dequeue	O(1)	O(1)
Implementation	Easier	More pointer handling
19. Important C Concepts to Remember
struct

Used to group related variables.

struct Queue {
    int front;
    int rear;
};

Pointer to struct
struct Queue *q;

Structure member

With a normal structure variable:

q.front


With a structure pointer:

q->front

malloc()

Allocates memory dynamically:

malloc(sizeof(struct Node))

free()

Releases dynamically allocated memory:

free(temp);

NULL

Usually means that a pointer does not point to a valid node.

q->front = NULL;

20. Common Mistakes
Mistake 1: Using . instead of ->

Wrong:

q.front


when q is a pointer.

Correct:

q->front

Mistake 2: Forgetting & in main()

If the function expects:

struct Queue *q


call it with:

enqueue(&q, 10);


not:

enqueue(q, 10);

Mistake 3: Forgetting to initialize

Always initialize the queue:

initialize(&q);

Mistake 4: Forgetting free()

After removing a dynamically allocated linked-list node:

free(temp);

Mistake 5: Forgetting to update rear

When the last linked-list node is removed:

if (q->front == NULL) {
    q->rear = NULL;
}


Both pointers must indicate that the queue is empty.

21. Exam Tips
Tip 1 — Memorize FIFO
FIFO = First In, First Out


Think of a line of people waiting.

The person who arrives first gets served first.

Tip 2 — Memorize FRONT and REAR
ENQUEUE → REAR
DEQUEUE → FRONT

Tip 3 — Know the difference between . and ->
struct variable  → .
struct pointer   → ->


Example:

struct Queue q;

q.front;


But:

struct Queue *q;

q->front;

Tip 4 — Understand the pointers

For linked-list queues:

front → first node
rear  → last node


For example:

front
  ↓
[10] → [20] → [30] → NULL
                         ↑
                        rear

Tip 5 — Know the empty conditions

Array queue:

front == -1


Linked-list queue:

front == NULL

Tip 6 — Know Overflow and Underflow

Overflow:

Trying to insert when the queue cannot accept another element.

Underflow:

Trying to remove an element from an empty queue.

22. Quick Memorization Sheet
QUEUE
│
├── FIFO
│
├── ENQUEUE
│     └── Insert at REAR
│
├── DEQUEUE
│     └── Remove from FRONT
│
├── ARRAY
│     ├── Fixed size
│     ├── front = -1 initially
│     └── rear = -1 initially
│
└── LINKED LIST
      ├── Dynamic size
      ├── front = NULL initially
      ├── rear = NULL initially
      └── use malloc() and free()

Most Important Lines to Remember
// Array
q->items[q->rear] = value;

// Linked list
q->rear->next = newNode;
q->rear = newNode;

// Dequeue
q->front = q->front->next;

// Free removed node
free(temp);


Golden Rule: For a queue, insert at the REAR and remove from the FRONT.
