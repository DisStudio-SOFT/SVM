#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "core_settings.h"

typedef struct _stack {
    uint8_t *arr;
    size_t pos;
    size_t size;
} _stack;

_stack stack;

void stack_push(_stack *ptr, uint8_t value){
    if(ptr->pos > ptr->size){
        ptr->size += 32;
        ptr->arr = realloc(ptr->arr, ptr->size * sizeof(uint8_t));
        if(!ptr->arr)
            perror("memory");
    }
    ptr->arr[ptr->pos++] = value;
}

void error(char *msg){
    printf("error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void run(size_t size, uint8_t *code){
    stack.arr =  malloc(STACK_INITSIZE * sizeof(uint8_t));
    stack.pos =  0;
    stack.size = STACK_INITSIZE;
    for(size_t pos=0; pos < size; pos++){
        switch(code[pos]){
            case STACK_PUSH:
                stack_push(&stack, code[pos+1]);
                break;
            case STACK_POP:
                stack.arr[--stack.pos] = 0;
                break;
            case STACK_CLEAR:
                free(stack.arr);
                stack.arr =  malloc(STACK_INITSIZE * sizeof(uint8_t));
                stack.pos =  0;
                stack.size = STACK_INITSIZE;
                break;
            case STACK_JUMP_IF_ZERO:
                if(stack.arr[stack.pos-1] == 0x00){
                    pos = code[pos+1] + code[pos+2] * 10 + code[pos+3] * 100 + code[pos+4] * 100;
                    pos-=2;
                } else {
                    pos+=4;
                }
                if(pos > size){
                    error("Segmentation memory");
                }
                break;
            case STACK_CALL:
                switch(code[pos+1]){
                    case SC_STACK_PUTCHAR:
                        printf("%c", stack.arr[stack.pos-1]);
                        break;
                    case SC_STACK_EXIT:
                        exit(stack.arr[stack.pos-1]);
                        break;
                }
                break;
        }
    }
    free(stack.arr);
}