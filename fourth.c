#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h> 
//prepei na ulopoiisoume tis wait kai signal twn semaphores me pipes
typedef struct {
 int value;
 queue_t waiting;
} Semaphore; 
int s_pipe[2];
void critical(int, pid_t);
void non_critical(int, pid_t);
void my_init(Semaphore*, int); //dimiourgei pipe upotithetai, arxikopoiei kai value
void my_wait();
void my_signal();

int main(int argc, char **argv) {
    int status;
    pid_t c[3];
    Semaphore *se; //enan simaforo theloume?
    Semaphore* s=my_init(se, 1 ); //xm
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
Semaphore* my_init(Semaphore* se, int x){
	pipe(s_pipe[0]);
	pipe(s_pipe[1]);
	close(s_pipe[1]);
	write(s_pipe[0], x, sizeof(x));
	se.value=x;
	return se;
}
void my_wait(){
	int res=0;
	while (res<=0){
	close(s_pipe[1]);
	read(s_pipe[0], &res, sizeof(res));}
	res--;
	close(s_pipe[1]);
	write(s_pipe[0], res, sizeof(res));
	
}
void my_signal(){
	int x=1;
	close(s_pipe[1]);
	write(s_pipe[0], x, sizeof(x));
}

void critical(int i, pid_t me){
	for(int j=0; j<5; j++){
		printf("Child%d %d executes a critical section", i, me);
	}
}

void non_critical(int i, pid_t me){
	for(int j=0; j<7; j++){
		printf("Child%d %d executes a non critical section", i, me);
	}
}