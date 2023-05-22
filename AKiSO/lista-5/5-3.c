#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define DEBUG 0

const char* builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int lsh_cd(char **argv);    // change directory
int lsh_help(char **argv);  // print help
int lsh_exit(char **argv);  // exit shell

int lsh_execute(char **argv, int *argc);
int lsh_run_foreground(char **argv);
int lsh_run_background(char **argv);
char** lsh_read_line(int *argc);
void lsh_free(char** argv, int argc);

int (*builtin_func[]) (char **) = { // array of function pointers
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);    // number of builtins
}

int main(int argc, char const *argv[])
{
    int status = 0;
    while(status != -1){
        int argc = 0;   // number of arguments
        char** argv = lsh_read_line(&argc); // read line
        status = lsh_execute(argv,&argc); // execute command

        if(DEBUG){
            printf("argc = %d, status = %d\n", argc, status);
            for(int i = 0; i < argc; i++){
                printf("argv[%d] = %s\t", i, argv[i]);
            }
            printf("\n");
        }
        lsh_free(argv, argc);   // freeing memory
    }

    return 0;
}

int lsh_cd(char **argv){
    if(argv[1] == NULL){
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
        return -1;
    }
    else{
        if(chdir(argv[1]) != 0){
            perror("lsh");  // print error message
        }
    }
    return 0;
}
int lsh_help(char **argv){
    printf("Builtin commands:\n");
    for(int i = 0; i < lsh_num_builtins(); i++){
        printf(" %s \t", builtin_str[i]);   // print builtin commands
    }
    printf("\n");
    return 0;
}
int lsh_exit(char **argv){
    return -1;   // exit shell
}

int lsh_execute(char **argv, int *argc){
    if(*argc == -1){ // error or EOF
        return -1;
    }
    if(*argc == 0){  // empty line
        return 0;
    }
    for(int i = 0; i < lsh_num_builtins(); i++){    // check if command is builtin
        if(strcmp(argv[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(argv);
        }
    }
    if(argv[*argc - 1][0] == '&'){ // check if command is to be run in background
        free(argv[*argc - 1]);   // free memory
        (*argc)--; // decrease number of arguments
        argv[*argc] = NULL; // set last argument to NULL
        return lsh_run_background(argv);    // run command in background
    }
    else{
        return lsh_run_foreground(argv);    // run command in foreground
    }
}
int lsh_run_foreground(char **argv){
    int pid = fork();
    if(pid == 0){   // child process
        if(execvp(argv[0], argv) == -1){    // execute command
            perror("lsh");  // print error message
        }
        exit(EXIT_SUCCESS); // exit child process
    }
    else if(pid < 0){   // error forking
        perror("lsh");  // print error message
        return 0;
    }
    else{   // parent process
        int status = 0;
        waitpid(pid, &status, WUNTRACED);   // wait for child process to terminate
        return status;
    }
}
int lsh_run_background(char **argv){
    
    int pid = fork();

    if(pid == 0){   // child process
        if(execvp(argv[0], argv) == -1){    // execute command
            perror("lsh");  // print error message
        }
        exit(EXIT_SUCCESS); // exit child process
    }
    else if(pid < 0){   // error forking
        perror("lsh");  // print error message
        return 0;
    }
    else{   // parent process
        int status = 0;
        waitpid(pid, &status, WNOHANG); // don't wait for child process to terminate
        signal(SIGCHLD, SIG_IGN);   // ignore SIGCHLD signal
        return status;
    }
}
char** lsh_read_line(int *argc){
    printf("\nlsh> ");
    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    read = getline(&line, &len, stdin); // read line
    if(read == -1){ // error or EOF
        free(line);
        (*argc) = -1; // set argc to -1 to indicate error or EOF
        return NULL;
    }

    line[strlen(line) - 1] = '\0'; // remove newline character
    if(line[strlen(line) - 1] == '&'){ // check if command is to be run in background
        line[strlen(line) - 1] = ' '; // remove & character
        line[strlen(line)] = '&'; // add & character
    }

    char delim[] = " ";
    char* ptr = strtok(line, delim);
    char** argv = NULL; // array of arguments

    while (ptr != NULL) // split line into tokens
    {
        argv = (char**)realloc(argv, sizeof(char*) * (*argc + 1));  // make space for new argument
        argv[*argc] = (char*)malloc(sizeof(char) * (strlen(ptr)));  // make space for argument
        strcpy(argv[*argc], ptr);   // copy token to argv
        (*argc)++;  // increment number of arguments
        ptr = strtok(NULL, delim); // get next token
    }

    free(line); 
    return argv;    // return array of arguments
}
void lsh_free(char** argv, int argc){
    for(int i = 0; i < argc; i++){
        free(argv[i]);  // free each argument
    }
    free(argv); // free array of arguments
}

#undef DEBUG