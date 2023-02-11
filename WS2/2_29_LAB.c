/**
 * Description: 2.29.1: LAB: Using math functions, This code takes 3 inputs and uses math functions such as pow, sqrt and fabs to caulcuate different outcomes"
 * Author names:Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/6/23
 * Creation date: 2/6/23
 **/
#include <stdio.h>
#include <math.h>

int main(void) {
   double x;
   double y;
   double z;

   scanf("%lf %lf %lf", &x, &y ,&z);
   printf("%0.2lf %0.2lf %0.2lf %0.2lf\n", pow(x,z), pow(x,pow(y,2)), fabs(y), sqrt(pow((x*y), z)));

   return 0;
}
