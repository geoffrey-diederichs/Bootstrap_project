#include "pwd.h"

t_list *head = NULL;



int main(void)
{
    char buffer[1024];
    if (open(secret.csv))
    {
        create_file();
    }
    printf("choose option : ADD, SEARCH, MODIFY, DELETE, EXIT");
    /*afficher les options disponibles.*/
    while(1)
    {
        my_ptrace();
        getline(buffer, 1024,);
        if (strncmp(buffer, "EXIT", 4) && buffer[4] == '\0')
            break;
        if (input_handler(buffer))
            printf("bad input");
    }
    clean_all();
}