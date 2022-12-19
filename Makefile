NAME 				= minishell
CC 					= gcc -g
FLAGS 				= -Wall -Werror -Wextra
INCLUDES 			= -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) \
						-I$(FT_PRINTF_HEADERS) -I/usr/local/opt/readline/include
LIBRARIES 			= -lft -lft_printf \
						-L$(LIBFT_DIRECTORY) -L$(FT_PRINTF_DIRECTORY) \
						-L/usr/local/opt/readline/lib

LIB_DIRECTORY 		= ./lib/

LIBFT 				= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY 	= $(LIB_DIRECTORY)libft/
LIBFT_HEADERS 		= $(LIBFT_DIRECTORY)includes/

FT_PRINTF			= $(FT_PRINTF_DIRECTORY)libft_printf.a
FT_PRINTF_DIRECTORY = $(LIB_DIRECTORY)ft_printf/
FT_PRINTF_HEADERS 	= $(FT_PRINTF_DIRECTORY)includes/

HEADERS_DIRECTORY 	= ./includes/
HEADERS_LIST 		= minishell.h
HEADERS 			= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY 	= ./sources/
SOURCES_LIST 		= main.c debug.c enviro.c keymap.c sort_list.c signal.c \
						parsing/exec.c\
						parsing/exec_arg.c\
						parsing/parser.c\
						parsing/pipe.c\
						parsing/redir.c\
						parsing/redir2.c\
						parsing/token.c\
						parsing/expansion.c\
						parsing/quotes.c\
						execution/executer.c\
						execution/executer_utils.c\
						execution/run.c\
						builtins/ft_cd.c\
						builtins/ft_env.c\
						builtins/ft_exit.c\
						builtins/ft_pwd.c\
						builtins/ft_echo.c\
						builtins/ft_execve.c\
						builtins/ft_export.c\
						builtins/ft_unset.c\
						utils/env_utils.c\
						utils/str_utils.c\
						utils/str_utils2.c\
						utils/utils.c\
						utils/signal_utils.c



SOURCES 			= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY 	= objects/
OBJECTS_LIST 		= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS				= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS
GREEN 				= \033[0;32m
RED 				= \033[0;31m
RESET 				= \033[0m

all: $(NAME)

bonus: all

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(LIBRARIES) $(INCLUDES) -lreadline -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)/parsing
	@mkdir -p $(OBJECTS_DIRECTORY)/execution
	@mkdir -p $(OBJECTS_DIRECTORY)/builtins
	@mkdir -p $(OBJECTS_DIRECTORY)/utils
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo ".\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(FT_PRINTF):
	@echo "$(NAME): $(GREEN)Creating $(FT_PRINTF)...$(RESET)"
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(FT_PRINTF)
	@echo "$(NAME): $(RED)$(FT_PRINTF) was deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all bonus clean fclean re
