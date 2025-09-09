#include "unistd.h"

int putchar(char c) {
    if (write(1, &c, 1) == -1) {
        return -1;
    }

    return (unsigned char)c;
}

int puts(const char *str) {
    // Print the string character by character
    while (*str) {
        if (putchar(*str++) == -1) {
            return -1;
        }
    }

    // Print the required breakline
    if (putchar(0xa) == -1) {
        return -1;
    }

    return 1;
}

int putnbr(int num) {
    // Contains the ascii representation of num
    char str[12];
    int index = 0;

    // Adds the negative sign if needed
    if (num < 0) {
        str[index++] = '-';
        num *= -1;
    }

    if (num == 0) { // Some exception to take care of
        str[0] = '0';
        str[1] = 0;
    }
    else {
        // Adds the number characters by characters
        long i;
        for (i = 10000000000 ; i >= 10 ; i /= 10) {
            if (num >= i/10) {
                str[index++] = '0' + (num%i)/(i/10);
            }
        }
        str[index] = 0;
    }
    
    // Puts the resulting string
    if (puts(str) == -1) {
        return -1;
    }
    return 1;
}

ssize_t getline(char **lineptr, size_t *n, int fd) {
    // Check if the buffer exists and it's size is big enough
    if (!lineptr || !*lineptr || !n) return -1;
    if (*n < 2) return -1;

    int i, ret;
    // Since we don't have malloc yet, only reading n bytes
    for (i = 0; i < (*n-1); i++) {
        ret = read(fd, &(*lineptr)[i], 1);
        if (ret == 0) { // If read sent back an EOF
            if (i == 0) return -1;
            break;
        } else if (ret != 1) { // If read sent back an error
            (*lineptr)[i] = '\0';
            return -1;
        } else if ((*lineptr)[i] == 0xa) { // If a linebreak is reached
            i++;
            break;
        }
    }
    (*lineptr)[i] = '\0';

    return i;
}

// Same fonction as puts, but without the breakline and returning the number of printed characters
int puts_printf(const char *str) {
    int len = 0;
    // Print the string character by character
    while (*str) {
        if (putchar(*str++) == -1) {
            return -1;
        }
        len++;
    }

    return len;
}

// Same fonction as putnbr, but without the breakline and returning the number of printed characters
int putnbr_printf(int num) {
    // Contains the ascii representation of num
    char str[12];
    int index = 0;

    // Adds the negative sign if needed
    if (num < 0) {
        str[index++] = '-';
        num *= -1;
    }

    if (num == 0) { // Some exception to take care of
        str[0] = '0';
        str[1] = 0;
    }
    else {
        // Adds the number characters by characters
        long i;
        for (i = 10000000000 ; i >= 10 ; i /= 10) {
            if (num >= i/10) {
                str[index++] = '0' + (num%i)/(i/10);
            }
        }
        str[index] = 0;
    }
    
    // Puts the resulting string
    int ret = puts_printf(str);
    if (ret == -1) {
        return -1;
    }
    return ret;
}

// Int overflow and underflow in this function :)
int printf(const char *format, ...) {
    // Using builtins to fetch arguments
    __builtin_va_list ap;
    __builtin_va_start(ap, format);

    // Printing out the string characters by characters
    // Len will keep track of the number of characters printed out by the "formatters"
    // Index will keep track of the other characters
    int index, ret, len = 0;
    for (index = 0; format[index] != 0; index++) {
        // First checking for formatters
        if (format[index] == '%') {
            switch (format[index+1]) {
                case 's':
                    const char *str = __builtin_va_arg(ap, const char *);
                    ret = puts_printf(str);
                    if (ret == -1) {
                        __builtin_va_end(ap);
                        return -1;
                    }
                    index++;
                    len += ret-1;
                    continue;
                case 'd':
                    int nbr = __builtin_va_arg(ap, int);
                    ret = putnbr_printf(nbr);
                    if (ret == -1) {
                        __builtin_va_end(ap);
                        return -1;
                    }
                    index++;
                    len += ret-1;
                    continue;
                case 'c':
                    int c = __builtin_va_arg(ap, int); // Can't directly fetch a char apparently
                    unsigned char out = (unsigned char)c;
                    if (putchar(out) == -1) {
                        __builtin_va_end(ap);
                        return -1;
                    }
                    index++;
                    len -= 1; // -1 since index is increased by 2
                    continue;
            }
        }

        // If no formatter just printing out the character
        if (putchar(format[index]) == -1) {
            __builtin_va_end(ap);
            return -1;
        }
    }
    putchar(0);
    len += index; // Total number of characters printed out

    __builtin_va_end(ap);
    return len;
}
