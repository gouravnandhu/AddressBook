#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"
#define MAGENTA "\x1b[35m"
#define BOLD "\x1b[1m"
#define RED "\x1b[31m"
//#define RESET "\x1b[0m"

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook, int sortCriteria);
void editContact(AddressBook *addressBook, int sortCriteria);
void deleteContact(AddressBook *addressBook, int sortCriteria);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook,char * name);
void saveContactsToFile(AddressBook *addressBook, char * a);
void saveAndExit(AddressBook *addressBook,char * name);

#endif
