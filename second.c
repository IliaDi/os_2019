#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void sighandler(int);

int main(int argc, char **argv) {
	int status;
    pid_t c1, c2, c3, c4, c5, mypid;
	int n1 = 1, n2 = 1, n3 = 1, n4 = 1, n5 = 1;

    c1 = fork();
    if (c1 < 0) { printf("fork produced error"); }
    else if (c1 == 0) {//c1 code
	    signal(SIGCONT, sighandler);
	    pause();
		while(1){
			printf("Child1 %d is executed ( %d )\n", getpid() ,n1++);
			sleep(1);
		}
        exit(0);
    } else {
        c2 = fork();
        if (c2 < 0) { printf("fork produced error"); }
        else if (c2 == 0) {//c2 code
			signal(SIGCONT, sighandler);
	        pause();
			while(1){
			    printf("Child2 %d is executed ( %d )\n", getpid() , n2++);
			    sleep(1);
		    }
            exit(0);
        } else {
            c3 = fork();
            if (c3 < 0) { printf("fork produced error"); }
            else if (c3 == 0) {//c3 code
			    signal(SIGCONT, sighandler);
	            pause();
				while(1){
			        printf("Child3 %d is executed ( %d )\n", getpid(), n3++);
			        sleep(1);
		        }
                exit(0);
            } else {
                c4 = fork();
                if (c4 < 0) { printf("fork produced error"); }
                else if (c4 == 0) {//c4 code
				    signal(SIGCONT, sighandler);
	                pause();
					while(1){
			            printf("Child4 %d is executed ( %d )\n", getpid() , n4++);
			            sleep(1);
		             }
                    exit(0);
                } else {

                    c5 = fork();
                    if (c5 < 0) { printf("fork produced error"); }
                    else if (c5 == 0) {//c5 code
					    signal(SIGCONT, sighandler);
	                    pause();
						while(1){
			                printf("Child5 %d is executed ( %d )\n", getpid(), n5++);
			                sleep(1);
		                }
                        exit(0);
                    } else {  
                        //F
						for (int j=0; j<4; j++){
								
							for(int i=1; i<argc; i++){
								bool check=true;
								if (strcmp(argv[i],"1")==0){ mypid= c1; }
								else if (strcmp(argv[i],"2")==0){ mypid= c2;}
								else if (strcmp(argv[i],"3")==0){ mypid= c3; }
								else if (strcmp(argv[i],"4")==0){ mypid= c4; }
								else if (strcmp(argv[i],"5")==0){ mypid= c5; }
							    else {printf("There are only 5 children\n");check=false;}
								sleep(2);
								if(check) {
									kill(mypid, SIGCONT);	
                                    sleep(3);
									if(j==3){ kill(mypid, SIGTERM);}
									else {	kill(mypid, SIGSTOP); }
									
								}	
								
							}
						}
                        wait(&status);
                        exit(0);
                    }
                    wait(&status);
                    exit(0);
                }
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

void sighandler(int signum){
	return;
}


