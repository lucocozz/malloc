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
    #ifdef LIBFT
        show_page_num();
    #endif
    return (0); 
}