#include <stdio.h>

int main(void)
{
	unsigned char c = 0;
	c = 0 << 7;
	c |= 1 << 6;
	c |= 0 << 5;
	c |= 0 << 4;
	c |= 0 << 3;
	c |= 0 << 2;
	c |= 1 << 1;
	c |= 1 << 0;
	printf("%c\n", c);
}