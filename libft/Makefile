# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 17:55:26 by rel-mham          #+#    #+#              #
#    Updated: 2023/05/02 14:39:27 by rel-mham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_strlen.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_putstr_fd.c \
	  ft_strcmp.c \
	  ft_strncmp.c \
	  ft_split.c \
	  ft_substr.c \
	  ft_strdup.c \
	  ft_atoi.c \
	  

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJS)
	ar -rc $(NAME) $(OBJS)

%.o:%.c
	gcc $(FLAGS) -c $<

clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)

re:fclean all
