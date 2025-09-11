#include "pwd.h"

void ft_bzero(void *s, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
        ((unsigned char *)s)[i] = '\0';
}

void	*memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		*ptr = (unsigned char)c;
		i++;
		ptr++;
	}
	return (s);
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

int add_node(t_list **my_list, char *name, char *password, bool generate)
{
    t_list *new = malloc(sizeof(t_list));
    if (!new)
    {
        printf("malloc");
        return 1;
    }
    memset(new, 0, sizeof(t_list));

    strncpy(name, new->name, sizeof(name)-1);
    new->name[strlen(new->name)] = '\0';
    strncpy(password, new->password, sizeof(new->password)-1);
    new->password[strlen(new->password)] = '\0';
    new->len = strlen(password);
    new->key = calculate_signature(new->password, new->len);
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
    char *key_str = itoa(new->key);
    cypher(new->password, new->password, new->len, key_str, strlen(key_str));
    //printf("DEBUG: Added service: '%s', password: '%s'\n", new->name, new->password);
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

    ft_bzero(tmp->password, strlen(tmp->password));
    if (!prev)
        *my_list = tmp->next;
    else
        prev->next = tmp->next;

    //free(tmp);
    return 0;
}

int delete_list(t_list **my_list)
{
    t_list *tmp = *my_list;
    t_list *next;

    while (tmp)
    {
        ft_bzero(tmp->password, strlen(tmp->password));
        next = tmp->next;
        //free(tmp);
        tmp = next;
    }

    *my_list = NULL;
    return 0;
}
