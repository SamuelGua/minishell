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
# include <curses.h>			// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <string.h>

int main(int ac, char **av, char **envp)
{

	char *str;
	(void) ac;
	// (void) av;
	// while(1)
	// {
	// 	str = readline("Coucou > ");
	// 	if(!str)
	// 	{
	// 		break;
	// 	}
	// 	if(strncmp(str, "cd", 2) == 0)
	// 	{
	// 		chdir(av[1]);
	// 	}
	// 	else if(strcmp(str, "ls") == 0)
	// 	{
	// 		char *tab[2] = {"ls", NULL};
	// 		execve("/usr/bin/ls", tab, envp);
	// 	}
	// }

	char *env_var = getenv("PWD");
	if (chdir(av[1]) == -1)
		printf("cd: no such file or directory: %s\n", av[1]);
	else
		printf("FILE %s\n", av[1]);
		char *argv[] = {"/usr/bin/ls", "-l", NULL};
	execve(argv[0], argv, NULL);
	printf("ENVP %s", env_var);
	
}