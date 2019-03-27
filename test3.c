#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char **argv) {
    int status,  temp;
	int l =1;
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
            close(fd1[0][0]);
            strcpy(input_str, "1");

            write(fd1[0][1], input_str, strlen(input_str) + 1);
            close(fd1[0][1]);

            wait(&status);
        }

            // child process
        else {
            while (l <= k) {
                     printf("This is child %d , l is %d \n",i,l);
                     if(i==1 && l!=1){ 
                        close(fd1[n + 1][1]);
                        char my_str[100];
                        read(fd1[n + 1][0], my_str, 100);
                        temp = atoi(my_str); //string->int
						printf("This is temp (the int from the read string) %d \n",temp);
                        res = temp * l;
                        close(fd1[n + 1][0]);
                    }
					else {
                        close(fd1[i][1]);
                        char my_str[100];
                        read(fd1[i][0], my_str, 100);
                        temp = atoi(my_str); //string->int
						printf("This is temp (the int from the read string) %d \n",temp);
                        res = temp * l;
                        close(fd1[i][0]);

                    }
                    l++;
                    close(fd1[i][0]);
					printf("the res as an int is %d \n", res);
                    sprintf(input_str, "%d", res);
					printf("Now the res as a string is %s \n", input_str);
                    write(fd1[i + 1][1], input_str, strlen(input_str) + 1);
                    close(fd1[i + 1][1]);
              
            }
			exit(0);
        }
    }
} 
