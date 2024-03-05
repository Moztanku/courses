#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct Node{
    void* data;
    struct Node *next;
};

struct List{
    struct Node *head;
    struct Node *tail;
};

void push_L(struct List *l, void *data){
    if(l->head == NULL){
        l->head = malloc(sizeof(struct Node));
        l->head->data = malloc(sizeof(data));
        memcpy(l->head->data, data, sizeof(data));
        l->head->next = NULL;
        l->tail = l->head;
    } else {
        l->tail->next = malloc(sizeof(struct Node));
        l->tail->next->data = malloc(sizeof(data));
        memcpy(l->tail->next->data, data, sizeof(data));
        l->tail = l->tail->next;
        l->tail->next = NULL;
    }
}

void remove_L(struct List *l, int index){
    struct Node *n = l->head;
    for(int i = 0; i < index; i++){
        if(n->next == NULL)
            return;
        else
            n = n->next;
    }
    struct Node *next = n->next;
    free(n->data);
    *n = *(n->next);
    free(next);
}

void* get_L(struct List *l, int index){
    struct Node *n = l->head;
    for(int i = 0; i < index; i++){
        if(n->next != NULL)
            n = n->next;
        else
            return NULL;
    }
    return n->data;
}

void merge_L(struct List *l1, struct List *l2){
    if(l1->head == NULL){   // l1 is empty so just copy l2
        *l1 = *l2;
    } else if(l2->head != NULL){
        l1->tail->next = l2->head;
        l1->tail = l2->tail;
    } else { // l2->head == NULL so nothing to do
        return;
    }
}

void print_L(struct List *l){
    struct Node *n = l->head;

    printf("head->");
    while(n != NULL){
        printf("%i->", *(int*)n->data);
        n = n->next;
    }
    printf("tail\n");
}

int count_L(struct List *l){
    int count = 0;
    struct Node *n = l->head;
    while(n != NULL){
        count++;
        n = n->next;
    }
    return count;
}

struct List list_int = {NULL, NULL};

void push_(int data){
    push_L(&list_int, &data);
}

void remove_(int index){
    remove_L(&list_int, index);
}

int get_(int index){
    void* data = get_L(&list_int, index);
    return data != NULL? *(int*)data : -1;
}

void TEST_randomAndSameAccess(const int size, const int n, const int k);
void TEST_merge(const int size1, const int size2);

int main(){
        srand(time(NULL));
        // TEST_randomAndSameAccess(100000, 100, 1000);
        TEST_merge(10, 10);
        return 0;
}

void TEST_randomAndSameAccess(const int size, const int n, const int k){
    for(int i = 0; i < size; i++){
        printf("Pushing %i\n", i);
        int r = rand();
        push_(r);
    }

    int sameElements[n];
    clock_t accesTimes[n];
    for(int i = 0; i < n; i++){
        int r = rand() % size;
        sameElements[i] = r;
    }

    // Access to same element k times
    for(int i = 0; i < n; i++){
        printf("Running same element %i\n", i);
        clock_t start = clock();

        for(int j = 0; j < k; j++){
            get_(sameElements[i]);
        }

        accesTimes[i] = clock() - start;
    }

    clock_t randomAccesTimes[n];
    // Access to random elements k times
    int randomElements[k];

    for(int i = 0; i < n; i++){
        printf("Running random element %i\n", i);
        for(int j = 0; j < k; j++){
            int r = rand() % size;
            randomElements[j] = r;
        }
        clock_t start = clock();

        for(int j = 0; j < k; j++){
            get_(randomElements[j]);
        }

        randomAccesTimes[i] = clock() - start;
    }

    // Print results
    double sameAccessTime = 0;
    for(int i = 0; i < n; i++){
        sameAccessTime += (double)accesTimes[i] / CLOCKS_PER_SEC;
    }

    double randomAccessTime = 0;
    for(int i = 0; i < n; i++){
        randomAccessTime += (double)randomAccesTimes[i] / CLOCKS_PER_SEC;
    }

    printf("\nSame element access time: %f,\nrandom element access time: %f\n", sameAccessTime, randomAccessTime);
}

void TEST_merge(const int size1, const int size2){
    struct List list1 = {NULL, NULL};
    struct List list2 = {NULL, NULL};

    printf("Filling list 1 with %i elements\n", size1);
    for(int i = 0; i < size1; i++){
        int r = rand()%2;
        push_L(&list1, &r);
    }

    printf("Filling list 2 with %i elements\n", size2);
    for(int i = 0; i < size2; i++){
        int r = rand()%2;
        push_L(&list2, &r);
    }

    printf("Printing lists before merging:\n");
    print_L(&list1);
    print_L(&list2);

    merge_L(&list1, &list2);
    printf("Printing lists after merging:\n");
    print_L(&list1);
}