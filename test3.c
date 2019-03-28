#include < stdio.h > 
#include < stdlib.h > 
#include < unistd.h > 
#include < sys / types.h > 
#include < string.h > 
#include < sys / wait.h >

int main(int argc, char **argv) {
    int status, temp;
    char count[12]; //counter
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    int res = 1;
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
            if (i == 0) {
                close(fd1[0][0]);
                strcpy(input_str, "1");
                write(fd1[0][1], input_str, strlen(input_str) + 1);
                printf("This is the father the first time\n");
            }

            wait(&status);
        }

            // child process
        else {
            int counter = i + 1; //topikos metritis , gia pollaplasiasmo
            while (counter <= k) {
                char my_str[100];
                close(fd1[i][1]);
                read(fd1[i][0], my_str, 100);
                temp = atoi(my_str); //string->int
                printf("This is child %d \n", i);
                printf("This is prev reasult %d \n", temp);
                res = temp * counter;

                sprintf(input_str, "%d", res);
                if (i == n - 1) {
                    close(fd1[0][0]);
                    write(fd1[0][1], input_str, strlen(input_str) + 1);
                } else {
                    close(fd1[i + 1][0]);
                    write(fd1[i + 1][1], input_str, strlen(input_str) + 1);
                }
                printf("the res as a string is %s \n", input_str);
                counter = counter + n;
            }

            exit(0);
        }
    }
}