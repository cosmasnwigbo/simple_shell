#include "shell.h"
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define buff_size 20

/*
 * Display - a function command that display prompt and wait for the user
 * to enter input
 * @**av: parameter of func Display
 * @**env: parameter of func Display
 * Return: no return value expected
 * */

void Display(char **av, char **env);
void Display(char **av, char **env)
{
	char *str = NULL;
	int statue;
	int x = 0;
	int k;
	size_t num = 0;
	ssize_t char_count;
	char *argv[buff_size];
	pid_t child;


	while (true)
	{
		if (isatty(STDIN_FILENO))
			printf("joe$");
		char_count = getline(&str, &num, stdin);
		if (char_count == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		/* handle EOF*/
		while (str[x])
		{
			if (str[x] == '\n')
			str[x] = 0;
			x++;

		}
		/* tokenization*/
		k = 0;
		argv[k] = strtok(str, " ");
		while (argv[k] != NULL)
		{
			k++;
			argv[k] = strtok(NULL, " ");
		}
		/* create a  Process */
		child = fork();

		if (child == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		if (child == 0)
		{
			if (execve(argv[0], argv, env) == -1)
				printf("%s No such file or directory\n", av[0]);
		}
		else
			wait(&statue);
	}
}
