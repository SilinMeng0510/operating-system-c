/**
 * Description: Assignment 4: This code read multiple commands through stdin and run them through execvp. The result will be written in created files under name of child pid.
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 03/19/2023
 * Creation date: 03/17/2023
 **/

#include <sys/wait.h> //import library
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

/**
 * TRACE_NODE_STRUCT is a linked list of
 * pointers to function identifiers
 * TRACE_TOP is the head of the list is the top of the stack
**/
struct TRACE_NODE_STRUCT {
  char* functionid;                // ptr to function identifier (a function name)
  struct TRACE_NODE_STRUCT* next;  // ptr to next frama
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL;       // ptr to the top of the stack


/* --------------------------------*/
/* function PUSH_TRACE */
/* 
 * The purpose of this stack is to trace the sequence of function calls,
 * just like the stack in your computer would do. 
 * The "global" string denotes the start of the function call trace.
 * The char *p parameter is the name of the new function that is added to the call trace.
 * See the examples of calling PUSH_TRACE and POP_TRACE below
 * in the main, make_extend_array, add_column functions.
**/
void PUSH_TRACE(char* p)          // push p on the stack
{
  TRACE_NODE* tnode;
  static char glob[]="global";

  if (TRACE_TOP==NULL) {

    // initialize the stack with "global" identifier
    TRACE_TOP=(TRACE_NODE*) malloc(sizeof(TRACE_NODE));

    // no recovery needed if allocation failed, this is only
    // used in debugging, not in production
    if (TRACE_TOP==NULL) {
      printf("PUSH_TRACE: memory allocation error\n");
      exit(1);
    }

    TRACE_TOP->functionid = glob;
    TRACE_TOP->next=NULL;
  }//if

  // create the node for p
  tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

  // no recovery needed if allocation failed, this is only
  // used in debugging, not in production
  if (tnode==NULL) {
    printf("PUSH_TRACE: memory allocation error\n");
    exit(1);
  }//if

  tnode->functionid=p;
  tnode->next = TRACE_TOP;  // insert fnode as the first in the list
  TRACE_TOP=tnode;          // point TRACE_TOP to the first node

}/*end PUSH_TRACE*/


/* --------------------------------*/
/* function POP_TRACE */
/* Pop a function call from the stack */
void POP_TRACE()    // remove the op of the stack
{
  TRACE_NODE* tnode;
  tnode = TRACE_TOP;
  TRACE_TOP = tnode->next;
  free(tnode);

}/*end POP_TRACE*/


/* ---------------------------------------------- */
/* function PRINT_TRACE prints out the sequence of function calls that are on the stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC. */
/* Printing the function call sequence the other way around is also ok: funcC:funcB:funcA:global */
char* PRINT_TRACE()
{
  int depth = 50; //A max of 50 levels in the stack will be combined in a string for printing out.
  int i, length, j;
  TRACE_NODE* tnode;
  static char buf[100];

  if (TRACE_TOP==NULL) {     // stack not initialized yet, so we are
    strcpy(buf,"global");   // still in the `global' area
    return buf;
  }

  /* peek at the depth(50) top entries on the stack, but do not
     go over 100 chars and do not go over the bottom of the
     stack */

  sprintf(buf,"%s",TRACE_TOP->functionid);
  length = strlen(buf);                  // length of the string so far
  for(i=1, tnode=TRACE_TOP->next;
                        tnode!=NULL && i < depth;
                                  i++,tnode=tnode->next) {
    j = strlen(tnode->functionid);             // length of what we want to add
    if (length+j+1 < 100) {              // total length is ok
      sprintf(buf+length,":%s",tnode->functionid);
      length += j+1;
    }else                                // it would be too long
      break;
  }
  return buf;
} /*end PRINT_TRACE*/


// -----------------------------------------
// function REALLOC calls realloc
// TODO REALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File tracemem.c, line X, function F reallocated the memory segment at address A to a new size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* REALLOC(void* p,int t,char* file,int line)
{
	p = realloc(p,t);
	printf("File %s, line %i, function %s reallocated the memory segment at address %p to a new size %i\n", file, line, PRINT_TRACE(), p, t);
	return p;
}


// -------------------------------------------
// function MALLOC calls malloc
// TODO MALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File tracemem.c, line X, function F allocated new memory segment at address A to size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* MALLOC(int t,char* file,int line)
{
	void* p;
	p = malloc(t);
	printf("File %s, line %i, function %s allocated new memory segment at address %p to size %i\n", file, line, PRINT_TRACE(), p, t);
	return p;
}


// ----------------------------------------------
// function FREE calls free
// TODO FREE should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File tracemem.c, line X, function F deallocated the memory segment at address A"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void* p,char* file,int line)
{
	free(p);
	printf("File %s, line %i, function %s deallocated the memory segment at address %p\n", file, line, PRINT_TRACE(), p);
}


#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)


/**
 * linkedList is a linked list of
 * pointers, line, and index to the command inputs
**/
struct linkedList
{
	char* line;
	int index;
	struct linkedList* nextNode;
}; 

typedef struct linkedList linkedNode; //define linkedList wuth linkedNode type


// -----------------------------------------
// function CreateNode will create pointer to a linked node.
// Returns the pointer of the created linked node
linkedNode* CreateNode(char* line, int index, int size){
    PUSH_TRACE("CreateNode");

    linkedNode *tempNode;
    tempNode = (linkedNode*) malloc(sizeof(linkedNode)); // allocate memory address for the node and command line input
    tempNode->line = (char*) malloc(sizeof(char)*size);
    strcpy(tempNode->line, line);	// copy the command line input into the allocated address
    tempNode->index = index;	// assign index
    tempNode->nextNode = NULL;	// set the nextnode to null

    POP_TRACE();
    return tempNode;	// return the created node
}


// -----------------------------------------
// function PrintNodes will recursively print all linked nodes in a list.
// Returns void after done
void PrintNodes(linkedNode* tempNode){
    PUSH_TRACE("PrintNodes");

    printf("linkedlist[%d]=%s", tempNode->index, tempNode->line); // print current node
    if(tempNode->nextNode != NULL){	// if this is not the last node, print the next node
        PrintNodes(tempNode->nextNode);
    }

    POP_TRACE();
	return;
}


// -----------------------------------------
// function FreeList will recursively free all memory of address of linked nodes in the list.
// Returns void after done
void FreeList(linkedNode* tempNode){
    PUSH_TRACE("FreeList");

    if(tempNode->nextNode != NULL){	// if this is not the last node, free the next node first
        FreeList(tempNode->nextNode);
		free(tempNode->nextNode);	// after the current node
    }
    free(tempNode->line);	// free the command line input
	
    POP_TRACE();	
	return;
}


// -----------------------------------------
// function add_size will add an extra string space to an array.
// This function is adding more memory space for our array, using realloc
// Returns the pointer of the reallocated array of string (updated)
char** add_size(char** array, int size) {
    PUSH_TRACE("add_size");

    array = (char**) realloc(array, sizeof(char*) * size);	// reallocate the space for bigger array

    POP_TRACE();
    return array;
}// end add_size


// -----------------------------------------
// function new_size will create an initial array stroing 10 pointers.
// This function is allocating 10 char* memory space for our array, using malloc
// Returns the pointer of new array of string 
char** new_arr(char** array, int size) {
    PUSH_TRACE("new_arr");

    array = (char**) malloc(sizeof(char*) * size);	// allocate an array that can store specified number of strings

    POP_TRACE();
    return array;
}// end new_arr


// -----------------------------------------
// function alloc_string will allocate memory space for a string.
// This function is allocating memory space of the input length for our array, using malloc
// Returns the pointer of string 
void alloc_string(char** array, int index, int length) {
    PUSH_TRACE("alloc_string");

    array[index] = (char*) malloc(sizeof(char) * length); // allocate space for the string

    POP_TRACE();
	return;
}// end alloc_string


// ------------------------------------------
// function make_extend_array
// create an array store commands typed in shell
// This function is intended to demonstrate how memory usage tracing of malloc and free is done
linkedNode* make_extend_array()
{
    PUSH_TRACE("make_extend_array");

	char **array = NULL;	// initialize the array

	char *line = NULL;	// initailize the input line and buffer len
	size_t len = 0;

	int index = 0;	// initialize the input index and total size with 10 strings
	int SIZE = 10;

	linkedNode* list; // initialize the list head and current list
	linkedNode* current;

	array = new_arr(array, SIZE);  // 10 strings
	while(getline(&line, &len, stdin) != -1) {
        // check if there is more string needed
        if (index == SIZE) {
            SIZE += 1;
            array = add_size(array, SIZE);
        }

		// insert command read from stdin into char** array
		alloc_string(array, index, len);
        strcpy(array[index], line);

		// insert command read from stdin into linked list
		if (index == 0){ // if it's the start, create node for the head, and set current to head
			list = CreateNode(line, index, len);
			current = list;
		}
		else{ // if it's not the start, create next node and set the current to next node
			current->nextNode = CreateNode(line, index, len);
            current = current->nextNode;
		}

		++index;
	}
	free(line);

	// display the array
	for(int i = 0; i < index; i++){
		printf("array[%d]=%s",i,array[i]);
	}

	//now deallocate it
	for(int i = 0; i < SIZE; i++){
		free(array[i]);
	}
	free(array);

	POP_TRACE();
    return list;
}//end make_extend_array


// ------------------------------------------
// function dup_stdout
// dup2 between a file memtrace.out and standard output
// This function is intended to forward printf statement to our file
int dup_stdout(){
    PUSH_TRACE("dup_stdout");

    char* filename = "memtrace.out";	// set output file name
    int fd;

    if((fd = open(filename, O_RDWR | O_CREAT, 0777)) < 0){ // create or open the file and return a file descriptor of the file
        printf("error: memtrace.out can't be created \n"); // if fail, print error
        exit(2);
    }

    dup2(fd, STDOUT_FILENO);	// duplicate file descriptor
    close(fd);

    POP_TRACE();
    return 0;
}


// ----------------------------------------------
// function main
int main()
{
	PUSH_TRACE("main");

	if(dup_stdout() != 0){   // dup stdout to file
        return 1;
    }

	linkedNode* list = make_extend_array();	// start the function of reading command input, and return a head linked node
	PrintNodes(list);	// recursively print the whole linked list

	FreeList(list);	// free all node in linked list, except the head
	free(list);	// free the head of the linked list

	POP_TRACE();

	#undef free 
	free(TRACE_TOP);
	return(0);
}// end main
