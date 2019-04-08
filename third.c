#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <string.h> 
#include <sys/wait.h>


int main(int argc, char **argv) {
    int status,result, counter,i;
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
	int pipearray[2*n];
	for(i=0; i<n; i++){
		pipe(pipearray+2*i);
	}
	int parraycounter[2*n];
	for(i=0; i<n; i++){
		pipe(parraycounter+2*i);
	}
    pid_t c[n];

    for (i = 0; i < n; i++) {
        c[i] = fork();

        if (c[i] < 0) {
            fprintf(stderr, "fork Failed");
            return 1;
        }
            // child process
        else if(c[i]==0) {
			while(counter!=k){
				close(pipearray[i*2+1]);
				read(pipearray[i*2], &result, sizeof(result));
				close(parraycounter[i*2+1]);
				read(parraycounter[i*2], &counter, sizeof(counter));
				counter++;
				result=result*counter;
				int temp = result/counter;
				if(i==0){
					printf("H C1 diavazei %d apo ton patera grafei %d sthn C%d\n", temp,result,i+2);
					}
				else if(i==(n-1)){
					printf("H C%d diavazei %d apo C%d grafei %d sthn C1\n", i+1, temp,i ,result);
					}
				else{
					printf("H C%d diavazei %d apo C%d grafei %d sthn C%d\n", i+1, temp,i ,result,i+2);
				}
				if(counter==k){
					exit(0);
				}
				else if (i==(n-1 )){
					close(pipearray[0]);
					write(pipearray[1],&result, sizeof(result));
					close(parraycounter[0]);
					write(parraycounter[1], &counter, sizeof(counter));
				}
				else{
					close(pipearray[i*2+2]);
					write(pipearray[i*2+3],&result, sizeof(result));
					close(parraycounter[i*2+2]);
					write(parraycounter[i*2+3], &counter, sizeof(counter));
				}
			}
			
            exit(0);
        }
		//father 
		else if((c[i]>0) && (i==n-1)){
			result=1;
			counter=0;
			close(pipearray[0]);
			write(pipearray[1], &result, sizeof(result));
			close(parraycounter[0]);
			write(parraycounter[1],&counter, sizeof(counter));
			
			wait(NULL);
			exit(0);
			
		}
	}
	return 0;
}