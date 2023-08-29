#include "contact.h"
#include "utils.h"


void search_contact(contact *contacts,int *num_contact){
    int choice;

}

void delete_contact(){
    // he will delete the contact in the array and and in the file
    
}

void show_contacts(contact *contacts, int *num_contact){
     if(contacts==NULL || *num_contact==0){
        printf("No contacts yet\n");
    }

    for (int i = 0; i< *num_contact;i++){
        printf("[name] %s [number] %s [email] %s\n",contacts[i].name, contacts[i].number,contacts[i].email);
    }

}

void load_contacts(contact *contacts,int *max_contact,int *num_contact)
{
    FILE *file;
    char buffer[1024];
    file = fopen("./data/data.txt","r");
    if (file==NULL){
        fprintf(stderr,"Error reading file!\n");
        exit(1);
    }


    while(fgets(buffer,sizeof(buffer),file)!=NULL){
        //check memory size first
        if(*num_contact>=*max_contact){
            *max_contact *=2;
            contacts = realloc(contacts,(*max_contact)*sizeof(contact));
            if(contacts==NULL){
                fprintf(stderr,"Memory allocation failed!\n");
                fclose(file);
                exit(1);
            }
        }
        // read the data and append to the array
        if(sscanf(buffer,"%99s %99s %99s",contacts[*num_contact].name,contacts[*num_contact].number,contacts[*num_contact].email)==3){
            printf("loading contact n-%d: name: %s\n",*num_contact, contacts[*num_contact].name);
            (*num_contact)++;
        }
    }
    fclose(file);
    printf("Finish loading!\n");
    printf("\033[H\033[J");
    fflush(stdout);
}


void add_contact(contact *contacts, int *max_contact, int *num_contact)
{
    char name[100];
    char number[100];
    char email[100];

    printf("num_contact: %d, max_contact: %d\n",*num_contact,*max_contact);

   if (*num_contact >= *max_contact){
        *max_contact *= 2; 
        contact *new_contacts = realloc(contacts, *max_contact * sizeof(contact)); 

        if  (new_contacts == NULL){
            fprintf(stderr,"Memory allocation failed!\n");
            exit(1);
        }
        contacts = new_contacts; // Update the pointer
    } 

    contact new_contact;
    
    flush_input();
   
    get_user_input("\t\tPlease enter contact name:\n",name,sizeof(name)); 
    strcpy(new_contact.name, name);

    get_user_input("\t\tPlease enter contact number:\n",number, sizeof(number));
    strcpy(new_contact.number, number);

    get_user_input("\t\tPlease enter contact email:\n",email,sizeof(email));
    strcpy(new_contact.email,email);


    contacts[*num_contact]=new_contact;
    (*num_contact)++;

    save_history(&new_contact);
    fflush(stdout); 
    printf("Added contact succesfully!\n[name] %s, [number] %s, [email] %s.\n\n\n",
            new_contact.name, new_contact.number,new_contact.email);
    printf("num_contact: %d, max_contact: %d\n",*num_contact,*max_contact);
}


void save_history(contact *contact)
{
    FILE *fptr;
    fptr= fopen("./data/data.txt","a");
    if(fptr==NULL){
        fprintf(stderr,"Error opening the file\n");
        exit(1);
    }else{
        fprintf(fptr,"%s %s %s \n", contact->name,contact->number,contact->email);
        printf("Contact data append to history file!\n");
    }
}

