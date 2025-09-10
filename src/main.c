#include "pwd.h"

void handler(void) { 
    puts("Handler called\n"); 
    exit(-1);
}

int main(void)
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sa.sa_restorer = NULL;
    sa.sa_mask = 0;
    
    sigaction(2, &sa, 0); // 2 == SIGINT
    
    // To test ctrl+c
    char buf[10];
    read(0, buf, 10);
    
    return 0;
}

/*
    t_list *head = NULL;
    char buffer[1024];
    int fd = open("vault.db", O_RDONLY);

    if (fd == -1)
        create_file();
    else
        head = create_linked_list("vault.db");

    printf("choose option : ADD, SEARCH, MODIFY, DELETE, EXIT\n");

    while (1)
    {
        printf("> ");
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "EXIT") == 0)
            break;

        if (input_handler(&head, buffer))
            printf("bad input\n");
    }
    /*reecrire dans le fichier a la toute fin.
    probleme qui se pose: si l utilisateur fait un ctrl+C*//*
    put_on_the_file(head, "secret.csv");
    delete_list(&head);
    return 0;
}
*/
