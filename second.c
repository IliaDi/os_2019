#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*int myn;
pid_t mypid;
int curri;

void printFork() {
	printf("Child%d %d is executed (%d) " ,curri , mypid , myn );
	sleep(1);
}*/

int main(int argc, char **argv) {
	int status;
    //pid_t pid1, pid2 ,pid3,pid4,pid5;
    pid_t c1, c2, c3, c4, c5, mypid;

    c1 = fork();
    if (c1 < 0) { printf("fork produced error"); }
    else if (c1 == 0) {//c1 code
	    //pid1 = getpid();
		//signal(SIGCONT, printFork );
		kill(getpid(), SIGSTOP);
        printf("c1\n");		
        exit(0);
    } else {
        c2 = fork();
        if (c2 < 0) { printf("fork produced error"); }
        else if (c2 == 0) {//c2 code
		    //pid2 = getpid();
			//signal(SIGCONT, printFork );
			kill(getpid(), SIGSTOP);
			printf("c2\n");
            exit(0);
        } else {
            c3 = fork();
            if (c3 < 0) { printf("fork produced error"); }
            else if (c3 == 0) {//c3 code
			    //pid3 = getpid();
				//signal(SIGCONT, printFork );
				kill(getpid(), SIGSTOP);
				printf("c3\n");
                exit(0);
            } else {
                c4 = fork();
                if (c4 < 0) { printf("fork produced error"); }
                else if (c4 == 0) {//c4 code
				    //pid4 = getpid();
					//signal(SIGCONT, printFork );
					kill(getpid(), SIGSTOP);
					printf("c4\n");
                    exit(0);
                } else {

                    c5 = fork();
                    if (c5 < 0) { printf("fork produced error"); }
                    else if (c5 == 0) {//c5 code
					    //pid5 = getpid();
						//signal(SIGCONT, printFork );
						kill(getpid(), SIGSTOP);
						printf("c5\n");
                        exit(0);
                    } else {
                        //F
						//for (int j=0; j<4; j++){
							for(int i=1; i<argc;i++){
								//myn=j+1;
								bool check=true;
								if (strcmp(argv[i],"1")==0){ mypid= c1; /*curri=1;*/ }
								else if (strcmp(argv[i],"2")==0){ mypid= c2; /*curri=2;*/}
								else if (strcmp(argv[i],"3")==0){ mypid= c3; /*curri=3;*/ }
								else if (strcmp(argv[i],"4")==0){ mypid= c4; /*curri=4;*/ }
								else if (strcmp(argv[i],"5")==0){ mypid= c5; /*curri=5;*/ }
							    else {printf("There are only 5 children\n");check=false;}
								if(check) {kill(mypid, SIGCONT);
								sleep(5);
								/*if(j!=3){kill(mypid, SIGSTOP);}
								else{kill(mypid, SIGTERM);}}*/
							    kill(mypid, SIGTERM);}
								
							}
						//}
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