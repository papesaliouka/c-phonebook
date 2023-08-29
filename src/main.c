#include "contact.h"
#include "utils.h"

void main(){

    int max_contact = 10;
    int num_contact = 0;
    int choice;
    int start = 1;
    contact *contacts=NULL;
    
    contacts = calloc(max_contact,sizeof(contact));
    if(contacts==NULL){
        fprintf(stderr,"Memory allocation failed!\n");
        exit(1);
    }
    
    load_contacts(contacts, &max_contact,&num_contact);

    while(start){
        printf("\033[H\033[J");
        interface();
    
        choice = get_valid_choice(1,4);  
        
        fflush(stdout);

        switch(choice){
            case 1:
                 show_contacts(contacts,&num_contact);
                break;
            case 2:
                add_contact(contacts,&max_contact,&num_contact);
                break;
            case 3:
                search_contact(contacts,&num_contact);
                break;
            case 4:
                start=0;
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

