#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct part part;
struct part {
    int size;
    int pro;
    part* next;
};

part* create()
{
    part* node = (part*)malloc(sizeof(part));
    node->size = 0;
    node->next = NULL;
    node->pro = -1;  // -1 means the partition is free
    return node;
}

void mempart(part* ptr, int pro, int size)
{
    part* npart = create();
    npart->size = ptr->size - size;
    npart->next = ptr->next;
    ptr->pro = pro;
    ptr->size = size;
    ptr->next = npart;
}

void worst_fit(part* head, int pro, int size)
{
    part* temp = head;
    part* largest = NULL;
    while (temp != NULL)
    {
        if (temp->pro == -1 && temp->size >= size) {
            if (largest == NULL || temp->size > largest->size)
                largest = temp;
        }
        temp = temp->next;
    }
    if (largest != NULL) {
        mempart(largest, pro, size);
    }
}

void first_fit(part* head, int pro, int size)
{
    part* temp = head;
    while (temp != NULL)
    {
        if (temp->pro == -1 && temp->size >= size) {
            mempart(temp, pro, size);
            break;
        }
        temp = temp->next;
    }
}

void best_fit(part* head, int pro, int size)
{
    part* temp = head;
    part* best = NULL;
    while (temp != NULL)
    {
        if (temp->pro == -1 && temp->size >= size) {
            if (best == NULL || temp->size < best->size)
                best = temp;
        }
        temp = temp->next;
    }
    if (best != NULL) {
        mempart(best, pro, size);
    }
}

void printPart(part* head)
{
    part* temp = head;
    while (temp != NULL)
    {
        if (temp->pro == -1) {
            printf("Empty:%d ", temp->size);
        } else {
            printf("P%d:%d ", temp->pro, temp->size);
        }
        temp = temp->next;
    }
    printf("\n");
}

part* clone(part* head)
{
    if (head == NULL) {
        return NULL;
    }

    part* newHead = create();
    newHead->size = head->size;
    newHead->pro = head->pro;
    part* temp = head->next;
    part* newTemp = newHead;

    while (temp != NULL) {
        part* newNode = create();
        newNode->size = temp->size;
        newNode->pro = temp->pro;
        newTemp->next = newNode;
        newTemp = newNode;
        temp = temp->next;
    }

    return newHead;
}

void random_allocate(part* head, int n, int p[])
{
    int allocated = rand() % (n + 1);  // Randomly allocate up to n processes
    printf("Randomly allocating %d processes...\n", allocated);
    for (int i = 0; i < allocated; i++) {
        int process_id = rand() % n;  // Random process to allocate
        int size = p[process_id];     // Size of the process
        part* temp = head;
        while (temp != NULL) {
            if (temp->pro == -1 && temp->size >= size) {  // Find a free partition
                mempart(temp, process_id, size);
                printf("Allocated P%d of size %d\n", process_id, size);
                break;
            }
            temp = temp->next;
        }
    }
}

void main()
{
    srand(time(0));  // Seed for random number generation

    part* head = create();
    int size;
    printf("Enter Memory size:");
    scanf("%d", &size);
    head->size = size;

    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int p[n];
    printf("Enter process sizes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    // Randomly allocate some processes before user input
    random_allocate(head, n, p); 

    while (true)
    {
        // Clone the head after random allocation
        part* clonedHead = clone(head);
        
        int choice;
        printf("1.First Fit 2.Best Fit 3.Worst Fit 4.Exit: ");
        scanf("%d", &choice);
        
        if (choice == 4) {
            break; // Exit the loop
        }

        switch (choice)
        {
            case 1:
                for (int i = 0; i < n; i++) {
                    first_fit(clonedHead, i, p[i]);
                }
                break;
            case 2:
                for (int i = 0; i < n; i++) {
                    best_fit(clonedHead, i, p[i]);
                }
                break;
            case 3:
                for (int i = 0; i < n; i++) {
                    worst_fit(clonedHead, i, p[i]);
                }
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        printPart(clonedHead);  // Print the partitions of the cloned list
    }
}
