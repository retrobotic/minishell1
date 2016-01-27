##
## Makefile for pushswap in /home/champi_t/rendu/CPE_2015_Pushswap
## 
## Made by theo champion
## Login   <champi_t@epitech.net>
## 
## Started on  Tue Nov 17 18:48:59 2015 theo champion
## Last update Sun Jan 24 23:25:59 2016 theo champion
##

CC	= cc

RM	= rm -f

SRC     = main.c		\
          get_next_line.c	\
          lib.c			\
          utils.c		\
          builtin.c		\
          list_tool.c

NAME    = mysh

OBJS	= $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJS)
	$(CC) -g -o $(NAME) $(SRC)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
