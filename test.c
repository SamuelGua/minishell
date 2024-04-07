# include <stdio.h>				// printf, perror
# include <stdlib.h>			// malloc, free, exit, getenv
# include <unistd.h>			// write, access, read, close, fork, chdir, getcwd, isatty, ttyname, ttyslot, dup, dup2, pipe, execve, tcsetattr, tcgetattr
# include <fcntl.h>				// open
# include <sys/wait.h>			// wait, waitpid, wait3, wait4
# include <signal.h>			// signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>			// stat, lstat, fstat
# include <dirent.h>			// opendir, readdir, closedir
# include <string.h>			// strerror
# include <termios.h>			// ioctl
# include <readline/readline.h>	// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <curses.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	diff;
	size_t			i;

	i = 0;
	if (n == 0)
		return (0);
	while ((unsigned char)s1[i] && (unsigned char)s2[i]
		&& i < n - 1 && (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	diff = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (diff);
}
int main()
{
	printf("%d\n",ft_strncmp("HOME", "HOME", 12));
}