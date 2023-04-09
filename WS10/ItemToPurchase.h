#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

#define MAX_LEN 30

typedef struct ItemToPurchase {
   char itemName[MAX_LEN];
   int itemPrice;
   int itemQuantity;
} ItemToPurchase; 

void MakeItemBlank(ItemToPurchase *item);

void PrintItemCost(ItemToPurchase item);

#endif