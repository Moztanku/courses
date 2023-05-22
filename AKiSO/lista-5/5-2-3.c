#include <signal.h> 
#include <stdio.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <time.h>
#include <string.h>

void handle(int sig){
    static int count = 0;
    char buffer[100];
    sprintf(buffer, "Received signal %d, count = %d\n", sig, ++count);
    write(1, buffer, strlen(buffer));
}

int main(int argc, char const *argv[])
{
    int pid = fork();
    if (pid == 0)
    {
        signal(SIGUSR1, handle);
        while(1);
    }
    else
    {
        // send SIGUSR1 to child process 10000 times
        sleep(1);
        for(int i = 0; i < 10000; i++){
            // sleep for 1 ms
            struct timespec ts = {0,1000000};
            nanosleep(&ts, NULL);

            kill(pid, SIGUSR1);
        }
        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);
    }
}
