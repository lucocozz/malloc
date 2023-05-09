#ifdef LIBFT
# include "../includes/malloc.h"
#else
# include <stdlib.h>
#endif

int      main(void)
{
    int   i;
    char  *addr;

    i = 0; 
    while (i < 1024) 
    {
        i++;
    }
    return (0); 
}