/**

 * Description: q5: This program  allocate an array of 100 integers using malloc, then set data[100] to zero and frees the memeory

 * Author names: Silin Meng, Ibrahim Dobashi

 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu

 * Last modified date: 4/24/2023

 * Creation date: 4/24/2023

 **/

/*



/*

Worksheet Questions:

What happens when you run this program? 

    The program runs normally and exits without errors

What happens when you run this program using valgrind? Is the program correct?

    When using valgrind, we get an error message asying invalid write of size 4 and also indicates that we tried to access memory out of bounds

*/

#include <stdio.h>

#include <stdlib.h>



int main() {

    int *arr = (int *) malloc(100 * sizeof(int));

    arr[100] = 0;

    free(arr);

    return 0;

}