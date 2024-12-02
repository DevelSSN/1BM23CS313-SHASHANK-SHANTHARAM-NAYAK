#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node node;
struct node {
    int value;
    node* next;
};

node* createNode(int x) {
    node *n = (node*)malloc(sizeof(node));
    n->value = x;
    n->next = NULL;
    return n;
}

void enqueue(node** head, node** tail, int value) {
    node *new = createNode(value);
    new->next = *head;
    if(*head == NULL)
	    *tail=new;
    *head = new;
    printf("Enqueued %d\n", value);
}



void display(node* head) {
    node* temp = head;
    if (temp == NULL) {
        printf("No element\n");
        return;
    }
    while (temp != NULL) {
        printf("%d\t", temp->value);
        temp = temp->next;
    }
    printf("\n");
}



void dequeue(node** head, node** tail) {
    if (*tail == NULL) {
        return;
    }
    node* temp = *head;
    while (temp->next != NULL && temp->next->next != NULL) {
        temp = temp->next;
    }
    printf("Dequeued %d\n",(*tail)->value);
    if(temp->next==NULL)
    {
	    free(*tail);
	    *head = *tail = NULL;
	    return;
    }
    temp->next = NULL;
    free(*tail);
    *tail = temp;
}



int main() {
    node* head = NULL;
    node* tail = NULL;
    printf("1. Enqueue\n2. Dequeue\n3. Display\n0. Exit\n");

    int choice;
    char c;
    do {
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int x;
                printf("Enter node value: ");
                scanf("%d", &x);
                enqueue(&head, &tail, x);
                break;
            }
            case 2: {
                dequeue(&head, &tail);
                break;
            }
            case 3:
                display(head);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice\n");
        }

        if ((c = getchar()) == '\n' || c == EOF) {}

    } while (choice != 0);

    printf("\nExiting...\n");
    return 0;
}
