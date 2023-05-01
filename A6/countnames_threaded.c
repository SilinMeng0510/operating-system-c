/**
 * Description: Assignment 6: countnames_threaded: this program read only 2 text files with names, and count the occurance of all names from the files. The program will
 * create 2 threads doing the job concurrently while maintaining thread_safe.
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 4/29/23
 * Creation date: 4/29/23
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

/*****************************************
//CS149 Fall 2022
//Template for assignment 6
//San Jose State University
//originally prepared by Bill Andreopoulos
*****************************************/


//thread mutex lock for access to the log index
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;


//thread mutex lock for critical sections of allocating THREADDATA
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER; 


//thread mutex lock for access to the name counts data structure
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER; 


void* thread_runner(void*);
pthread_t tid1, tid2;

//struct points to the thread that created the object. 
//This is useful for you to know which is thread1. Later thread1 will also deallocate.
struct THREADDATA_STRUCT
{
  pthread_t creator;
};
typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA* p=NULL;


//variable for indexing of messages by the logging function.
int logindex=0;
int *logip = &logindex;


//The name counts.
// You can use any data structure you like, here are 2 proposals: a linked list OR an array (up to 100 names).
//The linked list will be faster since you only need to lock one node, while for the array you need to lock the whole array.
//You can use a linked list template from A5. You should also consider using a hash table, like in A5 (even faster).
struct NAME_STRUCT
{
  char name[30];
  int count;
};
typedef struct NAME_STRUCT THREAD_NAME;

//node with name_info for a linked list
struct NAME_NODE
{
  THREAD_NAME name_count;
  struct NAME_NODE *next;
};
typedef struct NAME_NODE NODE;

static NODE* head = NULL;

// -----------------------------------------
// function FreeList will recursively free all memory of address of linked nodes in the list.
// Returns void after done
void freeList(NODE* tempNode){

    if(tempNode->next != NULL){	// if this is not the last node, free the next node first
        freeList(tempNode->next);
		    free(tempNode->next);	// after the current node
    }	
	return;
}

// -----------------------------------------
// function PrintNodes will recursively print all linked nodes in a list.
// Returns void after done
void printNodes(NODE* tempNode){

    if(tempNode->next != NULL){	// if this is not the last node, print the next node
        printNodes(tempNode->next);
    }
    printf("%s: %d\n", tempNode->name_count.name, tempNode->name_count.count); // print current node

	return;
}

/*********************************************************
// function main 
*********************************************************/
int main(int argc, char** argv)
{
  printf("==================================== Log Messages ====================================\n");
  if(argc != 3){    // return error with the file number is not 2
    perror("Please enter exact two input files!\n");
    exit(1);
  }
  head = (NODE*) calloc(1, sizeof(NODE)); // allocate space for head of linkedlist

  printf("Create first thread\n");  // create thread1 with a filename
  pthread_create(&tid1, NULL, thread_runner, argv[1]);
  
  printf("Create second thread\n"); // create thread2 with a filename
  pthread_create(&tid2, NULL, thread_runner, argv[2]);
  
  pthread_join(tid1, NULL); // wait for thread1
  printf("First thread exited\n");
  pthread_join(tid2, NULL); // wait for thread2
  printf("Second thread exited\n");

  printf("==================================== Name Counts ====================================\n");
  printNodes(head->next); // print out the list

  freeList(head); // free the list's memory spaces
  free(head);

  exit(0);

}//end main


