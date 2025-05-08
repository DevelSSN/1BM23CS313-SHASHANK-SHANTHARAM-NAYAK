#include <stdio.h>
#include <stdlib.h>

typedef struct part part;
struct part{
	int size;
	int pro;
	part* next;
};

part* create()
{
	part* node = (part*)malloc(sizeof(part));
	node->size=0;
	node->next=NULL;
	node->pro=-1;
	return node;
}
void mempart(part* ptr, int pro, int size)
{
	part* npart = create();
	npart->size = size;

}
