

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
    t_list *node = search_node(t_list *my_list);
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

int     input_handler(char *buffer)
{
    if(buffer == "ADD")
        add_pwd();
    else if (buffer == "SEARCH")
        search_pwd();
    else if (buffer == "DELETE")
        delete_pwd();
    else if (buffer == "EXIT")
        exit_pwd();
    else if (buffer == "MODIFY")
        modify_pwd();
    else
        return (1);


}