#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
extern void sucess(char *a);
extern void error(char * a);
extern int isalphabet(char *a);
extern int isneu(char *a);
extern int mail(char *a,int lenght);
extern int check(char *a, char *b, int len);
extern int idcheck(char *a);
extern void disp(void);
void highlight(char *a, char *b,int l);

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    if(sortCriteria == 1){
        for(int i = 0; i < addressBook->contactCount; i++ ){
        for(int j = 0; j < addressBook->contactCount - 1 - i; j++){
            int res = strcmp(addressBook->contacts[j].name,addressBook->contacts[j + 1].name);
            if(res > 0){
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
    }else if(sortCriteria == 2){
        for(int i = 0; i < addressBook->contactCount; i++ ){
        for(int j = 0; j < addressBook->contactCount - 1 - i; j++){
            int res = strcmp(addressBook->contacts[j].phone,addressBook->contacts[j + 1].phone);
            if(res > 0){
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
    }else if(sortCriteria == 3){
        for(int i = 0; i < addressBook->contactCount; i++ ){
        for(int j = 0; j < addressBook->contactCount - 1 - i; j++){
            int res = strcmp(addressBook->contacts[j].email,addressBook->contacts[j + 1].email);
            if(res > 0){
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
    }
    
    printf("*----------------------------------------------------------*\n");
    printf("| SN     Name            Phone no.           Address       |\n");
    printf("*----------------------------------------------------------*\n");
    for(int i = 0; i < addressBook->contactCount; i++){
        printf("|%d.   %-16s\t%2s\t %-18s|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("*----------------------------------------------------------*\n");

    
}

void initialize(AddressBook *addressBook, char * a) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    loadContactsFromFile(addressBook,a);
    
    
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook,char * a) {
    saveContactsToFile(addressBook,a);
     // Save contacts to file
     addressBook->contactCount = 0;
   
    //exit(EXIT_SUCCESS); // Exit the program
}



void createContact(AddressBook *addressBook)
{
	


    char temp[50];
    char num[20];
    char address[50];
    do
    {  
    printf("\n ✏️  Enter name : ");
    scanf("%[^\n]",temp);
    getchar();
    if(isalphabet(temp)){                                     // validating the name
        
        strcpy(addressBook->contacts[addressBook ->contactCount].name,temp);
    }
    if(isalphabet(temp) == 0){
        //printf("\nYou are given invalid name formate\nplease try again...!!!\n");
        error("You are given invalid name formate. Please try again");
    }
    } while (isalphabet(temp) == 0);
    do
    {  
label1 :   printf("\n ✏️  Enter PH no. : ");
    scanf("%[^\n]",num);
    getchar();

    for(int i = 0; i < addressBook ->contactCount; i++){
        if(check(addressBook->contacts[i].phone,num,strlen(num))){
            //printf("This Phone no. already been recorded\nTry another number\n");
            error("This Phone no. is already benn recorded. Try another number");
            goto label1;                                                  //returning to line 103 if the Ph no. is already recorded
        }
    }

    if(isneu(num)){                       //validating number that all are digits and first char is 6 or > 6
        
        strcpy(addressBook->contacts[addressBook ->contactCount].phone,num);
        
    }
    if(isneu(num) == 0){
        //printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
        error("You are given invalid phone no. formate. please try again");
    }
    } while (isneu(num) == 0);

    do
    {
label2: printf("\n ✏️  Enter gmail : ");
        scanf("%[^\n]",address);
        getchar();

        if(idcheck(address) == 0){
            //printf("\nYou are given invalid mail id formate\nplease try again...!!!\n");
            error("You are given invalid mail id formate. Try again");
            goto label2;
        }

        for(int i = 0; i < addressBook ->contactCount; i++){
        if(check(addressBook->contacts[i].email,address,strlen(address))){            //checking if the given mail id is already been recorded or not
            //printf("This mail id is already been recorded\nTry another id\n");
            error("This mail id is already benn recorded. Try another id");
            goto label2;
        }
    }

        if(mail(address,strlen(address))){            // validating mail id given
            
            strcpy(addressBook->contacts[addressBook ->contactCount].email,address);
        }
        if(mail(address,strlen(address)) == 0){
           // printf("\nYou are given invalid mail id formate\nplease try again...!!!\n");
           error("You are given invalid mail id formate. Try again");
        }
    } while (mail(address,strlen(address)) == 0);     // run the loop until submitting a valid mail id
    

    addressBook ->contactCount++;

    sucess("New Contact is created");
    
}

void searchContact(AddressBook *addressBook, int sortCriteria) 
{
    
    if(sortCriteria == 1){   // sorting based on name(sortCriteria == 1)
        char temp[50];
    printf("\n ✏️  Enter the name to be search : ");
    scanf("%[^\n]",temp);
    getchar();
    disp();
    int res = 0;
    int j = 1;
    int ind = 0;
    for(int i = 0; i < addressBook->contactCount; i++){
        res = check(addressBook->contacts[i].name,temp,strlen(temp));        //calling the check function
        if(res == 1){
           // printf("%d. %11s\t%13s\t %s\n",j,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
          
            printf("%d. ",j);highlight(addressBook->contacts[i].name,temp,strlen(temp));printf("\t%13s\t%s\n",addressBook->contacts[i].phone,addressBook->contacts[i].email);
            j++;
        }
    }
    
    

    if(j > 2){
        char phone[20];
label7:    printf("\n ✏️  Enter the number to be search : ");
    scanf("%[^\n]",phone);
    getchar();
    if(!isneu(phone)){
        //printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
        error("You are given invalid phone no. formate. Please try again");
        goto label7;
    }
     disp();
    int res1 = 0;
    for(int i = 0; i < addressBook->contactCount; i++){
        res1 = check(addressBook->contacts[i].phone,phone,strlen(phone));
        if(res1 == 1){
            printf("1. %11s\t%13s\t %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

        }
    }
    //sucess("Search completed");
    }
    if(j == 1){
        //printf("\n\tNo such name found in the directory\n");
        error("No such name found in the directory");
    }else{
        sucess("Search completed");
    }

    }

    else if(sortCriteria == 2){
        char temp[20];
label3:    printf("\n ✏️  Enter the number to be search : ");
    scanf("%[^\n]",temp);
    getchar();
    if(!isneu(temp)){
        //printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
        error("You are given invalid phone no. formate. Please try again");
        goto label3;
    }
    disp();
    int res = 0;
    int j = 1;
    for(int i = 0; i < addressBook->contactCount; i++){
        res = check(addressBook->contacts[i].phone,temp,strlen(temp));
        if(res == 1){
            printf("%d. %11s\t%13s\t %s\n",j,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            j++;
        }
    }
    if(j == 1){
        //printf("\n\tNo such Number found in the directory\n");
        error("No such Number found in the directory");
    }else{
        sucess("Search completed");
    }
    }

    else if(sortCriteria == 3){
        char temp[50];
label4:    printf("\n ✏️  Enter the mail id to be search : ");
    scanf("%[^\n]",temp);
    getchar();
    if(!mail(temp,strlen(temp))){
        //printf("\nYou are given invalid mail id formate\nplease try again...!!!\n");
        error("You are given invalid mail id formate. Please try again");
        goto label4;
    }
    disp();
    int res = 0;
    int j = 1;
    for(int i = 0; i < addressBook->contactCount; i++){
        res = check(addressBook->contacts[i].email,temp,strlen(temp));
        if(res == 1){
            printf("%d. %11s\t%13s\t %s\n",j,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            j++;
        }
    }
    if(j == 1){
        //printf("\n\tNo such mail id found in the directory\n");
        error("No such mail id found in the directory");
    }else{
        sucess("Search completed");
    }
    }

}

void editContact(AddressBook *addressBook, int sortCriteria)
{
	
    if(sortCriteria == 1){
        char temp[50];
    printf("\n ✏️  Enter the name to be Search : ");
    scanf("%[^\n]",temp);
    getchar();
    disp();
    int res = 0;
    int j = 1;
    int ind[addressBook->contactCount];
    int k = 0;
    for(int i = 0; i < addressBook->contactCount; i++){
        res = check(addressBook->contacts[i].name,temp,strlen(temp));
        if(res == 1){
            //printf("%d. %11s\t%13s\t %s\n",j,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf("%d.    ",j);highlight(addressBook->contacts[i].name,temp,strlen(temp));printf("\t%13s\t%s\n",addressBook->contacts[i].phone,addressBook->contacts[i].email);
            j++;
            ind[k] = i;
            k++;
        }
    }
    
    int res1 = 0;
    int j1 = 1;
    int ch;
    if(j == 1){
        //printf("\nNo such Contact is present in the Directory...!\n");
        error("No such Contact is present in the Directory");

    }
    else if(j <= 2){
        for(int a = 0; a < k; a++){
        
            char name[50];
            printf("✏️  Enter new Name : ");
            scanf("%[^\n]",name);
            getchar();
            strcpy(addressBook->contacts[ind[a]].name,name);   //updating with new name
            
            char ch1;
            printf("👉 Do you want to edit phone no. (y / n) :");
            scanf("%c",&ch1);
            getchar();
            if(ch1 == 'y'){
                char phone[20];
label11:         printf("✏️  Enter new phone no. : ");
                scanf("%[^\n]",phone);
                getchar();
                if(!isneu(phone)){
                    //printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
                    error("You are given invalid phone no. formateplease try again...!!!");
                    goto label11;
                }
                strcpy(addressBook->contacts[ind[a]].phone,phone);    //updating with new Ph no.
            }
            char ch2;
            printf(" 👉 Do you want to edit mail id (y / n) :");
            scanf("%c",&ch2);
            getchar();
            if(ch2 == 'y'){
                char meil[50];
label21:                printf(" ✏️  Enter new mail id : ");
                scanf("%[^\n]",meil);
                getchar();
                if(!mail(meil,strlen(meil))){
                    //printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
                    error("You are given invalid mail id formate. Try again");
                    goto label21;
                }
                strcpy(addressBook->contacts[ind[a]].email,meil);       //updating with new mail
            }
            break;
        }
        sucess("Contact edited successfully");
    }
    else if(j >= 2){
        printf("\n ✏️ Enter which one should edit : ");
    scanf("%d",&ch);
    getchar();
    
    for(int a = 0; a < k; a++){ 
        if(ch == (a+1)){
            char name[50];
            printf("✏️ Enter new Name : ");
            scanf("%[^\n]",name);
            getchar();
            strcpy(addressBook->contacts[ind[a]].name,name); 
            
        
            char ch1;
            printf(" 👉 Do you want to edit phone no. (y / n) :");
            scanf("%c",&ch1);
            getchar();
            if(ch1 == 'y'){
                char phone[20];
label1:         printf("✏️ Enter new phone no. : ");
                scanf("%[^\n]",phone);
                getchar();
                if(!isneu(phone)){
                    //printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
                    error("You are given invalid phone no. formate. please try again...!!!");
                    goto label1;
                }
                strcpy(addressBook->contacts[ind[a]].phone,phone);    //updating with new Ph no.
            }
            char ch2;
            printf("👉 Do you want to edit mail id (y / n) :");
            scanf("%c",&ch2);
            getchar();
            if(ch2 == 'y'){
                char meil[50];
label2:                printf("✏️ Enter new mail id : ");
                scanf("%[^\n]",meil);
                getchar();
                if(!mail(meil,strlen(meil))){
                    //printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
                    error("You are given invalid mail id formate. Try again");
                    goto label2;
                }
                strcpy(addressBook->contacts[ind[a]].email,meil);       //updating with new mail
            }
            break;
        }
        }
        sucess("Contact edited successfully");
    }
    
    
        

    
    }
    else if(sortCriteria == 2){
        char temp[20];
label3:    printf("\n ✏️ Enter the phone no. to be Search : ");
    scanf("%[^\n]",temp);
    getchar();
    if(!isneu(temp)){
        //printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
        error("You are given invalid phone no. formate. please try again...!!!");
        goto label3;
    }
    disp();
    int res = 0;
    int j = 1;
    for(int i = 0; i < addressBook->contactCount; i++){
        res = check(addressBook->contacts[i].phone,temp,strlen(temp));
        if(res == 1){
            printf("%d. %11s\t%13s\t %s\n",j,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            j++;
            char phone[20];
label4:            printf("✏️ Enter new Phone no. : ");
            scanf("%[^\n]",phone);
            getchar();
            if(!isneu(phone)){
                   // printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
                   error("You are given invalid phone no. formate. please try again...!!!");
                    goto label4;
                }
            strcpy(addressBook->contacts[i].phone,phone);
            char ch;
            printf("👉 Do you want to edit name (y / n) :");
            scanf("%c",&ch);
            getchar();
            if(ch == 'y'){
                char name[50];
                printf(" ✏️ Enter new Name : ");
                scanf("%[^\n]",name);
                getchar();
                strcpy(addressBook->contacts[i].name,name);
            }
            char ch1;
            printf("👉 Do you want to edit mail id (y / n) :");
            scanf("%c",&ch1);
            getchar();
            if(ch1 == 'y'){
                char mail[50];
                printf("✏️ Enter new mail id : ");
                scanf("%[^\n]",mail);
                getchar();
                strcpy(addressBook->contacts[i].email,mail);
            }
        }
    }
    if(j == 1){
       // printf("\nNo such Contact is present in the Directory...!\n");
       error("No such Contact is present in the Directory...!");
    }else{
        sucess("Contact edited successfully");
    }
    }
    else if(sortCriteria == 3){
        char temp[20];
label5:    printf("\n ✏️ Enter the mail id to be Search : ");
    scanf("%[^\n]",temp);
    getchar();
    if(!mail(temp,strlen(temp))){
        //printf("\nYou are given invalid mail id formate\nplease try again...!!!\n");
        error("You are given invalid mail id formate. Please tyr again");
        goto label5;
    }
    disp();
    int res = 0;
    int j = 1;
    for(int i = 0; i < addressBook->contactCount; i++){
        res = check(addressBook->contacts[i].email,temp,strlen(temp));
        if(res == 1){
            printf("%d. %11s\t%13s\t %s\n",j,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            j++;
            char mail[50];
            printf("✏️ Enter new mail id : ");
            scanf("%[^\n]",mail);
            getchar();
            strcpy(addressBook->contacts[i].email,mail);
            char ch;
            printf(" 👉 Do you want to edit name (y / n) :");
            scanf("%c",&ch);
            getchar();
            if(ch == 'y'){
                char name[50];
                printf("✏️ Enter new Name : ");
                scanf("%[^\n]",name);
                getchar();
                strcpy(addressBook->contacts[i].name,name);
            }
            char ch1;
            printf("👉 Do you want to edit phone no. (y / n) :");
            scanf("%c",&ch1);
            getchar();
            if(ch1 == 'y'){
                char phone[20];
                printf("✏️ Enter new phone no. : ");
                scanf("%[^\n]",phone);
                getchar();
                strcpy(addressBook->contacts[i].phone,phone);
            }
        }
    }
    if(j == 1){
       // printf("\nNo such Contact is present in the Directory...!\n");
        error("No such Contact is present in the Directory...!");
    }else{
        sucess("Contact edited successfully");
    }
    }
    
}

void deleteContact(AddressBook *addressBook, int sortCriteria)
{
	
    if(sortCriteria == 1){
        char temp[50];
    printf("\n 👉 Enter the name to be Delete : ");
    scanf("%[^\n]",temp);
    getchar();
    disp();
    int res = 0;
    int j = 1;
    int ind[addressBook->contactCount];
    int k = 0;
    for(int i = 0; i < addressBook->contactCount; i++){
        res = check(addressBook->contacts[i].name,temp,strlen(temp));
        if(res == 1){
            //printf("%d. %11s\t%13s\t %s\n",j,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf("%d.    ",j);highlight(addressBook->contacts[i].name,temp,strlen(temp));printf("\t%13s\t%s\n",addressBook->contacts[i].phone,addressBook->contacts[i].email);
            j++;
            ind[k] = i;
            k++;
        }
    }
    int res1 = 0;
    int j1 = 1;
    int ch;
    if(j == 1){
        //printf("\nNo such Contact is present in the Directory to be delete...!\n");
        error("No such Contact is present in the Directory to be delete...!");
    }
    else if(j <=2 ){

        for(int a = 0; a < k; a++){
        
            //printf("\nThis Contact is Deleted\n");
            sucess("This Contact is Deleted");
            for(int k = ind[a]; k < addressBook->contactCount; k++){      //shifting the array contact from from that perticular contact to until last
                addressBook->contacts[k] = addressBook->contacts[k + 1];
            }
            addressBook->contactCount--;              // count is decremented
        
    
        }

    }
    else if(j > 2){
        printf("\n 👉 Enter which one should delete : ");
    scanf("%d",&ch);
    getchar();
    for(int a = 0; a < k; a++){
        if(ch == (a+1)){
            //printf("\nThis Contact is Deleted\n");
            sucess("This Contact is Deleted");
            for(int k = ind[a]; k < addressBook->contactCount; k++){      //shifting the array contact from from that perticular contact to until last
                addressBook->contacts[k] = addressBook->contacts[k + 1];
            }
            addressBook->contactCount--;              // count is decremented
        }
    
        }
    }
    
    
    
    }
    
    else if(sortCriteria == 2){
        char temp[20];
label3:    printf("\n 👉 Enter the phone no. to be Delete : ");
    scanf("%[^\n]",temp);
    getchar();
    if(!isneu(temp)){
        //printf("\nYou are given invalid phone no. formate\nplease try again...!!!\n");
        error("You are given invalid phone no. formate");
        goto label3;
    }
    disp();
    int res = 0;
    int j = 1;
    for(int i = 0; i < addressBook->contactCount; i++){
        res = check(addressBook->contacts[i].phone,temp,strlen(temp));
        if(res == 1){
            printf("%d. %11s\t%13s\t %s\n",j,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            j++;
            //printf("\nThis Contact is Deleted\n");
            sucess("This Contact is Deleted");
            for(int k = i; k < addressBook->contactCount; k++){
                addressBook->contacts[k] = addressBook->contacts[k + 1];
            }
            addressBook->contactCount--;
        }
    }
    if(j == 1){
        //printf("\nNo such Contact is present in the Directory to be delete...!\n");
        error("No such Contact found in the Directory");
    }
    }
    else if(sortCriteria == 3){
        char temp[50];
label4:    printf("\n 👉 Enter the mail id to be Delete : ");
    scanf("%[^\n]",temp);
    getchar();
    if(!mail(temp,strlen(temp))){
        //printf("\nYou are given invalid mail id formate\nplease try again...!!!\n");
        error("You are given invalid mail id formate. Please try again");
        goto label4;
    }
    disp();
    int res = 0;
    int j = 1;
    for(int i = 0; i < addressBook->contactCount; i++){
        res = check(addressBook->contacts[i].email,temp,strlen(temp));
        if(res == 1){
            printf("%d. %11s\t%13s\t %s\n",j,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            j++;
            //printf("\nThis Contact is Deleted\n");
            sucess("This Contact is Deleted");
            for(int k = i; k < addressBook->contactCount; k++){
                addressBook->contacts[k] = addressBook->contacts[k + 1];
            }
            addressBook->contactCount--;
        }
    }
    if(j == 1){
        //printf("\nNo such Contact is present in the Directory to be delete...!\n");
        error("No such Contact is present in the Directory to be delete...!");
    }
    }
    
   
}
