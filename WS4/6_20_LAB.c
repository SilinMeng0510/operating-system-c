/**
 * Description: 6.20.1: LAB: Track laps to miles: creates a function that converts laps amount to miles
 *    then calls it in with a user input and outputs it
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/22/2023
 * Creation date: 2/22/2023
 **/

#include <stdio.h>


/**
 * This function converts laps to its representation in miles
 * Assumption: each lap is 0.25 miles
 * Input parameters: userlaps (double) 
 * Returns: a double
**/
double LapsToMiles(double userLaps){
   return (userLaps * 0.25);
}

int main(void) {

   double userInput;
   scanf("%lf", &userInput);
   printf("%0.2lf\n", LapsToMiles(userInput));

   return 0;
}
