#include "stack.h"
#include <stdlib.h> 
#include <stdio.h>



 struct StackElement* newElement(int in){
	struct StackElement* new = (struct StackElement*) malloc(sizeof(struct StackElement));
	new->data = in;
	new->next = NULL;
	return new;
}

int stackInit(intstack_t* self)
{
	self->size = 0;
	self->top = NULL;
	return 0;
}

void stackRelease(intstack_t* self)
{
	while (!stackIsEmpty(self)){
		stackPop(self);
	}
}

void stackPush(intstack_t* self, int i)
{
	struct StackElement* newStackElement = newElement(i);
	newStackElement->next = self->top;
	self->top = newStackElement;
}

int stackTop(const intstack_t* self)
{
	int data = (self->top)->data;
	return data;
}

int stackPop(intstack_t* self)
{
	if (self->top == NULL){
		fprintf(stderr, "Pop on empty Stack!\n");
        exit(1);
	}
	int data = (self->top)->data;	
	struct StackElement* temp = self->top;
	self->top = (self->top)->next;
	free(temp);
	return data;
}

int stackIsEmpty(const intstack_t* self)
{
	if (self->top){return 0;}
	return 1;
}

void stackPrint(const intstack_t* self)
{
}

int main()
{
	intstack_t stack;

	stackInit(&stack);
	
	stackPush(&stack, 1);
	stackPush(&stack, 2);
	stackPush(&stack, 3);
	
	while (!stackIsEmpty(&stack))
		printf("%i\n", stackPop(&stack));
	
	stackPop(&stack);
	
	stackRelease(&stack);
	return 0;
}