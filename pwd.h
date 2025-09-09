# ifndef PWD_H
# define PWD_H



typedef struct s_pwd
{
  unsigned int key;
  unsigned int len;
  char name[1024];
  char password[1024];
  t_pwd *next;
} t_pwd;
