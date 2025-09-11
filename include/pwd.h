# ifndef PWD_H
# define PWD_H

#include "string.h"
#include <stdbool.h>
#include "fcntl.h"
#include "unistd.h"
#include "stdio.h"
#include <stdlib.h>



typedef struct s_list
{
  unsigned int key;
  unsigned int len;
  char name[1024];
  char password[1024];
  struct s_list *next;
} t_list;


void    put_on_the_file(t_list *my_list, const char *file);
t_list *create_linked_list(const char *filename);

void ft_bzero(void *s, size_t n);

t_list *find_last(t_list *my_list);
t_list *search_node(t_list *my_list, const char *name);
int add_node(t_list **my_list, char *name, char *password, bool generate);
int delete_node(t_list **my_list, const char *name);
int delete_list(t_list **my_list);

int add_pwd(t_list **my_list);
void modify_pwd(t_list *my_list);
void search_pwd(t_list *my_list);
void delete_pwd(t_list **my_list);
int input_handler(t_list **my_list, const char *buffer);

size_t strcspn(const char *s, const char *reject);
char *fgets(char *buf, int size, int fd);
int strlen(char *str);
char	*itoa(int n);
int atoi(const char *str);
char *strcpy(char *dst, const char *src);

int cypher(char *src, char *dst, int data_len, char *key, int key_len);
int calculate_signature(char *data, int size);
bool verify_signature(char *data, int size, int key);
long get_random_byte();
int generate_password(char *dst, int data_len);

char *open_db(const char *filename);
size_t save_db(const char *filename, const char *data, unsigned long long size);

extern t_list *head;

# endif