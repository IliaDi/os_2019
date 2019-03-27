#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char **argv) {
    int status,  temp;
	int pl[2];
	char count[12];
	if (pipe(pl)==-1){
		fprintf(stderr, "Pipe Failed");
        return 1;
	}
    int res = 1;
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    pid_t c[n];
    int fd1[n + 1][2];
    for (int i = 0; i <= n; i++) {
        if (pipe(fd1[i]) == -1) {
            fprintf(stderr, "Pipe Failed");
            return 1;
        } //pd[i][0]: read , pd[i][1]: write
    }
    char input_str[100];

    for (int i = 0; i < n; i++) {
        c[i] = fork();

        if (c[i] < 0) {
            fprintf(stderr, "fork Failed");
            return 1;
        }

            // Parent process
        else if (c[i] > 0) {
			close(pl[0]);
			strcpy(count,"1");
			write(pl[1], count, strlen(count)+1);
			close(pl[1]);
			
            close(fd1[0][0]);
            strcpy(input_str, "1");
            write(fd1[0][1], input_str, strlen(input_str) + 1);
            close(fd1[0][1]);

            wait(&status);
        }

            // child process
        else {
			close(pl[1]);
			read(pl[0],count, 12);
            while (atoi(count) <= k) {
				    close(pl[0]);
                    if(i==1 && (*l)!=1){ 
                        close(fd1[n + 1][1]);
                        char my_str[100];
                        read(fd1[n + 1][0], my_str, 100);
						printf("This is child %d , l is %d \n",i,(*l));
                        temp = atoi(my_str); //string->int
						printf("This is temp (the int from the read string) %d \n",temp);
						close(pl[1]);
						read(pl[0],count, 12);
                        res = temp * (atoi(count));
						close(pl[0]);
                        close(fd1[n + 1][0]);
                    }
					else {
                        close(fd1[i][1]);
                        char my_str[100];
                        read(fd1[i][0], my_str, 100);
						printf("This is child %d , l is %d \n",i,(*l));
                        temp = atoi(my_str); //string->int
						printf("This is temp (the int from the read string) %d \n",temp);
                        close(pl[1]);
						read(pl[0],count, 12);
                        res = temp * (atoi(count));
						close(pl[0]);
                        close(fd1[i][0]);

                    }
                    close(pl[1]);
					read(pl[0],count, 12);
					int temp1=atoi(count)++;
					close(pl[0]);
					write(pl[1], temp1, strlen(temp1) + 1);
					close(pl[1]);
                    close(fd1[i][0]);
                    sprintf(input_str, "%d", res);
                    write(fd1[i + 1][1], input_str, strlen(input_str) + 1);
					printf("the res as an int is %d \n", res);
                    close(fd1[i + 1][1]);
              
            }
			exit(0);
        }
    }
}        
