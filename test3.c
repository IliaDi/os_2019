#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
    // We use two pipes 
    // First pipe to send input string from parent 
    // Second pipe to send concatenated string from child 
  
    int fd[2];  // Used to store two ends of first pipe 
  
    char my_str[12]; 
    pid_t p; 
  
    if (pipe(fd)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
   
    p = fork(); 
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        close(fd[0]);  // Close reading end of first pipe 
        strcpy(my_str,"hey");
        // Write input string and close writing end of first 
        // pipe. 
        write(fd[1], my_str, strlen(my_str)+1); 
        close(fd[1]); 
  
        // Wait for child to send a string 
        wait(NULL); 
    } 
  
    // child process 
    else
    { 
        close(fd[1]);  // Close writing end of first pipe 
  
        // Read a string using first pipe 
        char concat_str[100]; 
        read(fd[0], concat_str, 100); 
  
        exit(0); 
    } 
}
