#include "pwd.h"

t_list *create_linked_list(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return NULL;

    t_list *head = NULL;
    t_list *tail = NULL;

    int c;
    char tmp_buf[1024];
    int idx;

    while (1)
    {
        t_list *node = malloc(sizeof(t_list));
        if (!node) {
            close(fd);
            return head;
        }
        node->next = NULL;
        node->key = 0;
        node->len = 0;
        node->name[0] = '\0';
        node->password[0] = '\0';

        // --- Lire name ---
        idx = 0;
        while ((c = read(fd, &tmp_buf[idx], 1)) == 1 && tmp_buf[idx] != ' ' && idx < 1023)
            idx++;
        if (c != 1) { free(node); break; } // EOF
        tmp_buf[idx] = '\0';
        strcpy(node->name, tmp_buf);

        // --- Lire key ---
        idx = 0;
        while ((c = read(fd, &tmp_buf[idx], 1)) == 1 && tmp_buf[idx] != ' ' && idx < 31)
            idx++;
        if (c != 1) { free(node); break; }
        tmp_buf[idx] = '\0';
        node->key = atoi(tmp_buf);

        // --- Lire len ---
        idx = 0;
        while ((c = read(fd, &tmp_buf[idx], 1)) == 1 && tmp_buf[idx] != ' ' && idx < 31)
            idx++;
        if (c != 1) { free(node); break; }
        tmp_buf[idx] = '\0';
        node->len = atoi(tmp_buf);

        // --- Lire password ---
        int to_read = node->len;
        idx = 0;
        while (to_read > 0)
        {
            c = read(fd, &node->password[idx], 1);
            if (c != 1) break; // EOF ou erreur
            idx++;
            to_read--;
        }

        // --- Ajouter le noeud à la liste ---
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }

        // --- Sauter un espace éventuel entre les noeuds ---
        read(fd, &c, 1);
        if (c != 1) break; // EOF
    }

    close(fd);
    return head;
}

void    put_on_the_file(t_list *my_list, const char *file)
{
    t_list *tmp = my_list;
    char    buf[32];

    unlink(file);
    int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        return ;
    while(tmp)
    {
        write (fd, tmp->name, strlen(tmp->name));
        write (fd, " ", 1);
        itoa(tmp->key, buf, 10);
        write (fd, buf, strlen(buf));
        write (fd, " ", 1);
        ft_bzero(buf, sizeof(buf));
        itoa(tmp->len, buf, 10);
        write (fd, buf, strlen(buf));
        ft_bzero(buf, sizeof(buf));
        write (fd, " ", 1);
        write (fd, tmp->password, tmp->len);
        tmp = tmp->next;
    }
    close(fd);
    ft_bzero(buf, sizeof(buf));
    /*le processus inverse qd on veut reecrire dans le fichier.*/
}