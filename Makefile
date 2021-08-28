# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 01:43:12 by gunkim            #+#    #+#              #
#    Updated: 2021/08/26 18:33:08 by gunkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	philosophers - Makefile
#	----------------------------------------
#	Refer to : https://github.com/google/honggfuzz/blob/master/Makefile
#	Refer to : https://github.com/JaeSeoKim/42cursus/blob/master/01_ft_printf/Makefile

# =========================
# what we want to make
# =========================

NAME        := philo
BONUS       := philo_bonus

# =========================
# implicit rule
# =========================

CC        := gcc
CFLAGS    := 
CFLAGS    := -g
# CFLAGS    := -g3 -fsanitize=address
CFLAGS    += -Wall
CFLAGS    += -Wextra
CFLAGS    += -Werror

RM        := rm
RFLAGS    := -rf

# =========================
# source files
# =========================

SRCS := \
	destroy.c \
	dining.c \
	fork.c \
	ft_atoi.c \
	ft_putnbr.c \
	loop.c \
	main.c \
	print.c \
	set_up_dining.c \
	time.c

# =========================
# object files
# =========================

OBJS := $(SRCS:.c=.o)

# =========================
# dependency files
# =========================

DEPS := $(SRCS:.c=.d)

# =========================
# ANSI/VT100
# =========================

LF      := \n
CR      := \r
ESC     := \e

ER      := $(ESC)[1K
CRLF    := $(CR)$(LF)
ERCR    := $(ER)$(CR)

# =========================
# rules
# =========================

.PHONY: all bonus clean fclean re

all : $(NAME)

bonus : $(BONUS)

clean :
	@$(RM) $(RFLAGS) $(OBJS)

fclean :
	@$(RM) $(RFLAGS) $(OBJS) $(NAME) $(BONUS)
	@printf "[$(NAME)] ✔️  Cleaned all !!$(LF)"

re : fclean all

.PHONY: depend clean_depend

depend : $(DEPS)

clean_depend :
	@$(RM) $(RFLAGS) depend_file
	@printf "[$(NAME)] 🧹 Cleaned dependency files$(LF)"

%.d : %.c
	@$(CC) -MM $< | sed 's|^|$(DIR_OBJ)/|' | sed 's|$(DIR_OBJ)/  ||' >> depend_file

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@printf "$(ERCR)[$(NAME)] ✔️  Make $(NAME) !!$(LF)"

%.o : %.c
	@$(CC) -g $(CFLAGS) -c $< -o $@
	@printf "$(ERCR)[$(NAME)] 🔧 Compiling object file $@"

# DO NOT DELETE

dining.o: dining.c philo.h
ft_atoi.o: ft_atoi.c
main.o: main.c philo.h
print.o: print.c philo.h
set_up_dining.o: set_up_dining.c philo.h
time.o: time.c philo.h
