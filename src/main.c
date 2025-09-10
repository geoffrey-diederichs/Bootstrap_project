#include "file_handler.h"
#include "stdio.h"

int main(void) {
    char *buf = open_db(db_name);
    puts(buf);
    return 0;
}


/*
#include "pwd.h"

int main(void)
{
    t_list *head = NULL;
    char buffer[1024];
    int fd = open("secret.csv", O_RDONLY);

    if (fd == -1)
        create_file();
    else
        create_linked_list(&head);

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

    delete_list(&head);
    clean_all();
    return 0;
}
*/