#include <stdio.h>
#include "contact.h"
void choice(char *);
AddressBook addressBook;
int main() {
    
    
     // Initialize the address book

    int ch;
    do{
    printf(BLUE"══════════════════════════════════════════════════════════════════════════════\n"RESET);
    printf(BOLD MAGENTA"\t\t         Contact List\n"RESET);
    printf("\n1. 👨‍👩‍👦 Family\n2. 🌟 Friends\n3. 📂 Office\n4. 💾 Save and Exit\n");
    printf("👉  Enter your choice :");
    scanf("%d",&ch);
    switch (ch)
    {
    case 1:
        initialize(&addressBook,"family.txt");
        choice("family.txt");
        break;
    case 2:
        initialize(&addressBook,"friend.txt");
        choice("friend.txt");
        break;
    case 3:
        initialize(&addressBook,"office.txt");
        choice("office.txt");
        break;
    case 4:
        printf("Saving...exit\n");
        //exit(EXIT_SUCCESS);
        break;
    default:
        printf("Invalid input\n");
        break;
    }
}while(ch != 4);
   
    
       return 0;
}

void choice(char * a){
    int choice;
     do {
        printf("\nAddress Book Menu:\n");
        printf("1. 👤 Create contact\n");
        printf("2. 🔍 Search contact\n");
        printf("3. ✒️  Edit contact\n");
        printf("4. 🗑️  Delete contact\n");
        printf("5. 📋 List all contacts\n");
        printf("6. 💾 Exit\n");
        printf(" 👉  Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                printf("\nSelect search method:\n");
                printf("1. 🔎 search by name\n");
                printf("2. 🔎 search by phone\n");
                printf("3. 🔎 search by email\n");
                printf("\n 👉 Enter your choice: ");
                int searchChoice;
                scanf("%d", &searchChoice);
                getchar();
                searchContact(&addressBook, searchChoice);
                break;
            case 3:
                printf("\nSelect edit criteria:\n");
                printf("1. ✒️  edit by name\n");
                printf("2. ✒️  edit by phone\n");
                printf("3. ✒️  edit by email\n");
                printf("\n 👉 Enter your choice: ");
                int editChoice;
                scanf("%d", &editChoice);
                getchar();
                editContact(&addressBook, editChoice);
                break;
            case 4:
                printf("\nSelect delete criteria:\n");
                printf("1. 🗑️  delete by name\n");
                printf("2. 🗑️  delete by phone\n");
                printf("3. 🗑️  delete by email\n");
                printf("\n 👉 Enter your choice: ");
                int deleteChoice;
                scanf("%d", &deleteChoice);
                getchar();
                deleteContact(&addressBook, deleteChoice);
                break;
            case 5:
                printf("\nSelect sort criteria:\n");
                printf("1. ↕️  Sort by name\n");
                printf("2. ↕️  Sort by phone\n");
                printf("3. ↕️  Sort by email\n");
                printf("\n 👉 Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveAndExit(&addressBook,a);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}