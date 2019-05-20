#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//prepei na ulopoiisoume tis wait kai signal twn semaphores me pipes

int s_pipe[2];
void critical(int, pid_t);
void non_critical(int, pid_t);
void my_wait();
void my_signal();

int main(int argc, char **argv) {
    int status;
    pid_t c[3];
	pipe( s_pipe );
    c[0] = fork();
    if (c[0] < 0) { printf("fork produced error"); }
    else if (c[0] == 0) {//c1 code
        my_wait();
		critical(1, getpid() );
		my_signal();
		non_critical(1, getpid() );
		non_critical(1, getpid() );
		my_wait();
		critical(1, getpid() );
		my_signal();
		non_critical(1, getpid() );
		my_wait();
		critical(1, getpid() );
		my_signal();
        exit(0);
    } else {
        c[1] = fork();
        if (c[1] < 0) { printf("fork produced error"); }
        else if (c[1] == 0) {//c2 code
		    non_critical(2, getpid() );
            my_wait();
		    critical(2, getpid() );
		    my_signal();
			non_critical(2, getpid() );
            my_wait();
		    critical(2, getpid() );
		    my_signal();
			non_critical(2, getpid() );
            my_wait();
		    critical(2, getpid() );
		    my_signal();
            exit(0);
        } else {
            c[2] = fork();
            if (c[2] < 0) { printf("fork produced error"); }
            else if (c[2] == 0) {//c3 code
                my_wait();
		        critical(3, getpid() );
		        my_signal();
				non_critical(3, getpid() );
				my_wait();
		        critical(3, getpid() );
		        my_signal();
				non_critical(3, getpid() );
				my_wait();
		        critical(3, getpid() );
		        my_signal();
				non_critical(3, getpid() );
                exit(0);
            } else { //F

                wait(&status);
                exit(0);
            }
            wait(&status);
            exit(0);
        }
        wait(&status);
        exit(0);
    }

}
void my_wait(){
	int res=1;
	while (res!=0){
	read(s_pipe[0], &res, sizeof(res));
	}
	res=1;
	write(s_pipe[1], res, sizeof(res));
	
}
void my_signal(){
	int x=0;
	write(s_pipe[1], x, sizeof(x));
}

void critical(int i, pid_t me){
	for(int j=0; j<5; j++){
		printf("Child%d %d executes a critical section", i, me);
	}
}

void non_critical(int i, pid_t me){
	for(int j=0; j<7; j++){
		int temp;
		read(s_pipe[0], &temp, sizeof(temp));
		while(temp==0){
		printf("Child%d %d executes a non critical section", i, me);
		read(s_pipe[0], &temp, sizeof(temp));}
	}
}