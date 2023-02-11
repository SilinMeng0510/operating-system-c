/**
 * Description: 3.22.1: LAB: Smallest number, This code uses if statments to determine the smallest number of three inputted values"
 * Author names:Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/6/23
 * Creation date: 2/6/23
 **/#include <stdio.h>

int main(void) {

   int x, y ,z;
   int smallest;
   scanf("%d %d %d", &x, &y ,&z);

   if(x <= y && x <= z){
      smallest = x;
   }
   else if(y <= x && y <= z){
      smallest = y;
   }
   else{
      smallest = z;
   }

   printf("%d\n", smallest);
   return 0;
}
