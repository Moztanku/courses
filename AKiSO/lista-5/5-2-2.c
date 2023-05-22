#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    for(int i = 1; i < 32; i++){
        printf("Sending signal %d to init\n", i);
        sleep(1);
        int result = kill(1, i);
        if(result == -1){
            perror("kill");
        }
    }
    return 0;
}