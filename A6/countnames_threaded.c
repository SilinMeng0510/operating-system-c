/**
 * Description: Assignment 6: countnames_threaded: 
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
} NODE;



/*********************************************************
// function main 
*********************************************************/
int main(int argc, char** argv)
{
  if(argc != 3){
    perror("Please enter exact two input files!\n");
    exit(1);
  }

  printf("Create first thread\n");
  pthread_create(&tid1, NULL, thread_runner, argv[1]);
  
  printf("Create second thread\n");
  pthread_create(&tid2, NULL, thread_runner, argv[2]);
  
  pthread_join(tid1, NULL);
  printf("First thread exited\n");
  pthread_join(tid2, NULL);
  printf("Second thread exited\n");

  //TODO print out the sum variable with the sum of all the numbers

  exit(0);

}//end main


/**********************************************************************
// function thread_runner runs inside each thread 
**********************************************************************/
void* thread_runner(void* filename)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  pthread_t me;
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
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: This is thread %ld and I created THREADDATA %p\n",
      logindex, (long) me, (int)getpid(), tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (long) me, p);
  }
  else {
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: This is thread %ld and I can access the THREADDATA %p\n",
      logindex, (long) me, (int)getpid(), tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (long) me, p);
  }
  pthread_mutex_unlock(&tlock1);  // critical section ends for log message

  FILE *file = fopen((char*)filename, "r");
  if(file == NULL) {
    pthread_mutex_lock(&tlock1);   // critical section starts for log message
    logindex++;
    fprintf(stderr, "Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: range: cannot open file %s\n",
      logindex, (long) me, (int)getpid(), tm.tm_mon+1, tm.tm_mday,tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (char*)filename);
    pthread_mutex_unlock(&tlock1);  // critical section ends for log message

    pthread_exit(NULL);
  }
  else {
    pthread_mutex_lock(&tlock1);    // critical section starts for log message
    logindex++;
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: opened file %s.\n", logindex, (long) me, (int)getpid(),
           tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (char*)filename);
    pthread_mutex_unlock(&tlock1);  // critical section ends for log message
  }
 
  char *line = NULL;
  size_t len = 0;
  int lineCounter = 1;
  while(getline(&line, &len, file) != -1) {
    if (line[0] == '\n' || line[0] == ' ') { // Printing Error message while there is a empty line
      fprintf(stderr, "Warning - file %s line %d is empty.\n", (char*)filename, lineCounter);
      ++lineCounter; // Count which line we are in
      continue;
    }
    ++lineCounter;
  }
  free(line);
  fclose(file);


  pthread_mutex_lock(&tlock1);   // critical section starts for log message
  logindex++;
  if (p != NULL && p->creator == me) {
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: This is thread %ld and I delete THREADDATA\n",
      logindex, (long) me, (int)getpid(), tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (long) me);

    pthread_mutex_lock(&tlock2);  // critical section starts for allocating THREADDATA
    free((void*)p);
    p = NULL;
    pthread_mutex_unlock(&tlock2);  // critical section ends for allocating THREADDATA
  } 
  else {
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d: This is thread %ld and I can access the THREADDATA\n",
      logindex, (long) me, (int)getpid(),tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (long) me);
  }
  pthread_mutex_unlock(&tlock1);  // critical section ends for log message

  pthread_exit(NULL);
  return NULL;
}//end thread_runner

