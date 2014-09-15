/*
 * =====================================================================================
 *
 *       Filename:  ContactsDirectory.cpp
 *
 *    Description:  the work for this short term 2014/9/10~2014/9/21
 *
 *        Version:  1.0
 *        Created:  2014年09月12日 10时01分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHENXIN,cxandmjq@gmail.com   
 *   Organization:  hdu
 *
 * =====================================================================================
 */
#include "head.h"
FILE *file;
char id[10];
int id_length;
Contact_ptr ptr = NULL;
Contact_ptr head = NULL;
int numoflist = 0;

int main()
{
    if(test_initialized() == STATENO)
    {
        if(Create_user() == STATENO)
            exit(-1);
    }
    load(file);
    return 0;
}

void mkswich()
{
    int i;
    printf("add someone,please press 1,delete someone please 2,search someone please press 3,4 is for exit");
    scanf("%d", &i);
    switch(i):
        case '1':
            char name_temp[10], tel_number_temp[20], addr_temp[30];
            printf("please input the name(less 10 words):%s", name_temp);
            printf("please input the tel_number_temp:");
            scanf("%s", tel_number_temp);
            printf("please input the address:%s", addr_temp);
            scanf("%s", addr_temp);
            add_item(name_temp, tel_number_temp, addr_temp);
            break;
        case '2':

            
            
            

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  STATE test_initialized()
 *  Description:  
 * =====================================================================================
 */
STATE test_initialized()
{
    system("reset");
    if((file = fopen("ContactList", "rb")) == NULL)
    {
        printf("hey man,this is ur first using,please initialize\n");
        return STATENO;
    }
    else
    {
        file = fopen("ContactList", "rb+");
        return STATEOK;
    }
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  STATE Create_user()
 *  Description:  
 * =====================================================================================
 */
STATE Create_user()
{       
    printf("please input ur ID:");
    if((file = fopen("ContactList", "w")) != NULL)
    {
        scanf("%s",id);
        id_length = strlen(id);
        if((fwrite(&id_length, sizeof(int), 1, file) != 0) && (fputs(id, file) != EOF))
        {
            fputc(numoflist, file);
            printf("initialization succeed\n");
        }
    }
    else
    {
        printf("initialization false\n");
        return STATENO;
    }

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  void savediskload(FILE *f)
 *  Description:  
 * =====================================================================================
 */
void load(FILE *f)
{
    int i = 0;
    fread(&id_length, sizeof(int), 1, f);
    fread(id, sizeof(id[0]), id_length, f);
    fread(&numoflist, sizeof(int), 1, f);
    printf("trying to load ur list\n");
    printf("ur id is %s\nthere are %d contacts\n", id, numoflist);
    for(; i<numoflist; i++)
    {
        if(numoflist == 0)
        {
            head = ptr = (Contact_ptr)malloc(sizeof(Contact));
        }
        fread(ptr, sizeof(Contact), 1, f);
        ptr = ptr->next;
    }
    fclose(f);
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  add_item
 *  Description:  
 * =====================================================================================
 */
STATE add_item(char *name, char *tel_number, char *addr)
{
    if(numoflist == 0)
    {
        head = (Contact_ptr)malloc(sizeof(Contact));  
        strcpy(head->name, name);
        strcpy(head->tel_number, tel_number);
        strcpy(head->addr, addr);
        ptr = head->next;
        numoflist++;
    }
    else
    {
        ptr = (Contact_ptr)malloc(sizeof(Contact));
        strcpy(ptr->name, name);
        strcpy(ptr->tel_number, tel_number);
        strcpy(ptr->addr,addr);
        ptr = ptr->next;
        numoflist++;
    }
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delete_item
 *  Description:  
 * =====================================================================================
 */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  savedisk
 *  Description:  
 * =====================================================================================
 */
void savedisk()
{
    FILE* f= fopen("ContactList","rb")
    int i = 0;
    fwrite(&id_length, sizeof(int), 1, f);
    fwrite(&id, sizeof(char), id_length, f);
    fwrite(&numoflist, sizeof(int), 1, f);
    for(; i<numoflist; i++)
    {
         Contact_ptr temp = head;
         fwrite(temp, sizeof(Contact), numoflist, file);
    }
    getexit();
    fclose(f);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  void exit()
 *  Description:  free all space
 * =====================================================================================
 */
void getexit()
{
    Contact_ptr temp = head;
    int i = 0;
    for(; i<numoflist ;i++)
    {
        free(temp);
        temp = temp->next;
    }
}

