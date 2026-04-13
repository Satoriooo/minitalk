#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
	unsigned char *bytes = (unsigned char *)av[1];

	printf("Character: %s\n\n", av[1]);

	int i = 0;

	while(i < 3)
	{
		printf("Byte %d (Decimal): %u\n", i + 1, bytes[i]);
		printf("Byte %d (Hex): 0x%X\n", i + 1, bytes[i]);

		printf("Byte %d (Binary): ", i + 1);
		int b = 7;
		while (b)
			printf("%d", bytes[i] >> b-- & 1);
		printf("\n\n");
		i++;
	}
}