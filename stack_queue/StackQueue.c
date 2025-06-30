#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
    int size;
} Stack;

typedef struct Queue {
    Node* rear;
    Node* front;
    int size;
} Queue;

Stack* createstack() {
    Stack* s = malloc(sizeof(Stack));
    if (!s) {
        perror("[!]> Allocation stack");
        exit(EXIT_FAILURE);
    }
    s->top = NULL;
    s->size = 0;
    return s;
}

int emptystack(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, int value) {
    Node* n = malloc(sizeof(Node));
    if (!n) {
        perror("[!]> Allocation push");
        exit(EXIT_FAILURE);
    }
    n->data = value;
    n->next = s->top;
    s->top = n;
    s->size++;
}

int pop(Stack* s) {
    if (emptystack(s)) {
        printf("[!]> Empty stack");
        return -1;
    }
    Node* temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    s->size--;
    return value;
}

void printstack(Stack* s) {
    Node* curr = s->top;
    printf("[?]> The stack : \n");
    printf("TOP : ");
    while (curr) {
        printf("[%d] -> ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void freestack(Stack* s) {
    while(!emptystack(s)) {
        pop(s);
    }
    free(s);
}

Queue* createqueue() {
    Queue* q = malloc(sizeof(Queue));
    if (!q) {
        perror("[!]> Allocation queue");
        exit(EXIT_FAILURE);
    }
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

int emptyqueue(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, int value) {
    Node* n = malloc(sizeof(Node));
    if (!n) {
        perror("[!]> Allocation enqueue");
        exit(EXIT_FAILURE);
    }
    n->data = value;
    n->next = NULL;
    if (emptyqueue) {
        q->front = q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
    q->size++;
}

int dequeue(Queue* q) {
    if (emptyqueue(q)) {
        printf("[!]> Empty queue");
        return -1;
    }
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    free(temp);
    q->size--;
    return value;
}

void printqueue(Queue* q) {
    Node* curr = q->rear;
    printf("[?] The queue : \n");
    printf("REAR : ");
    while (curr) {
        printf("[%d] -> ", curr->data);
        curr = curr->next;
    }
    printf(" : FRONT \n");
}

void freequeue(Queue* q) {
    while (!emptyqueue(q)) {
        dequeue(q);
    }
    free(q);
}

void MenuStack () {
    printf("\n ==============<| Stack |>============== \n");
    printf("    1. Push \n");
    printf("    2. Pop \n");
    printf("    3. Show the stack \n");
    printf("    0. Quit the stack \n");
    prinf("choice : ");
}

void MenuQueue() {
    printf("\n ==============<| Queue |>============== \n");
    printf("    1. Enqueue \n");
    printf("    2. Dequeue \n");
    printf("    3. Show the queue \n");
    printf("    0. Quit the queue \n");
    prinf("choice : ");
}

int main () {
    int StructureChoice;
    printf("-----------------------------------------------<| Data Structure |>-----------------------------------------------");
    printf("Which structure to choose : \n");
    printf("    1. Stack \n");
    printf("    2. Queue \n");
    prinf("Your choice : ");
    scanf("%d", &StructureChoice);

    if (StructureChoice == 1) {
        Stack* s = createstack();
        int choice, val;
        do {
            MenuStack();
            scanf("%d", &choice);
            switch(choice) {
                case 1:
                    prinf("[+]> Value to push : \n");
                    scanf("%d", &val);
                    push(s, val);
                    break;
                case 2:
                    val = pop(s);
                    if (val != -1) {
                        printf("[-]> Value pop : %d \n", val);
                    }
                    break;
                case 3:
                    printstack(s);
                    break;
                case 0:
                    printf("[!]> Exit \n");
                    break;
                default:
                    printf("[!]> Invalid Choice \n");
            }
        } while (choice != 0);
        freestack(s); 
    } else if (StructureChoice == 2) {
        Queue* q = createqueue();
        int choice, val;
        do {
            MenuQueue();
            scanf("%d", &choice);
            switch(choice) {
                case 1:
                    prinf("[+]> Value to enqueue : \n");
                    scanf("%d", &val);
                    enqueue(q, val);
                    break;
                case 2:
                    val = dequeue(q);
                    if (val != -1) {
                        printf("[-]> Value to dequeue : %d \n", val);
                    }
                    break;
                case 3:
                    printqueue(q);
                    break;
                case 0:
                    printf("[!]> Exit \n");
                    break;
                default:
                    printf("[!]> Invalid Choice \n");
            } 
        } while (choice != 0);
        freequeue(q);
    } else {
        printf("[!]> Invalid Choice, end of programm.");
    }
    return 0;
}