# ifndef PWD_H
# define PWD_H



typedef struct s_list
{
  unsigned int key;
  unsigned int len;
  char name[1024];
  char password[1024];
  t_list *next;
} t_list;
