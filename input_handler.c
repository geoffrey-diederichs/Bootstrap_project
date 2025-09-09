

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