#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <string.h> 
#include <sys/wait.h>

int main(int argc, char **argv) {
    int status, temp;
    char count[12]; //counter
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    int res = 1;
    pid_t c[n];
    int fd1[n ][2];
    for (int i = 0; i  n; i++) {
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
				close(fd1[0][1]);
                printf("This is the father the first time\n");
            }

            wait(&status);
        }

            // child process
        else {
               // mperdeuetai sth loopa otan k>n , DEN PETYXAINEI O SYNGRONISMOS
			int counter = i + 1; //topikos metritis , gia pollaplasiasmo
            while (counter <= k) {
                char my_str[100];
                close(fd1[i][1]);
                read(fd1[i][0], my_str, 100);
				close(fd1[i][0]); //αν λείπει αυτό , τότε "κολλάει αφού διαβάσει και γράψει το παιδί 0 , αλλά και τα άλλα close τα δευτερα , αν λείπουν κολλάει στην τελευταία επανάληψη και δεν μπορεί να γράψει
				
                temp = atoi(my_str); //string->int
                printf("This is child %d \n", i);
                printf("This is prev result %d \n", temp);
                res = temp * counter;
                sprintf(input_str, "%d", res);
			   
				if(i==n-1){
					close(fd1[0][0]);
					write(fd1[0][1], input_str, strlen(input_str)+1);
					close(fd1[0][1]);
				}
				else{
                close(fd1[i + 1][0]);
                write(fd1[i + 1][1], input_str, strlen(input_str) + 1);
				close(fd1[i+1][1]);
				}
                
                printf("the res as a string is %s \n", input_str);
                counter = counter + n;
            }

            exit(0);
        }
    }
}

/*ΛΟΙΠΟΝ
Αν εχουμε ν=3 και κ=6
τότε, παιδί 0 εκτελείται συνεχόμενα και διατηρεί ίδιο πρεβ 
παιδί 1 (1) παιρνει την τιμή που έγραψε το παιδί 0 (1)
παιδι 1 (2) παρίρνει επίσης την τιμή που εγραψε το 0 (1)
παιδί 2 (1) παιρνει την τιμή που εγραψε το παιδί 1 (1)
παιδί 2 (2) παίρνει την τιμή που έγραψε το παιδί 1 (1)
ΑΡΑ δεν περιμένουν το 2ο + γράψιμο (το οβεραιτ στο παιπ) αλλά τους αρκεί η αρχική τιμούλα 
*/