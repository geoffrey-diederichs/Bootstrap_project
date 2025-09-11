#include "pwd.h"

int atoi(const char *str)
{
    int res = 0;
    int sign = 1;

    while (*str == ' ' || (*str >= 9 && *str <= 13)) // skip spaces/tabs/newlines
        str++;

    if (*str == '-' || *str == '+')
        if (*str++ == '-')
            sign = -1;

    while (*str >= '0' && *str <= '9')
        res = res * 10 + (*str++ - '0');

    return res * sign;
}

char *strcpy(char *dst, const char *src)
{
    char *ret = dst;

    while ((*dst++ = *src++)) // copie et ajoute le \0 automatiquement
        ;

    return ret;
}

int strlen(char *str)
{
    int i = 0;
    
    while(str[i] != 0)
    {
        i++;
    }
    return (i);
}

static int	num_digit(long num)
{
	int	cur;

	cur = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		cur++;
	while (num != 0)
	{
		num = num / 10;
		cur++;
	}
	return (cur);
}

char	*itoa(int n)
{
	long	len;
	long	nl;
	char	*result;

	len = num_digit(n);
	nl = n;
	if (n < 0)
		nl *= -1;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = 0;
	if (nl == 0)
		result[0] = '0';
	else
	{
		while (len--, nl != 0)
		{
			result[len] = (nl % 10) + '0';
			nl = (nl - (nl % 10)) / 10;
		}
		if (n < 0)
			result[len] = '-';
	}
	return (result);
}



size_t strcspn(const char *s, const char *reject)
{
    size_t i = 0;

    while (s[i] != '\0') {
        const char *r = reject;
        while (*r != '\0') {
            if (s[i] == *r)
                return i; // on a trouvé un caractère interdit
            r++;
        }
        i++;
    }
    return i; // aucun caractère interdit trouvé
}

char *fgets(char *buf, int size, int fd)
{
    if (size <= 0 || !buf)
        return NULL;

    int i = 0;
    char c;
    while (i < size - 1) {
        int ret = read(fd, &c, 1);
        if (ret <= 0) {
            if (i == 0)  // rien lu -> EOF direct
                return NULL;
            break;       // sinon on renvoie ce qu'on a
        }
        buf[i++] = c;
        if (c == '\n')  // on arrête à la fin de ligne
            break;
    }
    buf[i] = '\0';
    return buf;
}

int add_password(t_list **my_list)
{
    char name[1024];
    char password[1024];

    printf("Enter service name: ");
    if (!fgets(name, sizeof(name), 0))
        return 1;
    name[strcspn(name, "\n")] = '\0';

    printf("Enter password (or leave empty to generate): ");
    if (!fgets(password, sizeof(password), 0))
        return 1;
    password[strcspn(password, "\n")] = '\0';

    if (strlen(password) == 0)
    {
        if (generate_password(password, 20) != 0)
        {
            printf("Failed to generate password\n");
            return 1;
        }
    }

    add_node(my_list, name, password, true);
    
    printf("Password for '%s' added successfully\n", name);
    return 0;
}

void modify_pwd(t_list *my_list)
{
    char service[1024];
    char new_password[1024];

    printf("Enter the service name to modify: ");
    if (!fgets(service, sizeof(service), 0))
        return;
    service[strcspn(service, "\n")] = '\0';

    t_list *node = search_node(my_list, service);
    if (!node)
    {
        printf("No password found for service %s\n", service);
        return;
    }

    printf("Enter the new password: ");
    if (!fgets(new_password, sizeof(new_password), 0))
        return;
    new_password[strcspn(new_password, "\n")] = '\0';

    ft_bzero(node->password, sizeof(node->password));

    char *key_str = itoa(node->key);
    if (!key_str)
    {
        printf("Memory allocation failed\n");
        return;
    }

    cypher(new_password, node->password, strlen(new_password), key_str, strlen(key_str));
    //free(key_str);

    printf("Password updated successfully\n");
}

void search_pwd(t_list *my_list)
{
    char service[1024];

    printf("Service ? ");
    if (!fgets(service, sizeof(service), 0))
        return;
    service[strcspn(service, "\n")] = '\0';

    t_list *node = search_node(my_list, service);
    if (!node)
    {
        printf("No password found for %s\n", service);
        return;
    }

    char *key_str = itoa(node->key);
    if (!key_str)
    {
        printf("Memory allocation failed\n");
        return;
    }

    // Déchiffre
    cypher(node->password, node->password, node->len, key_str, strlen(key_str));
    
    printf("Password: %s\n", node->password);

    // Rechiffre pour garder la sécurité
    cypher(node->password, node->password, node->len, key_str, strlen(key_str));
    //free(key_str);
}

void delete_pwd(t_list **my_list)
{
    char service[1024];
    printf("Service to delete: ");
    if (!fgets(service, sizeof(service), 0))
        return;
    service[strcspn(service, "\n")] = '\0';

    delete_node(my_list, service);
}

int input_handler(t_list **my_list, const char *buffer)
{
    if (strcmp(buffer, "ADD") == 0)
        add_password(my_list);
    else if (strcmp(buffer, "SEARCH") == 0)
        search_pwd(*my_list);
    else if (strcmp(buffer, "DELETE") == 0)
        delete_pwd(my_list);
    else if (strcmp(buffer, "EXIT") == 0)
        return 0;
    else if (strcmp(buffer, "MODIFY") == 0)
        modify_pwd(*my_list);
    else
        return 1;
    return 0;
}
