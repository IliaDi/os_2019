//ο πατέρας δημιουργεί n παιδιά (n , k είσοδος προγρ.) k: ακέραιος θέλω να υπολογίσω το k!
//ο πατέρας στέλνει χ=1 στην πρώτη και κυκλικά κάνουν 1 πολλαπλασιασμό το κάθε παιδί χ*(κ) Το κ αυξάνεται σε κάθε βήμα και δίνουν(ΓΡΑΦΟΥΝ) το αποτέλεσμα χ' στο επόμενο παιδί (1->2->3->4->1...) αυτό θα γίνει k φορές 
//άρα έχω λούπα κ φορές (ΑΠΟ 1 ΜΕΧΡΙ Κ) για να πάει από παιδί σε παιδί
//η επικοινωνία μέσω διοχετεύσεων (named pipes)

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {
	int status;
	int res, nbytes,l, temp; 
	int n = argv[1];
	int k = argv[2];
	char string[];
	pid_t c[n];
	char readbuffer[80];
	int pd[n][2];
	for (int i=0; i<n; i++){
		pipe(pd[i]); //pd[i][0]: read , pd[i][1]: write
	}
	for (int i=0; i<n; i++){
		c[i]=fork();
		if (c[i] < 0) { printf("fork produced error"); }
        else if (c[i] == 0) {//c[i] code
		    //ΠΩΣ ΘΑ ΜΕΤΡΉΣΩ ΤΙΣ Κ ενεργοποιήσεις? έστω l
			if (l<=k){
			close(pd[i][1]);
			nbytes=read(pd[i][0] , readbuffer , sizeof(readbuffer));
			temp = atoi(nbytes);
			res=temp*l;
			string = stoi(res);
			l++;
			if(i<n-1){
				close(pd[i+1][0]);
				write(pd[i+1][1] , string , (strlen(string)+1));
				
			}
			else {
				close(pd[0][0]);
				write(pd[0][1] , string , (strlen(string)+1));
			}
			}
            exit(0);
        } 
	    else {//F 
		    sleep(1);
			//γράψε στην c[0] 1	
			close(pd[0][0]);
			l=1;
			string[]="1";
			write(pd[0][1], string, (strlen(string)+1));
			
		    wait(&status);
			exit(0);
		}
	}
}