#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	if (open("/dev/stdout", O_RDONLY) == -1)
		return (printf("Error\n"));
	else
		printf("Good");
}