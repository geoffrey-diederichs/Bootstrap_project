#include "pwd.h"

void ft_bzero(void *s, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
        ((unsigned char *)s)[i] = '\0';
}

t_list *find_last(t_list *my_list)
{
    if (!my_list)
        return NULL;
    while (my_list->next)
        my_list = my_list->next;
    return my_list;
}

t_list *search_node(t_list *my_list, const char *name)
{
    while (my_list)
    {
        if (strcmp(my_list->name, name) == 0)
            return my_list;
        my_list = my_list->next;
    }
    return NULL;
}

int add_node(t_list **my_list, const char *name, const char *pwd, bool generate)
{
    t_list *new = malloc(sizeof(t_list));
    if (!new)
    {
        perror("malloc");
        return 1;
    }

    strncpy(new->name, name, sizeof(new->name)-1);
    new->name[sizeof(new->name)-1] = '\0';
    strncpy(new->pwd, pwd, sizeof(new->pwd)-1);
    new->pwd[sizeof(new->pwd)-1] = '\0';
    new->len = strlen(pwd);
    new->key = calculate_signature(new->pwd, new->len);
    new->next = NULL;

    if (*my_list == NULL)
    {
        *my_list = new;
    }
    else
    {
        t_list *last = find_last(*my_list);
        last->next = new;
    }
    return 0;
}

int delete_node(t_list **my_list, const char *name)
{
    t_list *tmp = *my_list;
    t_list *prev = NULL;

    while (tmp && strcmp(tmp->name, name))
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp)
    {
        printf("Can't find the service\n");
        return 1;
    }

    ft_bzero(tmp->pwd, strlen(tmp->pwd));
    if (!prev)
        *my_list = tmp->next;
    else
        prev->next = tmp->next;

    free(tmp);
    return 0;
}

int delete_list(t_list **my_list)
{
    t_list *tmp = *my_list;
    t_list *next;

    while (tmp)
    {
        ft_bzero(tmp->pwd, strlen(tmp->pwd));
        next = tmp->next;
        free(tmp);
        tmp = next;
    }

    *my_list = NULL;
    return 0;
}