/**********************************************************************
// function thread_runner runs inside each thread 
**********************************************************************/
void* thread_runner(void* filename)
{
  time_t t = time(NULL);    // set timer for the thread
  struct tm tm = *localtime(&t);

  pthread_t me;     // get thread number or id
  me = pthread_self();

  pthread_mutex_lock(&tlock2);  // critical section starts for allocating THREADDATA
  if (p == NULL) {
    p = (THREADDATA*) malloc(sizeof(THREADDATA));
    p->creator = me;
  }
  pthread_mutex_unlock(&tlock2);  // critical section ends for allocating THREADDATA

  pthread_mutex_lock(&tlock1);  // critical section starts for log message
  logindex++;
  if (p != NULL && p->creator == me) {
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: This is thread %ld and I created THREADDATA %p\n",    // print log message of creating threaddata
      logindex, (long) me, (int)getpid(), tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (long) me, p);
  }
  else {
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: This is thread %ld and I can access the THREADDATA %p\n", // print log message of secondary thread
      logindex, (long) me, (int)getpid(), tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (long) me, p);
  }
  pthread_mutex_unlock(&tlock1);  // critical section ends for log message

  FILE *file = fopen((char*)filename, "r"); // open file
  if(file == NULL) {  // if open file fails
    pthread_mutex_lock(&tlock1);   // critical section starts for log message
    logindex++;
    fprintf(stderr, "Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: range: cannot open file %s\n",
      logindex, (long) me, (int)getpid(), tm.tm_mon+1, tm.tm_mday,tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (char*)filename); // print log message of open file fails
    pthread_mutex_unlock(&tlock1);  // critical section ends for log message
  }
  else {
    pthread_mutex_lock(&tlock1);    // critical section starts for log message
    logindex++;
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: opened file %s.\n", logindex, (long) me, (int)getpid(), // print log message of open file successfully
           tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (char*)filename);
    pthread_mutex_unlock(&tlock1);  // critical section ends for log message

    char *line = NULL;  // necessary variables for reading file
    size_t len = 0;
    int lineCounter = 1;
    while(getline(&line, &len, file) != -1) {   // read until the end of the file
      if (line[0] == '\n' || line[0] == ' ') { // Printing Error message while there is a empty line
      fprintf(stderr, "Warning - file %s line %d is empty.\n", (char*)filename, lineCounter);
      ++lineCounter; // Count which line we are in
      continue;
      }
      if (line[strlen(line) - 1] == '\n') { // delete the newline from string
      line[strlen(line) - 1] = '\0';
      }

      int found = 0;
      NODE* node = head; 
      pthread_mutex_lock(&tlock3);  // critical section starts for access linkedlist
      while((node = node->next) != NULL){ // scan through the linkedlist to match the input name
        if (strcmp(node->name_count.name, line) == 0){ // increment the count if found
          node->name_count.count++;
          found = 1;
          break;
        }
      }
      pthread_mutex_unlock(&tlock3);  // critical section ends for access linkedlist
      if(!found){ // if not found
        THREAD_NAME name = {{'\0', 0}}; // set the up the thread_name variable
        strcpy(name.name, line);
        name.count = 1;
        NODE* new = (NODE*) calloc(1, sizeof(NODE));  // set the up the new linkedlist node
  
        pthread_mutex_lock(&tlock3);  // critical section starts for access linkedlist
        new->name_count = name; // create and insert the new node to the head
        new->next = head->next;
        head->next = new;
        pthread_mutex_unlock(&tlock3);  // critical section ends for access linkedlist
      }
      ++lineCounter;  // keep the line counter updated in the file
    }
    free(line); // free the line and file
    fclose(file);
  }

  pthread_mutex_lock(&tlock2);  // critical section starts for allocating THREADDATA
  if (p != NULL && p->creator == me) { // check if the thread created the THREADDATA
    pthread_mutex_unlock(&tlock2);  // critical section ends for allocating THREADDATA
    pthread_mutex_lock(&tlock1);   // critical section starts for log message
    logindex++;
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: This is thread %ld and I delete THREADDATA\n",  // print log message that the first thread delete the Threaddata
      logindex, (long) me, (int)getpid(), tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (long) me);
    pthread_mutex_unlock(&tlock1);  // critical section ends for log message

    pthread_mutex_lock(&tlock2);  // critical section starts for allocating THREADDATA
    free((void*)p);   // free the thread_data and set it to NULL
    p = NULL;
    pthread_mutex_unlock(&tlock2);  // critical section ends for allocating THREADDATA
  } 
  else {
    pthread_mutex_unlock(&tlock2);  // critical section ends for allocating THREADDATA
    pthread_mutex_lock(&tlock1);   // critical section starts for log message
    logindex++;
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: This is thread %ld and I can access the THREADDATA\n", // print log message of the secondary thread
      logindex, (long) me, (int)getpid(),tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (long) me);
    pthread_mutex_unlock(&tlock1);  // critical section ends for log message
  }

  pthread_exit(NULL);
  return NULL;
}//end thread_runner

