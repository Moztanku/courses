#include <signal.h> 
#include <stdio.h>
#include <sys/wait.h> 
#include <unistd.h>

void handle(int sig){   //  signal handler
    printf("Received signal %d\n", sig);
    fflush(stdout);
}


int main(int argc, char const *argv[])
{
    int pid = fork();   // create child process
    if (pid == 0)   // child process
    {
        for(int i = 1; i <= 31; i++){   // register signal handler for all signals
            signal(i, handle);
        }
        while(1);  // infinite loop
    }
    else    // parrent process
    {
        for(int i = 1; i <= 31; i++){   // send all signals to child process
            if( i == SIGKILL || i == SIGSTOP )  // SIGKILL and SIGSTOP cannot be caught or ignored
                continue;
            sleep(1);
            kill(pid, i);   // send signal
        }
        kill(pid, SIGKILL); // kill child process
        wait(NULL); // wait for child process to terminate
    }
    return 0;
}
