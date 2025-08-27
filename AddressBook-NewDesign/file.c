#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook, char * a) {
  
    FILE * fp = NULL;
    fp = fopen(a,"w");

    for(int i = 0; i < addressBook->contactCount; i++){
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook, char * a) {
    FILE * fp = NULL;
    fp = fopen(a,"r");

    if (fp == NULL) {
    printf("Failed to open file\n");
    return;
}

    char name[20];
    char phone[11];
    char mail[20];
    int i = 0;
    while(fscanf(fp," %[^,],%[^,],%[^\n]",name, phone, mail) == 3){
        strcpy(addressBook->contacts[i].name,name);
        strcpy(addressBook->contacts[i].phone,phone);
        strcpy(addressBook->contacts[i].email,mail);
        i++;
        addressBook->contactCount++;
    }
    fclose(fp);
}


int isalphabet(char *a){                          //validating name that given as input
    int i = 1;
    int flag = 0;
    while(a[i]){
        if((isalpha(a[0])) && ((isalpha(a[i])) || (a[i] == ' ') || (a[i] == '.'))){
            flag = 1;
        }else{
            flag = 0;
            break;
        }
        i++;
    }

    if(flag){
        return 1;
    }else{
        return 0;
    }
}
int isneu(char *a){                          //validating number
    int i = 0;
    int flag = 0;
    while(a[i] && a[0] >= '6'){
        if(isdigit(a[i])){
            flag = 1;
        }else{
            flag = 0;
            break;
        }
        i++;
    }
    if(flag && i == 10){
        return 1;
    }
    else{
        return 0;
    }
}
int mail(char *a,int lenght){                     //validating mail id
    int i = 0;
    int flag = 0;
    while(a[i]){
        if(a[i] != tolower(a[i])){
            flag = 0;
            break;
        }
        if( isalpha(a[0]) && (a[i] == '@' && isalnum(a[i - 1]) && isalpha(a[i + 1]))){
            flag = 1;
            break;
        }
        i++;
    }

    if(flag && a[lenght - 1] == 'm' && a[lenght - 2] == 'o' && a[lenght - 3] == 'c' && a[lenght - 4] == '.' ){
        return 1;
    }else{
        return 0;
    }
}
int check(char *a, char *b, int len){             // function for checking a word is present in main string
    
    int i = 0;
    while(a[i]){
        int j = 0;
        while(a[i] == b[j]){
            i++;
            j++;
            if(j == len){
                return 1;
            }
        }
        i++;
    }
    return 0;
}

int idcheck(char *a){                             // added more validation to given mail id
    int start,stop;
    int flag = 0;
    int i = 0;
    while(a[i]){
        if(a[i] == '@'){
            start = i;
        }
        if(a[i] == '.'){
            stop = i;
        }
        i++;
    }
    for(int j = start + 1; j < stop; j++){
        if(isalpha(a[j])){
            flag = 1;
        }else{
            flag = 0;
            break;
        }
    }
    if(flag){
        return 1;
    }else{
        return 0;
    }
}


void disp(){                                      // function for displaying the title and lines 
    printf("\nSN     Name         Phone no.        Address\n");
    printf("----------------------------------------------------\n");
}

void error(char * a){
    printf(RED"\n|---------------%s-------------|\n"RESET,a);
}
void sucess(char *a){
    printf(GREEN"\n|---------------%s-------------|\n"RESET,a);
}
void highlight(char *a, char *b,int l){
    int i = 0;
    int flag = 0;
    while(a[i]){
        int j = 0;
        while(a[i] == b[j]){
            i++;
            j++;
        }
        if(j == l){
            int s = i;
            i = i - l;
            while( i != s){
                printf(BOLD GREEN"%c"RESET,a[i]);
                i++;
            }
            --i;
        }else{
            printf("%c",a[i]);
        }
        i++;
    }

}