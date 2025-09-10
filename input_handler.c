

void    add_pwd()
{
    static t_list   *my_list = NULL;
    t_list  *last;
    if (!my_list)
    {
        my_list = my_malloc(sizeof(t_list));
        if(!my_list)
            /*gerer ce cas d erreur*/;
        /*demander le service et le mdp associe*/
    }
    last = find_last(my_list);
    
    /*demander le service et pour le mdp
    deux options : generer mdp ou en entrer un*/
    add_node(my_list, name, pwd, true);
    printf("password added successfully");
}

void    search_pwd()
{
    /*demander le mdp de quel service veut il*/;
    t_list *node = search_node(t_list *my_list, name);
    if(node == NULL)
    {
        printf("il n existe pas de mdp pour %s", buffer);
        return ;
    }
    /*fonction qui dechiffre le mdp et le print*/;
}

void    delete_pwd()
{
    /*demander le nom du service que l on veut supprimer*/
    delete_node(buffer);

}

int input_handler(char *buffer)
{
    if (ft_strncmp(buffer, "ADD", 3) == 0 && buffer[3] == '\0')
        add_pwd();
    else if (ft_strncmp(buffer, "SEARCH", 6) == 0 && buffer[6] == '\0')
        search_pwd();
    else if (ft_strncmp(buffer, "DELETE", 6) == 0 && buffer[6] == '\0')
        delete_pwd();
    else if (ft_strncmp(buffer, "EXIT", 4) == 0 && buffer[4] == '\0')
        exit_pwd();
    else if (ft_strncmp(buffer, "MODIFY", 6) == 0 && buffer[6] == '\0')
        modify_pwd();
    else
        return 1;
    return 0;
}
