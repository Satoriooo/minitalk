# include <stdio.h>
# include <string.h>

int main ()
{
	size_t i = 0;
	size_t n = 3;

	while (i < 64)
	{
		printf("i: %zu, n >> (63 - i) & 1: %zu\n", i, n >> (63 - i) & 1);
		i++;
	}

}