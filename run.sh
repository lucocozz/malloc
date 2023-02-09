#!/bin/sh
export LD_LIBRARY_PATH="."
export LD_PRELOAD="`pwd`/libft_malloc.so"
$@
