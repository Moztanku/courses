#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node{
    void* data;
    struct Node *next;
    struct Node *prev;
};

struct CircularList{
    struct Node *head;
    struct Node *tail;
};

void push_CL(struct CircularList *l, void *data){
}

int main(){

}