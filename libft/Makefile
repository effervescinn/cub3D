# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/14 16:06:15 by lnorcros          #+#    #+#              #
#    Updated: 2020/11/14 16:06:17 by lnorcros         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

REG_FILES = ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcpy.c ft_tolower.c ft_bzero.c ft_memccpy.c ft_putnbr_fd.c ft_strlen.c ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c ft_memcmp.c	ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c
REG_OFILES = $(patsubst %.c,%.o,$(REG_FILES))
BONUS_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUS_OFILES = $(patsubst %.c,%.o,$(BONUS_FILES))
HEADER = libft.h
NAME = libft.a
FLAGS = -Wall -Wextra -Werror

ifdef WITH_BONUS
OFILES = $(REG_OFILES) $(BONUS_OFILES)
else
OFILES = $(REG_OFILES)
endif

all:		$(NAME)

$(NAME):	$(OFILES)
			ar rcs $(NAME) $(OFILES)
			
%.o:		%.c $(HEADER)
			gcc $(FLAGS) -c $< -o $@

clean:
			rm -f $(REG_OFILES) $(BONUS_OFILES)

fclean:		clean
			rm -f $(NAME) 

re:			fclean all

bonus:
			$(MAKE) WITH_BONUS=1 all

.PHONY:		all clean fclean re
