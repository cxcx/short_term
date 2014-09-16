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
    while(1)
    {
        mkswich();
    }
    return 0;
}

void mkswich()
{
    int i;
    printf("to show all press 1\nadd someone please press 2\nto delete someone please 3\nto search someone please press 4\n5 is for exit\nplease input ur choice:");
    scanf("%d", &i);
    if((i!=1)&&(i!=2)&&(i!=3)&&(i!=4)&&(i!=5))
    {
        printf("ilegle input\n");
        exit(0);
    }
    switch(i){
        case 1:
            show_all();
            break;
        case 2:
            char name_temp[10];
            char tel_number_temp[20];
            char addr_temp[30];
            printf("please input the name(less 10 words):");
            scanf("%s", name_temp);
            printf("please input the tel_number_temp:");
            scanf("%s", tel_number_temp);
            printf("please input the address:");
            scanf("%s", addr_temp);
            add_item(name_temp, tel_number_temp, addr_temp);
            break;
        case 3:
            char delete_name[10];
            printf("please input who u want to delete:");
            scanf("%s", delete_name);
            delete_item(delete_name);
            break;
        case 4:
            char search_name[10];
            printf("please input the name for search:");
            scanf("%s", search_name);
            break;
        case 5:
            getexit();
            break;
    }
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
 *         Name:  show_all
 *  Description:  
 * =====================================================================================
 */
void show_all()
{
    if(numoflist == 0)
    {
        printf("no contacts\n");
    }
    else
    {
        Contact_ptr temp_ptr = head;
        int i = 0;
        for(; i<numoflist; i++)
        {
            printf("%d.", i);
            printf("Name:%s;\ntelephone number:%s;\nadress:%s:\n", temp_ptr->name, temp_ptr->tel_number, temp_ptr->addr);
            temp_ptr = temp_ptr->next;
        }
    }
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  add_item
 *  Description:  
 * =====================================================================================
 */
void add_item(char *name, char *tel_number, char *addr)
{
    Contact_ptr temp_ptr = NULL;
    if(numoflist == 0)
    {
        head = (Contact_ptr)malloc(sizeof(Contact));  
        strcpy(head->name, name);
        strcpy(head->tel_number, tel_number);
        strcpy(head->addr, addr);
        ptr = head;
        numoflist++;
    }
    else
    {
        ptr->next = (Contact_ptr)malloc(sizeof(Contact));
        strcpy(ptr->next->name, name);
        strcpy(ptr->next->tel_number, tel_number);
        strcpy(ptr->next->addr,addr);
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
STATE delete_item(char* name_temp)
{
    Contact_ptr temp_ptr = head;
    if(strcmp(temp_ptr->name, name_temp) == 0)
    {
                head = head->next;
                free(temp_ptr);
                return STATEOK;
    }
    while(temp_ptr->next != NULL && strcmp(temp_ptr->next->name, name_temp) != 0)
    {
        temp_ptr = temp_ptr->next;
        if(temp_ptr->next == NULL)
        {
            printf("this contact doesn't exit\n");
            return STATENO;
        }
        else
        {
            Contact_ptr temp = temp_ptr->next;
            temp_ptr->next = temp_ptr->next->next;
            free(temp);
            numoflist--;
           return STATEOK;
        }
    }
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  serch_item
 *  Description:  
 * =====================================================================================
 */
Contact_ptr serch_item(char* name_temp)
{
    Contact_ptr temp_ptr = head;
    Contact_ptr serch_result = NULL;
    Contact_ptr serch_home = NULL;
    while(temp_ptr != NULL)
    {
        temp_ptr = temp_ptr->next;
        if(strcmp(temp_ptr->name, name_temp) == 0)
        {
            if(serch_home == NULL)
            {
                serch_home = serch_result = temp_ptr;
            }
            else
                serch_result->next = temp_ptr;
                serch_result = serch_result->next;
        }
    }
    return serch_home;
}
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  savedisk
 *  Description:  
 * =====================================================================================
 */
void savedisk()
{

    Contact_ptr temp = head;
    FILE* f= fopen("ContactList","rb");
    int i = 0;
    fwrite(&id_length, sizeof(int), 1, f);
    fwrite(&id, sizeof(char), id_length, f);
    fwrite(&numoflist, sizeof(int), 1, f);
    //for(; i<numoflist; i++)
    //{
     //    fwrite(temp, sizeof(Contact), numoflist, file);
       //  temp = temp->next;
    //}
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
    savedisk();
    Contact_ptr temp = head;
    int i = 0;
    for(; i<numoflist ;i++)
    {
        free(temp);
        temp = temp->next;
    }
    printf("exited\n");
    exit(0);
}

