
#include "pwd.h"

int     modify_node(t_list *my_list, char *name)
{
    /*retrouver le nom du service et demander par quoi
    veut on le modifier. P-e le rechiffrer derriere.*/
}

void	ft_bzero(void *s, size_t n)
{
	int	i;

	i = -1;
	if (n > 0)
	{
		while ((size_t)++i < n)
		{
			*(unsigned char*)(s + i) = '\0';
		}
	}
}


int    delete_node(t_list *my_list, char *name)
{
    t_list *tmp = my_list;
    t_list *prev = NULL;
    
    while (tmp && strcmp(tmp->name, name))
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
    {
        printf("Can't find the service\n");
        return (1);
    }
    ft_bzero(tmp.pwd, ft_strlen(tmp.pwd));
    if (prev == NULL)
        *my_list = tmp->next;
    else
        prev->next = tmp->next;
    free(tmp);
    return (0);

}

int     delete_list(t_list *my_list, char *name)
{
    t_list *tmp = my_list;
    t_list *next = NULL;
    while (tmp)
    {
        ft_bzero(tmp.pwd, ft_strlen(tmp.pwd));
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    return (0);
}

t_list *search_node(t_list* my_list, char *name)
{
    t_list *tmp = my_list;

    while(tmp)
    {
        if (strncmp(tmp->name, name) && )
    }
}

int     add_node(t_list *my_list, char *name, char *pwd, bool generate)
{
    t_list *last = find_last(my_list);
    t_list *new = malloc(sizeof(t_list));
    if (!new)
    {
        printf("error malloc");
        return (1);
    }

    ft_strncpy(new->name, name, 1024);
    ft_strncpy(new->pwd, pwd, 1024);
    new->next = NULL;
    last->next = new;
    return (0);
}

t_list  *find_last(t_list *my_list)
{
    t_list *tmp = my_list;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    return (tmp);
}