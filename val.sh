#!/bin/bash
make && valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=/home/scely/Documents/minishell/ignore_readline.supp ./minishell
