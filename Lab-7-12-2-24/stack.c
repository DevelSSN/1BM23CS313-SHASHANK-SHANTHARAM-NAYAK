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

void push(node** head, int value) {
    node *new = createNode(value);
    new->next = *head;
    *head = new;
    printf("Inserted %d at begin\n", value);
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

void pop(node** head) {
    if (*head == NULL) {
        return;
    }
    node* temp = *head;
    *head = (*head)->next;
    printf("Popped %d\n",temp->value);
    free(temp);
}

void top(node* head)
{
	(head!=NULL)?printf("%d\n",head->value):printf("Empty\n");
}

int main() {
    node* head = NULL;

    printf("1. Push\n2. Pop\n3. Display\n4. Top\n0. Exit\n");

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
                push(&head, x);
                break;
            }
            case 3:
                display(head);
                break;
            case 2:
                pop(&head);
                break;
	    case 4: top(head);
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
