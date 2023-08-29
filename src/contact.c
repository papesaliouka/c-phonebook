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


typedef struct {
    contact contact;
    int id;
}searched;


void search(contact *contacts, int *num_contact){
    // he will search by name and print the contact
    char search_term[100];
    int count=0;
    int choice;
    searched *found=calloc(1,sizeof(searched));
    int found_num=0;

research:    
    printf("\033[H\033[J");
    printf("\n\n\t\tPlease enter the search term (name email number): ");
    scanf("%s",search_term);
    for (int i=0; i<*num_contact;i++){
        if(strcmp(contacts[i].name,search_term)==0||strcmp(contacts[i].email,search_term)==0||strcmp(contacts[i].number,search_term)==0){
            count++;
            found=realloc(found,(found_num+1)*sizeof(searched));
            found[found_num].id=i;
            found[found_num].contact=contacts[i];
            found_num++;
        }
    }
    printf("\n");

selection:

    if(found_num>0){
        int max =0;
        int min =0;
        for(int i=0;i<found_num;i++){
            printf("\t\t[%d]  [name] %s [number] %s [email] %s\n\n\n",i,found[i].contact.name, found[i].contact.number,found[i].contact.email);
            if (found[i].id>max){
                max=found[i].id;
            }
            if (found[i].id<min){
                min=found[i].id;
            }
        }

        printf("\n\n\n");

        printf("\t\tselect the contact you want to update or delete:");
        int selected = get_valid_choice(min,max);
        int choice;
        printf("\n\n\t\t[1] Delete contact\n\n\n");
        printf("\t\t[2] Update contact\n\n\n");
        printf("\t\t[3] cancel\n\n\n");
        choice = get_valid_choice(1,3);
        switch(choice){
            case 1:
                delete_contact(selected,contacts,num_contact);
                return;
            case 2:
                update_contact(selected,contacts,num_contact);
                return;
            case 3:
            default:
                printf("\t\tInvalid choice\n");
                sleep(1);
                printf("\033[H\033[J");
                goto selection;
        }


    }

    if(count==0){
        printf("\t\tNo contact found!\n\n\n");
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

}


void delete_contact(int id, contact *contacts, int *num_contact){
    // he will delete the contact in the array and and in the file
    printf("\033[H\033[J");
    printf("\n\n\t\tAre you sure you want to delete this contact?\n\n\n");
    printf("\t\t[name] %s [number] %s [email] %s\n\n\n",contacts[id].name, contacts[id].number,contacts[id].email);
    printf("\t\t[1] Yes\n\n\n");
    printf("\t\t[2] No\n\n\n");
    int choice = get_valid_choice(1,2);
    switch(choice){
        case 1:
            printf("\033[H\033[J");
            printf("\n\n\t\tContact deleted succesfully!\n\n\n");
            for(int i=id;i<*num_contact;i++){
                contacts[i]=contacts[i+1];
            }
            (*num_contact)--;
            sleep(1);
            return;
        case 2:
            return;
        default:
            printf("\t\tInvalid choice\n");
    }
    
}

void update_contact(int id, contact *contacts, int *num_contact ){
    // he will update the contact in the array and and in the file
start:
    printf("\033[H\033[J");
    printf("\n\n\t\t[1] Update name\n\n\n");
    printf("\t\t[2] Update number\n\n\n");
    printf("\t\t[3] Update email\n\n\n");
    printf("\t\t[4] Cancel\n\n\n");
    int choice;
    choice = get_valid_choice(1,4);
    switch(choice){
        case 1:
            printf("\033[H\033[J");
            printf("\n\n\t\tPlease enter the new name: ");
            scanf("%s",contacts[id].name);
            printf("\n\n\t\tContact updated succesfully!\n\n\n");
            sleep(1);
            return;
        case 2:
            printf("\033[H\033[J");
            printf("\n\n\t\tPlease enter the new number: ");
            scanf("%s",contacts[id].number);
            printf("\n\n\t\tContact updated succesfully!\n\n\n");
            sleep(1);
            return;
        case 3:
            printf("\033[H\033[J");
            printf("\n\n\t\tPlease enter the new email: ");
            scanf("%s",contacts[id].email);
            printf("\n\n\t\tContact updated succesfully!\n\n\n");
            sleep(1);
            return;
        case 4:
            return;
        default:
        printf("\t\tInvalid choice\n");
        sleep(1);
        goto start;
    }
    
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

