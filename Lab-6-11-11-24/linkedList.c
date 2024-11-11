#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node node;
struct node {
    int value;
    struct node *next;
};

node* createNode(int x) {
    node *n = (node*)malloc(sizeof(node));
    n->value = x;
    n->next = NULL;
    return n;
}

void inst_beg(node* head, int value) {
    node *new = createNode(value);
    new->next = head->next;
    head->next = new;
    printf("Inserted %d at begin\n", value);
}

void inst_end(node* head, int value) {
    node *new = createNode(value);
    node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
    printf("Inserted %d at end\n", value);
}

void display(node* head) {
    node *temp = head->next;
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

void del_beg(node* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    node* temp = head->next;
    head->next = temp->next;
    free(temp);
    printf("Deleted from the beginning\n");
}

void del_end(node* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    node* temp = head;
    while (temp->next != NULL && temp->next->next != NULL) {
        temp = temp->next;
    }
    node* toDelete = temp->next;
    temp->next = NULL;
    free(toDelete);
    printf("Deleted from the end\n");
}

void del_sp(node* head, int pos) {
    if (head == NULL || head->next == NULL) {
        printf("List is empty\n");
        return;
    }

    node* temp = head;
    for (int i = 1; i < pos; i++) {
        if (temp->next == NULL) {
            printf("Position not found\n");
            return;
        }
        temp = temp->next;
    }

    node* toDelete = temp->next;
    if (toDelete != NULL) {
        temp->next = toDelete->next;
        free(toDelete);
        printf("Deleted from position %d\n", pos);
    }
}

int main() {
    node *head = (node *)malloc(sizeof(node));
    head->next = NULL;

    printf("1. Inst-beg\n2. Inst-end\n3. Display\n4. Del-beg\n5. Del-end\n6. Del-sp\n0. Exit\n");

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
                inst_beg(head, x);
                break;
            }
            case 2: {
                int y;
                printf("Enter node value: ");
                scanf("%d", &y);
                inst_end(head, y);
                break;
            }
            case 3:
                display(head);
                break;
            case 4:
                del_beg(head);
                break;
            case 5:
                del_end(head);
                break;
            case 6: {
                int pos;
                printf("Enter position: ");
                scanf("%d", &pos);
                del_sp(head, pos);
                break;
            }
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
