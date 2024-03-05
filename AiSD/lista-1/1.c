#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Stack
{
    void* data;
    struct Stack *next;
};

void push_S(struct Stack *s, void *data)
{
    if(s->data == NULL){
        s->data = malloc(sizeof(data));
        memcpy(s->data, data, sizeof(data));
    } else {
        if(s->next == NULL)
            s->next = malloc(sizeof(struct Stack));
        push_S(s->next, data);
    }
}

void* pop_S(struct Stack *s)
{
    if(s->next != NULL){
        void* data = pop_S(s->next);
        if(s->next->data == NULL){
            free(s->next);
            s->next = NULL;
        }
        return data;
    }
    else if(s->data != NULL){
        void* data = s->data;
        s->data = NULL;
        return data;
    }
    else
        return NULL;
}

void push_Q(struct Stack *s, void *data){
    push_S(s, data);
}

void* pop_Q(struct Stack *s){
    if(s->data != NULL){
        void* data = s->data;
        if(s->next != NULL){
            struct Stack *next = s->next;
            *s = *(s->next);
            free(next);
        } else {
            s->data = NULL;
        }
        return data;
    } else {
        return NULL;
    }
}

struct Stack intStack;
struct Stack intQueue;

void pushS(int data)
{
    push_S(&intStack, &data);
}
int popS()
{
    int* data = pop_S(&intStack);
    int ret = data != NULL ? *(int*)data : -1;
    free(data);
    return ret;
}

void pushQ(int data)
{
    push_Q(&intQueue, &data);
}
int popQ()
{
    int* data = pop_Q(&intQueue);
    int ret = data != NULL ? *(int*)data : -1;
    free(data);
    return ret;
}

int main()
{
    for(int i = 0; i < 100; i++){   // Push 100 numbers to the stack and queue
        pushS(i);
        pushQ(i);
    }

    printf("LIFO : FIFO\n");

    for(int i = 0; i < 100; i++){   // Pop 100 numbers from the stack and queue
        printf("%i : %i\n", popS(), popQ());
    }

    return 0;
}