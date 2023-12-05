#include <stdio.h>
#include <stdlib.h>

typedef struct s_memory
{
    void *mem;
    struct memory *next;
} t_memory;

void	gc(void *adress)
{
	static t_memory	*head;
	t_memory		*node;

	
}

void	*my_alloc(int size)
{
	void	*allocation;
	t_memory	*memory;

	allocation = malloc(size);
	return (allocation);
}

int	main()
{
	char *str = my_alloc(10);
	str[9] = '\0';
	str[0] = 'M';
	printf ("%c || %c\n", str[0], str[9]);
	return (0);
}