#define CONTACT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
    char name[100];
    char number[100];
    char email[100];
} contact;

void interface();
void show_contacts(contact *contacts,int *num_contact);
void add_contact(contact *contacts,int *max_contact, int *num_contact);
void update_contact();
void delete_contact();
void show_contact();
void search_contact(contact *contacts,int *num_contact);
void search(contact *contacts,int *num_contact);
void load_contacts(contact *contacts, int *max_contact,int *num_contact);
void save_history(contact *contact);



