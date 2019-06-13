#include <unistd.h>
#include <stdio.h> //printf
#include <stdlib.h> //alloc
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t myPid=getpid();
    pid_t PPid=getppid();
    //printf("my pid: %d parent pid: %d\n", myPid, PPid);
    pid_t childPid=fork();
    if(childPid==0){
        //child (proces potomny)
        execl("/bin/ls", "ls", "-l", NULL); //odapala inny plik np. main2.c
        _exit(2);
    }
    else{
        //parent
        wait(NULL); //wait(&status) to samo waitpid(-1, NULL, WNOHANG)
        //WNOHANG-nie czeka tylko idzie dalej, trzeba jeszcze raz wywolac wait()
        char status[500];
        waitpid(childPid, &status, 0);
        printf("WYNIK: %s\n", status);
    }
    return 0;
}