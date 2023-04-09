#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

int main(void) {
 
   ItemToPurchase item1, item2;
   MakeItemBlank(&item1);
   MakeItemBlank(&item2);
   char input[MAX_LEN];
   int length = 0;
   
   printf("Item 1\nEnter the item name:\n");
   fgets(item1.itemName, MAX_LEN, stdin);
   length = strlen(item1.itemName);
   if(item1.itemName[length-1] == '\n') { 
      item1.itemName[length-1] = '\0'; 
   }
   printf("Enter the item price:\n");
   fgets(input, MAX_LEN, stdin);
   sscanf(input, "%d", &(item1.itemPrice));
   printf("Enter the item quantity:\n");
   fgets(input, MAX_LEN, stdin);
   sscanf(input, "%d", &(item1.itemQuantity));
   
   printf("\nItem 2\nEnter the item name:\n");
   fgets(item2.itemName, MAX_LEN, stdin);
   length = strlen(item2.itemName);
   if(item2.itemName[length-1] == '\n') { 
      item2.itemName[length-1] = '\0'; 
   }
   printf("Enter the item price:\n");
   fgets(input, MAX_LEN, stdin);
   sscanf(input, "%d", &(item2.itemPrice));
   printf("Enter the item quantity:\n");
   fgets(input, MAX_LEN, stdin);
   sscanf(input, "%d", &(item2.itemQuantity));
   
   printf("\nTOTAL COST\n");
   PrintItemCost(item1);
   PrintItemCost(item2);
   
   printf("\nTotal: $%d\n", item1.itemPrice * item1.itemQuantity + item2.itemPrice * item2.itemQuantity);
   return 0;
}