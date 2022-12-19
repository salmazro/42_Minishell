# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalhamel <aalhamel@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 13:01:55 by fkhan             #+#    #+#              #
#    Updated: 2022/12/08 17:44:19 by aalhamel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= libft_printf.a
CC 					= gcc
FLAGS 				= -Wall -Werror -Wextra
LIB					= ar -rcs
INCLUDES 			= -I$(HEADERS_DIRECTORY)

HEADERS_DIRECTORY 	= ./includes/
HEADERS_LIST 		= ft_printf.h
HEADERS 			= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY 	= ./sources/
SOURCES_LIST 		= ft_printf.c\
						utlityprintf.c\
						utlityprintf2.c
SOURCES 			= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY 	= objects/
OBJECTS_LIST 		= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS				= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS
GREEN 				= \033[0;32m
RED					= \033[0;31m
RESET 				= \033[0m

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(LIB) $(NAME) $(OBJECTS)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo ".\c"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re