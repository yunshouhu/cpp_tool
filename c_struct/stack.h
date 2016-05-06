#pragma once

#include <stdint.h>

struct stack {
	uint8_t *elements;
	uint32_t count;
	uint32_t capacity;
	uint32_t elementSize;
};

void stackInitialize(struct stack *stack, uint32_t elementSize);
void stackFree(struct stack *stack);

void *stackGet(struct stack *stack, uint32_t index);
void *stackPop(struct stack *stack);
void stackPush(struct stack *stack, void *data);
void stackRemove(struct stack *stack, uint32_t index);
void stackClear(struct stack *stack);
uint32_t stackSize(struct stack *stack);
int32_t stackIndexOf(struct stack *stack, void *element);
