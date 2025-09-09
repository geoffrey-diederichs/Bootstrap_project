#iunclude "pwd.h"





int main(void)
{
    char buffer[1024];
    if (my_open(secret.csv))
    {
        create_file();
    }
    /*afficher les options disponibles.*/
    while(1)
    {
        my_ptrace();
        read_line(0, buffer) || get_next_line(0);
        if (buffer == "EXIT")
            break;
        if (input_handler(buffer))
            printf("bad input");
    }
    clean_all();
}