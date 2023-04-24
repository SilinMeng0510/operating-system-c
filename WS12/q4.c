/**

 * Description: q4: This program allocates memeory on the heap using malloc then exits without freeing the memeory

 * Author names: Silin Meng, Ibrahim Dobashi

 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu

 * Last modified date: 4/24/2023

 * Creation date: 4/24/2023

 **/

/*



/*

Worksheet Questions:

What happens when this program runs? 

    when running the code, the codde exits normally without any errors

Can you use gdb to find any problems with it? 

    No using gdb doesn't help finding a problem since it when running with gdb, the code exits normally without crashing meaning gdb didn't detect any problems



How about valgrind (with the --leak-check=yes flag)?

    When running with valgrind, we get a message indacting that there was a memory leak of 4 bytes

*/



#include <stdio.h>

#include <stdlib.h>



int main() {

    int *ptr = (int *) malloc(sizeof(int));

    return 0;

}