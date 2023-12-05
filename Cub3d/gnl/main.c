#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd = open ("get_next_line.c", O_RDONLY);
	printf ("%s", get_next_line(fd));
}