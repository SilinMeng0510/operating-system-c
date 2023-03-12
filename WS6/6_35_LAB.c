/**
 * Description: 6.35.1: LAB: Sort an array: This code takes the first user input as the size value for the
 *    following inputs and stores them in an array of integers then sorts the array in a descending using 
 *    the SortArray function then outputs them
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 3/10/2023
 * Creation date: 3/8/2023
 **/
#include <stdio.h>

/**
 * This function uses bubble sort to sort a given array
 * Assumption: sortinglist array is not null
 * Input parameters: sortingList(array of integers), numVals(integer)
 * Returns: nothing
**/
void SortArray(int sortingList[], int numVals){
   
   int tmp;
   
   for(int i = 0; i < numVals; i++){
      for(int j = 0; j < numVals-i-1; j++){
         if(sortingList[j] < sortingList[j+1]){
          tmp = sortingList[j];
          sortingList[j] = sortingList[j+1];
          sortingList[j+1] = tmp;
            
         }
         
      }
   }
   
}


int main(void) {

   int userInput[20];
   int size;
   scanf("%d", &size);
   
   for(int i = 0; i < size; i++){
      
      scanf("%d", &userInput[i]);

   }
   SortArray(userInput, size);
   
   for(int i = 0; i < size; i++){
      printf("%d,", userInput[i]);
      
   }
   printf("\n");
   
   return 0;
}
