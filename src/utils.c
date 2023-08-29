#include "contact.h"
#include "utils.h"


void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Consume characters until a newline or end-of-file is encountered
    }
}

char *get_user_input(char *prompt, char *buffer, size_t buffer_size){
    printf("%s",prompt);
    fgets(buffer,buffer_size,stdin);
    buffer[strcspn(buffer,"\n")]='\0';
    return buffer;
}


void interface(){
    printf("\t\t********************************************\n");
    printf("\t\t*           Welcome to My Program          *\n");
    printf("\t\t*                                          *\n");
    printf("\t\t********************************************\n");
    printf("\t\t[1] To list all the contacts\t\t\t\t\n");
    printf("\t\t[2] To add a new contact\t\t\t\t\n");
    printf("\t\t[3] To search for a contact\t\t\t\t\n");
    printf("\t\t[4] To quit\t\t\t\t\n");
    printf("\t\t********************************************\n");
    printf("\t\t********************************************\n\n\n\n");
    printf("\t\tEnter your choice: ");
}
