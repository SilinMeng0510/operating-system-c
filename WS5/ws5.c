/**

 * Description: ws5.c: This code uses the fork() function to create a new 

 *    process and then output hello world from PID followed by the process ID

 * Author names: Silin Meng, Ibrahim Dobashi

 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu

 * Last modified date: 2/16/2023

 * Creation date: 2/13/2023

 **/



#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>



int main(){
   pid_t pid;

   fork();
   fork();
   printf("hello world from PID %d!\n", getpid());

   return 0;

}

