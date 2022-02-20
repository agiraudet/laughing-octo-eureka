# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2022/02/20 19:21:20 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	boids

INC_DIR			=	-I includes/ 

DEP				=	-lSDL2 -lSDL2_mixer -lm

SRCS_FILE		=	main.c \
					render.c \
					scene.c \
					boids.c \
					boids_ia.c \
					timer.c \
					calcul.c \
					settings.c \
					data.c \
					stream.c

SRCS_DIR		=	srcs/

SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_FILE))

OBJS			=	$(SRCS:.c=.o)

CFLAGS			=	-Wall -Wextra $(INC_DIR) -g

CC				=	clang

%.o:			%.s
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(DEP) -o $(NAME)

all:			$(NAME)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean flcean re
