#ifdef LIBFT
# include "../includes/malloc.h"
#else
# include <stdlib.h>
#endif

int main()
{
    malloc(1024);
    malloc(1024 * 32);
    malloc(1024 * 1024);
    malloc(1024 * 1024 * 16);
    malloc(1024 * 1024 * 128);
    #ifdef LIBFT
        show_alloc_mem(); 
    #endif
    return (0); 
}