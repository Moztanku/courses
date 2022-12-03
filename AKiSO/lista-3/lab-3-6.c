#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

void* thread(void* temp){
    int r = *(int*) temp;
    char str[16*30];
    
    for(int g = 0; g < 256; g++)
        for(int b = 0; b < 256; b++){
            // sprintf(
            //     str,
            //     "\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World\033[38;2;%i;%i;%imHello World",
            //     r,g,b*16,
            //     r,g,b*16+1,
            //     r,g,b*16+2,
            //     r,g,b*16+3,
            //     r,g,b*16+4,
            //     r,g,b*16+5,
            //     r,g,b*16+6,
            //     r,g,b*16+7,
            //     r,g,b*16+8,
            //     r,g,b*16+9,
            //     r,g,b*16+10,
            //     r,g,b*16+11,
            //     r,g,b*16+12,
            //     r,g,b*16+13,
            //     r,g,b*16+14,
            //     r,g,b*16+15
            // );
            // write(0,str,480);
            printf("\033[38;2;%i;%i;%imHello World",r,g,b);
        }
    return NULL;
}

int main(void){
    
    clock_t begin = clock();
    int n = 255;

    pthread_t thr[n];
    int r;
    for(r = 1; r < n; r++){
        pthread_create(&thr[r],NULL,thread,&r);
        pthread_detach(thr[r]);
    }
    pthread_join(thr[0],NULL);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n%f\n",time_spent);
    return 0;
}
