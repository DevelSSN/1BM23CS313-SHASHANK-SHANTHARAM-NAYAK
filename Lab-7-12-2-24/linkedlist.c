#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node node;
struct node {
    int value;
    node* next;
};

node* createNode(int x) {
    node* n = (node*)malloc(sizeof(node));
    n->value = x;
    n->next = NULL;
    return n;
}

void inst_beg(node** head, int value) {
    node *new = createNode(value);
    new->next = *head;
    *head = new;
    printf("Inserted %d at begin\n", value);
}

void inst_end(node* head, int value) {
    node* new = createNode(value);
    node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
    printf("Inserted %d at end\n", value);
}

void display(node* head) {
    node *temp = head;
    if (temp == NULL) {
        printf("No element\n");
        return;
    }
    while (temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}


void sort(node* head)
{
        if (head == NULL) return;
        node* temp1 = head;
        while (temp1 != NULL)
        {
                node* temp2 = temp1->next;
                while (temp2 != NULL)
                {
                        if (temp2->value < temp1->value)
                        {
                                int tmp = temp1->value;
                                temp1->value = temp2->value;
                                temp2->value = tmp;
                        }
                        temp2 = temp2->next;
                }
                temp1 = temp1->next;
        }
        display(head);
}


void reverse(node** headptr)
{
        node* head = *headptr;
        node* prev = NULL;
        node* tmp = head ? head->next : NULL;

        while (tmp != NULL)
        {
                head->next = prev;
                prev = head;
                head = tmp;
                tmp = tmp->next;
        }
        head->next = prev; // Don't forget to point the new tail to NULL
        *headptr = head;
        display(head);
}


node* concat(node* h1, node* h2) {
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;

    node* mh = NULL; 
    node* tmp = NULL;

    // Initializing the head of the merged list by comparing the first nodes
    if (h1->value < h2->value) {
        mh = h1;
        h1 = h1->next;
    } else {
        mh = h2;
        h2 = h2->next;
    }
    
    tmp = mh; // set tmp to the head of the merged list
    
    // Merging the two lists
    while (h1 != NULL && h2 != NULL) {
        if (h1->value < h2->value) {
            tmp->next = h1;
            h1 = h1->next;
        } else {
            tmp->next = h2;
            h2 = h2->next;
        }
        tmp = tmp->next; // Move tmp to the last node
    }

    // If one of the lists is not empty, append the rest of the remaining list
    if (h1 != NULL) {
        tmp->next = h1;
    } else {
        tmp->next = h2;
    }

    // Display the merged list
    display(mh);

    return mh;
}

int main() {
    node* h1 = NULL;
    node* h2 = NULL;
    printf("1. Inst-beg\n2. Inst-end\n3. Sort\n4. Reverse\n5. Concat\n6. Display\n0. Exit\n");

    int choice;
    char c;
    do {
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int x,y;
                printf("Enter node value and list: ");
                scanf("%d%d", &x, &y);
                (y==1)?inst_beg(&h1, x):inst_beg(&h2,x);
                break;
            }
            case 2: {
                int x,y;
                printf("Enter node value and list: ");
                scanf("%d%d", &x, &y);
                (y==1)?inst_end(h1, x):inst_end(h2,x);
		break;
            }
            case 3:{
		int y;
                printf("Enter list no: ");
		scanf("%d",&y);
                sort((y==1)?h1:h2);
                break;
		}
            case 4:{
                int y;
                printf("Enter list no: ");
		scanf("%d",&y);
                reverse((y==1)?&h1:&h2);
                break;
		   }
            case 5:
                node* newList = concat(h1,h2);
                break;
            case 6: {
		int y;
                printf("Enter list no: ");
		scanf("%d", &y);
		display((y==1)?h1:h2);
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
