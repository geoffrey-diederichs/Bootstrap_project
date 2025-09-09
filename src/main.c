#include "crypto.h"

int main(int argc, char **argv, char **envp) {
    char data[] = "Hello world!";
    cypher(*data, "test", 1);
    return 0;
}
