#ifdef LIBFT
# include "../includes/malloc.h"
#else
# include <stdlib.h>
#endif

# include <string.h>
# include <unistd.h>

void print(char *s)
{
    write(1, s, strlen(s));
}

int main()
{
    char *addr;

    addr = malloc(16);
    free(NULL);
    free((void *)addr + 5);
    if (realloc((void *)addr + 5, 10) == NULL)
        print("Bonjour\n");
}