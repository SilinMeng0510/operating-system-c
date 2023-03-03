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

#include <sys/types.h>



int main(){
   pid_t pid;

   for (int i = 0; i < 4; i++) {
      pid = fork();
      if (pid < 0) {
         fprintf(stderr, "fork failed\n");
         exit(1);
      } 
      else if (pid == 0) { 
         printf("hello world from PID %d!\n", getpid());
         return 0;
      }
   }

    return 0;

}

