#include <unistd.h>

int main()
{
	char *test[] = {"/usr/bin/echo", NULL, "maman", NULL };
	execve(test[0], test, NULL);
}