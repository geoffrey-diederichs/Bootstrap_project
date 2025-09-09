# ifndef PWD_H
# define PWD_H



typedef struct s_list
{
  unsigned int key;
  unsigned int len;
  char name[1024];
  char password[1024];
  struct s_list *next;
} t_list;


extern t_list *head;

# endif