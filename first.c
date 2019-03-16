/*Να γραφτεί πρόγραμμα σε γλώσσα
προγραμματισμού C και περιβάλλον Linux στο οποίο
η διεργασία πατέρας (F) δημιουργεί 5 διεργασίες
(C1,C2,C3,C4,C5) σύμφωνα με το παρακάτω δέντρο
διεργασιών (F->C1,C2 , C2->C5 , C1->C3,C4)
Κάθε μία τυπώνει Process Pid is executed, my father is Ppid*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int status;
    pid_t mypid;
    pid_t parent_pid;
    pid_t c1;
    c1 = fork();
    if (c1 < 0) { printf("fork produced error"); }
    else if (c1 == 0) {//c1 code
        pid_t c3;
        c3 = fork();
        if (c3 < 0) { printf("fork produced error"); }
        else if (c3 == 0) { //c3 code
            for (int i = 0; i < 10; i++) {
                parent_pid = getppid();
                mypid = getpid();
                printf("Process %d is executed, my father is %d \n", mypid, parent_pid);
                sleep(1);
            }
            exit(0);
        } else {//c1
            pid_t c4;
            c4 = fork();
            if (c4 < 0) { printf("fork produced error"); }
            else if (c4 == 0) { //c4
                for (int i = 0; i < 10; i++) {
                    parent_pid = getppid();
                    mypid = getpid();
                    printf("Process %d is executed, my father is %d \n", mypid, parent_pid);
                    sleep(1);
                }
                exit(0);
            } else {//c1
                for (int i = 0; i < 10; i++) {
                    parent_pid = getppid();
                    mypid = getpid();
                    printf("Process %d is executed, my father is %d \n", mypid, parent_pid);
                    sleep(1);
                }
                wait(&status);
                exit(0);
            }
            wait(&status);
            exit(0);
        }
        exit(0);
    } else { //F’s code
        pid_t c2 = fork();
        if (c2 < 0) { printf("fork produced error"); }
        else if (c2 == 0) { //c2 code
            pid_t c5 = fork();
            if (c5 < 0) { printf("fork produced error"); }
            else if (c5 == 0) {//c5 code
                for (int i = 0; i < 10; i++) {
                    parent_pid = getppid();
                    mypid = getpid();
                    printf("Process %d is executed, my father is %d \n", mypid, parent_pid);
                    sleep(1);
                }
                exit(0);
            } else {//c2 father of c5
                for (int i = 0; i < 10; i++) {
                    parent_pid = getppid();
                    mypid = getpid();
                    printf("Process %d is executed, my father is %d \n", mypid, parent_pid);
                    sleep(1);
                }
                wait(&status);
                exit(0);
            }
            exit(0);
        } else {//F
            wait(&status);
            exit(0);
        }
        wait(&status);
        exit(0);
    }
    return 0;
}