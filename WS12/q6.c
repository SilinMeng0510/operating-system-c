/**

 * Description: q6: This program  allocate an array of 100 integers using malloc, then frees the memoery using free, then tries to access data[0] after the memeory has been freed.

 * Author names: Silin Meng, Ibrahim Dobashi

 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu

 * Last modified date: 4/24/2023

 * Creation date: 4/24/2023

 **/

/*



Questions:



Does the program run? The program runs and exits without any errors

What happens when you use valgrind on it? valgrind shows an error message invaild read of size 4 and indicates that we tried to acess memeory that has been freed.

*/

#include <stdio.h>

#include <stdlib.h>



int main() {

    int *arr = (int *) malloc(100 * sizeof(int));

    free(arr);

    printf("%d\n", arr[0]);

    return 0;

}