COLOR_RESET = \033[0m
COLOR_RED = \033[91m
COLOR_GREEN = \033[92m
COLOR_YELLOW = \033[93m
COLOR_BOLD = \033[1m
MAKEFLAGS += --no-print-directory


NAME			:= minishell

SRC_DIR			:= src
OBJ_DIR			:= obj
SRCS			= $(MINISHELL_PATH) $(LIBFT_PATH) $(BUILT-IN_PATH) $(PARSING_PATH)

LIBFT_PATH		= $(LIBFT:%=src/libft/%)
LIBFT			= ft_atoi.c ft_isprint.c ft_lstmap_bonus.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c\
					ft_bzero.c ft_itoa.c ft_lstnew_bonus.c ft_putendl_fd.c ft_strlcat.c ft_substr.c\
					ft_calloc.c ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c\
					ft_free.c ft_lstadd_front_bonus.c ft_memchr.c ft_putstr_fd.c ft_strlen.c ft_toupper.c\
					ft_isalnum.c ft_lstclear_bonus.c ft_memcmp.c ft_split.c ft_strmapi.c get_next_line.c\
					ft_isalpha.c ft_lstdelone_bonus.c ft_memcpy.c ft_strchr.c ft_strncmp.c ft_isascii.c\
					ft_lstiter_bonus.c ft_memmove.c ft_strdup.c ft_strnstr.c ft_free_strjoin.c\
					ft_isdigit.c ft_lstlast_bonus.c ft_memset.c ft_striteri.c ft_strrchr.c\

MINISHELL_PATH	= $(MINISHELL:%=src/minishell/%)
MINISHELL		= main.c init_env.c\

BUILT-IN_PATH	= $(BUILT-IN:%=src/built-in/%)
BUILT-IN		= unset.c echo.c export.c export_utils.c pwd.c exit.c env.c cd.c\

PARSING_PATH	= $(PARSING:%=src/parsing/%)
PARSING			= token_utils.c token.c parsing.c delete_quote.c rules_parsing.c expansion.c\
					build_cmd.c build_cmd_utils.c\

INCLUDE			= include/minishell.h include/libft.h include/parsing.h
				
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS			:= -Wall -Wextra -Werror -g3 
CCFLAGS			:= -I include


RM				:= rm -rf
DIR_DUP			= mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(OBJS) -lreadline -o $(NAME)
		@echo "$(COLOR_GREEN)$(COLOR_BOLD)Compilation finie 👍 $(COLOR_RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
		@$(DIR_DUP)
		@$(CC) $(CFLAGS) $(CCFLAGS) -c -o $@ $<


clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(OBJ_DIR) $(NAME)
	@echo "$(COLOR_RED)$(COLOR_BOLD)files deleted$(COLOR_RESET)"


re:
	@$(MAKE) fclean
	@$(MAKE) all

git: fclean
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)- Cleaning done$(COLOR_RESET)"
	@git add *
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)- All files is adding$(COLOR_RESET)"
	@git commit -m "git make fast"
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)- All files is committed$(COLOR_RESET)"
	@git push
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)- Save is done$(COLOR_RESET)"


.PHONY: all clean fclean re git