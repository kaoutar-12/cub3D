#include "cub3d.h"

int main()
{
	int fd = open ("../maps/map.cub");
	char *str = get_next_line(fd);
	while (str)
	{
		printf ("%s\n", str);
		str = get_next_line(fd);
	}
}