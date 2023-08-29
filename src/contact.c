#include "contact.h"
#include "utils.h"




void search_contact(contact *contacts,int *num_contact){
    int choice;
    
    while(1){
        printf("\033[H\033[J");
        printf("\n\n\n\t\t[1] Search by name email or number \n\n\n");
        printf("\t\t[2] Back to main menu\n\n\n");

        choice = get_valid_choice(1,2);

        switch(choice){
            case 1:
                search(contacts,num_contact);
                break;
            case 2:
                return;
            default:
                printf("\t\tInvalid choice\n");
        }
    }
}


void search(contact *contacts, int *num_contact){
    // he will search by name and print the contact
    char search_term[100];
    int count=0;
    int choice;
research:    
    printf("\033[H\033[J");
    printf("\n\n\t\tPlease enter the search term (name email number): ");
    scanf("%s",search_term);
    for (int i=0; i<*num_contact;i++){
        if(strcmp(contacts[i].name,search_term)==0||strcmp(contacts[i].email,search_term)==0||strcmp(contacts[i].number,search_term)==0){
            printf("\n\t\t[%d]  [name] %s [number] %s [email] %s\n\n\n",(i+1),contacts[i].name, contacts[i].number,contacts[i].email);
            count++;
        }
    }
    printf("\n");
    if(count==0){
        printf("\t\tNo contact found!\n\n\n");
    }
    printf("\t\t[1] Search again\n\n\n");
    printf("\t\t[2] Back to main menu\n\n\n");
    choice = get_valid_choice(1,2);
    switch(choice){
        case 1:
            goto research;
            break;
        case 2:
            return;
        default:
            printf("\t\tInvalid choice\n");
    }

}


void delete_contact(){
    // he will delete the contact in the array and and in the file
    
}

void show_contacts(contact *contacts, int *num_contact){
    printf("\033[H\033[J");
    
    int choice;

     if(contacts==NULL || *num_contact==0){
        printf("\n\t\tNo contacts yet\n");
    }

    for (int i = 0; i< *num_contact;i++){
        printf("\n\t\t[name] %s [number] %s [email] %s\n\n\n",contacts[i].name, contacts[i].number,contacts[i].email);
    }

    printf("\t\t[1] Back to main menu\n\n\n");
    choice = get_valid_choice(1,1);

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

    printf("Loading contacts...\n");
    
    
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
            printf("\033[H\033[J");
            printf("loading in progresss (%f) \n",(float)(*num_contact)/(*max_contact));
            (*num_contact)++; 
        }
    }
    fclose(file);
    sleep(2);
    printf("Finish loading!\n");
    sleep(2);
    printf("\033[H\033[J");
    fflush(stdout);
}


void add_contact(contact *contacts, int *max_contact, int *num_contact)
{
redoo:
    printf("\033[H\033[J");
    int choice;
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

    printf("\t\t[1] Add another contact\n\n\n");
    printf("\t\t[2] Back to main menu\n\n\n");

    choice = get_valid_choice(1,2);
    switch(choice){
        case 1:
            goto redoo;
            break;
        case 2:
            return;
        default:
            printf("\t\tInvalid choice\n");
    }
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

