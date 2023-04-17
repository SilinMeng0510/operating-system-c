/**
 * Description: 8.14.1: LAB: Warm up: Contacts: This code creates a contact list using a linked list data structure, 
 *    where each contact node contains a name and phone number, and allows users to input and display contact information.
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 4/16/2023
 * Creation date: 4/16/2023
 **/
#include <stdio.h>
#include <string.h>

typedef struct ContactNode_struct {
   char contactName[50];
   char contactPhoneNumber[50];
   struct ContactNode_struct* nextNodePtr;
} ContactNode;
/**
 * This code initializes a ContactNode structure with a provided name and phone number
 * Assumption: Name and phone number strings is only up to 50 characters
 * Input parameters: ContactNode* node(node pointer), name[](string), phoneNumber (string)
 * Returns: nothing
**/
void InitializeContactNode(ContactNode* node, char name[], char phoneNumber[]) {
   strcpy(node->contactName, name);
   strcpy(node->contactPhoneNumber, phoneNumber);
   node->nextNodePtr = NULL;
}
/**
 * This function is our getter for the the name
 * Assumption: contactName is null terminated
 * Input parameters: node(node pointer)
 * Returns: pointer to ContactName
**/
char* GetName(ContactNode* node) {
   return node->contactName;
}
/**
 * This function is our getter for the the phone number
 * Assumption: contactPhoneNumber is null terminated
 * Input parameters: node(node pointer)
 * Returns: pointer to contactPhoneNumber
**/
char* GetPhoneNumber(ContactNode* node) {
   return node->contactPhoneNumber;
}
/**
 * This function takes two nodes pointers and inserts the second after the first
 * Assumption: both pointers point to a vaild sturcture
 * Input parameters: node (node pointer), nextNode (node pointer)
 * Returns: none
**/
void InsertAfter(ContactNode* node, ContactNode* nextNode) {
   nextNode->nextNodePtr = node->nextNodePtr;
   node->nextNodePtr = nextNode;
}
/**
 * This function gets the next node
 * Assumption: paramtetr points to a valid struct
 * Input parameters: node(node pointer)
 * Returns: pointer to nextNodePtr
**/
ContactNode* GetNext(ContactNode* node) {
   return node->nextNodePtr;
}
/**
 * This function prints the contacts info
 * Assumption: personNum is a vaild int
 * Input parameters: node (node pointer), personNum (integer)
 * Returns: none
**/
void PrintContactNode(ContactNode* node, int personNum) {
   printf("Person %d: %s, %s\n", personNum, GetName(node), GetPhoneNumber(node));
}

int main(void) {
   ContactNode person[3];
   ContactNode* head = &person[0];

   
   char name[50];
   char phoneNumber[50];
   for(int i = 0; i < 3; i++){
      fgets(name, sizeof(name), stdin);
      name[strcspn(name, "\n")] = '\0'; 
      fgets(phoneNumber, sizeof(phoneNumber), stdin);
      phoneNumber[strcspn(phoneNumber, "\n")] = '\0'; 
      InitializeContactNode(&person[i], name, phoneNumber);
      if(i > 0){
         InsertAfter(&person[i-1], &person[i]);  
      }
   }

   int personNum = 1;
   ContactNode* currentNode = head;
   while (currentNode != NULL) {
      PrintContactNode(currentNode, personNum);
      currentNode = GetNext(currentNode);
      personNum++;
   }
   
   printf("\nCONTACT LIST\n"); 
   currentNode = head; 
   while (currentNode != NULL) {
      printf("Name: %s\n", GetName(currentNode)); 
      printf("Phone number: %s\n\n", GetPhoneNumber(currentNode)); 
      currentNode = GetNext(currentNode);
   }

   return 0;
}