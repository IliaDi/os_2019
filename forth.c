#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {
	pid_t p1, p2, p3;
	int pd[2]; 		//status
	pipe( pd );
	close( pd[ 0 ] );
	close( pd[ 1 ] );
	p1 = fork ();
	int s=1;
	if ( p1<0 ){
		printf("error");
		exit( 0 );
	}
	else if ( p1==0 ){
		read( pd[0], &s, sizeof( s ) );
		for ( int i; i<5; i++){
			printf("child1 %d executes a critical section ,%d \n",getpid(), i );
		}
		sleep(3);
		write( pd[1], &s, sizeof( s ) );
		for ( int i=0; i<7; i++ ){
			printf("child1 %d executes a non critical section ,%d \n",getpid(), i );
		}
		for ( int i=0; i<7; i++ ){
			printf("child1 %d executes a non critical section ,%d \n",getpid(), i );
		}
		read( pd[0], &s, sizeof( s ) );
		for ( int i; i<5; i++){
			printf("child1 %d executes a critical section ,%d \n",getpid(), i );
		}
		sleep(3);
		write( pd[1], &s, sizeof( s ) );
		for ( int i=0; i<7; i++ ){
			printf("child1 %d executes a non critical section ,%d \n",getpid(), i );
		}
		exit(0);
	}
	else{
		p2 = fork();
		if ( p2<0 ){
			printf("error");
			exit( 0 );
		}
		else if ( p2 == 0 ){
			for ( int i=0; i<7; i++ ){
				printf("child2 %d executes a non critical section ,%d \n",getpid(), i );
			}
			read( pd[0], &s, sizeof( s ) );
			for ( int i; i<5; i++){
				printf("child2 %d executes a critical section ,%d \n",getpid(), i );
			}
			sleep(3);
			write( pd[1], &s, sizeof( s ) );
			for ( int i=0; i<7; i++ ){
				printf("child2 %d executes a non critical section ,%d \n",getpid(), i );
			}
			read( pd[0], &s, sizeof( s ) );
			for ( int i; i<5; i++){
				printf("child2 %d executes a critical section ,%d \n",getpid(), i );
			}
			sleep(3);
			write( pd[1], &s, sizeof( s ) );
			for ( int i=0; i<7; i++ ){
				printf("child2 %d executes a non critical section ,%d \n",getpid(), i );
			}
			read( pd[0], &s, sizeof( s ) );
			for ( int i; i<5; i++){
				printf("child2 %d executes a critical section ,%d \n",getpid(), i );
			}
			write( pd[1], &s, sizeof( s ) );
			exit(0);
		}
		else{
			p3 = fork();
			if ( p3<0 ){
				printf("error");
				exit( 0 );
			}
			else if ( p3 == 0 ){
				read( pd[0], &s, sizeof( s ) );
				for ( int i; i<5; i++){
					printf("child3 %d executes a critical section ,%d \n",getpid(), i );
				}
				sleep(3);
				write( pd[1], &s, sizeof( s ) );
				for ( int i=0; i<7; i++ ){
					printf("child3 %d executes a non critical section ,%d \n",getpid(), i );
				}
				read( pd[0], &s, sizeof( s ) );
				for ( int i; i<5; i++){
					printf("child3 %d executes a critical section ,%d \n",getpid(), i );
				}
				sleep(3);
				write( pd[1], &s, sizeof( s ) );
				for ( int i=0; i<7; i++ ){
					printf("child3 %d executes a non critical section ,%d \n",getpid(), i );
				}
				read( pd[0], &s, sizeof( s ) );
				for ( int i; i<5; i++){
					printf("child3 %d executes a critical section ,%d \n",getpid(), i );
				}
				sleep(3);
				write( pd[1], &s, sizeof( s ) );
				for ( int i=0; i<7; i++ ){
					printf("child3 %d executes a non critical section ,%d \n",getpid(), i );
				}
				exit(0);
			}
			else {
				write( pd[1], &s, sizeof( s ) );
			}	
		}
	}
}
