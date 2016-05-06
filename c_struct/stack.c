#include "stack.h"

#include <stdlib.h>
#include <string.h>

void stackInitialize(struct stack *stack, uint32_t elementSize)
{
	stack->elements = NULL;
	stack->count = stack->capacity = 0;
	stack->elementSize = elementSize;
}

void stackFree(struct stack *stack)
{
	free(stack->elements);
}

void *stackGet(struct stack *stack, uint32_t index)
{
	return stack->elements + stack->elementSize * index;
}

void *stackPop(struct stack *stack)
{
	if(stack->count > 0) {
		return stack->elements + --stack->count * stack->elementSize;
	}
	else {
		return NULL;
	}
}

void stackPush(struct stack *stack, void *data)
{
	if(++stack->count > stack->capacity) {
		stack->capacity <<= 1;
		if(stack->capacity < stack->count) stack->capacity = stack->count;
		
		stack->elements = realloc(stack->elements, stack->elementSize * stack->capacity);
	}

	memcpy(stack->elements + stack->elementSize * (stack->count - 1), data, stack->elementSize);
}

void stackRemove(struct stack *stack, uint32_t index)
{
	if(index != --stack->count) {
		memmove(stack->elements + index * stack->elementSize, stack->elements + (index + 1) * stack->elementSize, (stack->count - index) * stack->elementSize);
	}
}

void stackClear(struct stack *stack)
{
	stack->count = 0;
}

uint32_t stackSize(struct stack *stack)
{
	return stack->count;
}

int32_t stackIndexOf(struct stack *stack, void *element)
{
	uint32_t i;

	for(i = 0; i < stack->count; ++i) {
		if(memcmp(element, stack->elements + stack->elementSize * i, stack->elementSize) == 0) return i;
	}

	return -1;
}