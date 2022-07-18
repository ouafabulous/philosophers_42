# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 19:30:49 by omoudni           #+#    #+#              #
#    Updated: 2022/07/17 23:26:10 by omoudni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


define compiling_m
	@echo -n "$(shell tput bold)$(shell tput setaf 3)Compiling - mandatory$1 $(shell tput sgr0)"
		@$(CC) $(CFLAGS) $(CPPFLAGS) -o $1 > /dev/null -c $2
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define finishing_m
	@echo -n "$(shell tput bold)$(shell tput setaf 2)Creating executable - mandatory$1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS_M) $(OBJS_M) -o $1
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define cleaning
	@echo -n "$(shell tput bold)$(shell tput setaf 8)Cleaning $1 $(shell tput sgr0)"
	@rm -rf $1 $2> /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define fcleaning
	@echo -n "$(shell tput bold)$(shell tput setaf 8)Fcleaning $1 $(shell tput sgr0)"
	@rm -f $1 > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

SRC_DIR_M = mandatory/src_m/
OBJ_DIR_M = mandatory/bin_m/
INC_DIR_M = mandatory/includes_m/

SRCS_M = main.c \
		 parser.c \
		 threader.c \
		 philo_creator.c \
		 utils.c \
		 printer.c \
		 routine.c \
		 routine_utils.c \
		 simulation_stopper.c \

OBJS_M = $(addprefix $(OBJ_DIR_M), $(SRCS_M:%.c=%.o))

PHILO = philo

CC = gcc -pthread

CFLAGS = -Werror -Wextra -Wall -g3

CPPFLAGS_M = -I$(INC_DIR_M)

all: $(PHILO)

$(PHILO): $(OBJS_M)
	$(call finishing_m, $(PHILO))

$(OBJ_DIR_M):
	@mkdir -p $(OBJ_DIR_M)

$(OBJ_DIR_M)%.o: $(SRC_DIR_M)%.c | $(OBJ_DIR_M)
	$(call compiling_m, $@, $<)

clean:
	$(call cleaning, $(OBJ_DIR_M), $(OBJ_DIR_B))

fclean: clean
	$(call fcleaning, $(PHILO))

re: fclean all

.PHONY: all clean fclean re
