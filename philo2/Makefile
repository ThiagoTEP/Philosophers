# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 11:45:55 by thevaris          #+#    #+#              #
#    Updated: 2025/09/26 12:54:58 by thevaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = philosophers.c philosophers_utils.c init_philos.c routine_philos.c check_philos.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "\n------------- COMPILATION DONE -------------\n"
	@echo "\n---- WELCOME TO THE PHILOSPHERS PROJECT ------\n"
	@echo "\n--------------- BY THEVARIS ----------------\n"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo "\n------------- REMOVED OBJECTS -------------\n"

fclean: clean
	rm -f $(NAME)
	@echo "\n------------- REMOVED	 EXECUTABLES -------------\n"

re: fclean all

.PHONY: all clean fclean re
