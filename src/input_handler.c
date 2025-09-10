#include "pwd.h"

int add_pwd(t_list **my_list)
{
    char name[1024];
    char pwd[1024];

    printf("Enter service name: ");
    if (!fgets(name, sizeof(name), stdin))
        return 1;
    name[strcspn(name, "\n")] = '\0';

    printf("Enter password (or leave empty to generate): ");
    if (!fgets(pwd, sizeof(pwd), stdin))
        return 1;
    pwd[strcspn(pwd, "\n")] = '\0';

    if (strlen(pwd) == 0)
    {
        if (generate_password(pwd, 20) != 0)
        {
            printf("Failed to generate password\n");
            return 1;
        }
    }

    add_node(my_list, name, pwd, true);
    printf("Password for '%s' added successfully\n", name);
    return 0;
}

void modify_pwd(t_list *my_list)
{
    char service[1024];
    char new_pwd[1024];

    printf("Enter the service name to modify: ");
    if (!fgets(service, sizeof(service), stdin))
        return;
    service[strcspn(service, "\n")] = '\0';

    t_list *node = search_node(my_list, service);
    if (!node)
    {
        printf("No password found for service %s\n", service);
        return;
    }

    printf("Enter the new password: ");
    if (!fgets(new_pwd, sizeof(new_pwd), stdin))
        return;
    new_pwd[strcspn(new_pwd, "\n")] = '\0';

    ft_bzero(node->pwd, sizeof(node->pwd));
    cypher(new_pwd, node->pwd, strlen(new_pwd), itoa(calculate_signature()));
    printf("Password updated successfully\n");
}

void search_pwd(t_list *my_list)
{
    char service[1024];

    printf("Service ? ");
    if (!fgets(service, sizeof(service), stdin))
        return;
    service[strcspn(service, "\n")] = '\0';

    t_list *node = search_node(my_list, service);
    if (!node)
    {
        printf("No password found for %s\n", service);
        return;
    }

    cypher(node->pwd, node->pwd, node->len, itoa(node->key)); // déchiffre
    printf("Password: %s\n", node->pwd);
    cypher(node->pwd, node->pwd, node->len, itoa(node->key)); // rechiffre
}

void delete_pwd(t_list **my_list)
{
    char service[1024];
    printf("Service to delete: ");
    if (!fgets(service, sizeof(service), stdin))
        return;
    service[strcspn(service, "\n")] = '\0';

    delete_node(my_list, service);
}

int input_handler(t_list **my_list, const char *buffer)
{
    if (strcmp(buffer, "ADD") == 0)
        return add_pwd(my_list);
    else if (strcmp(buffer, "SEARCH") == 0)
        search_pwd(*my_list);
    else if (strcmp(buffer, "DELETE") == 0)
        delete_pwd(my_list);
    else if (strcmp(buffer, "EXIT") == 0)
        return 0;
    else if (strcmp(buffer, "MODIFY") == 0)
        modify_pwd(*my_list);
    else
        return 1;
    return 0;
}
