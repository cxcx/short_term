/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2014年09月12日 10时03分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHENXIN,cxandmjq@gmail.com,ID:1096451250
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STATEOK 1
#define STATENO 0

typedef short int STATE;
typedef struct Contact{
    char name[10];
    char tel_number[20];
    char addr[30];
    struct Contact *next;
}Contact, *Contact_ptr;

STATE test_initialized();
STATE Create_user();
void load(FILE *f);
STATE add_item(char *name, char *tel_number, char* addr);
STATE delete_item(char *name);
STATE modify_name(char *name);
STATE modify_addr(char *addr);
STATE modify_telnum(char *tel_number);
void savedisk();
void getexit();
void mkswich();
