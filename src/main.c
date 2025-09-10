#include "pwd.h"

int main(void)
{
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
    probleme qui se pose: si l utilisateur fait un ctrl+C*/
    put_on_the_file(head, "secret.csv");
    delete_list(&head);
    return 0;
}
