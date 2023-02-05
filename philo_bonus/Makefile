#*************************************************************************** #
#                                                                              #
#            :::      ::::::::                                                 #
#          :+:      :+:    :+:                                                 #
#        +:+ +:+         +:+         Makefile v2.0                             #
#      +#+  +:+       +#+                                                      #
#    +#+#+#+#+#+   +#+               By: troberts <troberts@student.42.fr>     #
#         #+#    #+#                                                           #
#        ###   ########.fr                                                     #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              VARIABLE REFERENCE                              #
# **************************************************************************** #

NAME= philo

CC= clang
CFLAGS= -Wall -Werror -Wextra -g3 -pthread $(INCLUDE) #-fsanitize=thread
LDFLAGS= -pthread #-fsanitize=thread
DEPFLAGS= -MT $@ -MMD -MP -MF $(DEP_DIR)$*.d

INCLUDE = -I$(INCLUDE_DIR)

INCLUDE_DIR= inc
OBJ_DIR= obj/
SRC_DIR= src/
DEP_DIR= dep/

# **************************************************************************** #
#                                .C & .H FILES                                 #
# **************************************************************************** #

SRC_FILE=	\
			clean.c \
			ft_atoi.c \
			main.c \
			monitor.c \
			philo.c \
			routine.c \
			utils.c

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ_FILE= 	$(SRC_FILE:.c=.o)
OBJ=		$(addprefix $(OBJ_DIR), $(OBJ_FILE))
DEP_FILE=	$(SRC_FILE:.c=.o)
DEP=		$(addprefix $(DEP_DIR), $(DEP_FILE))
#OBJ=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# **************************************************************************** #
#                                HEADER CONFIG                                 #
# **************************************************************************** #

#                 # <-- start here         | <-- middle             # <-- stop here
HEADER_NAME 	= +                      Philo                      #

COLOR_RED		= \033[0;31m
COLOR_GREEN		= \033[0;32m
COLOR_YELLOW	= \033[0;33m
COLOR_BLUE		= \033[0;34m
COLOR_PURPLE	= \033[0;35m
COLOR_CYAN		= \033[0;36m
COLOR_WHITE		= \033[0;37m
COLOR_END		= \033[m

HEADER =		@echo "${COLOR_CYAN}\
				\n/* ************************************************************************** */\
				\n/*                                                                            */\
				\n/*            :::      ::::::::                                               */\
				\n/*          :+:      :+:    :+:                                               */\
				\n/*        +:+ +:+         +:${HEADER_NAME}*/\
				\n/*      +\#+  +:+       +\#+                                                    */\
				\n/*    +\#+\#+\#+\#+\#+   +\#+                       Thomas Robertson                */\
				\n/*         \#+\#    \#+\#                     <troberts@student.42.fr>            */\
				\n/*        \#\#\#   \#\#\#\#\#\#\#\#.fr                                                   */\
				\n/*                                                                            */\
				\n/* ************************************************************************** */\
				\n \
				\n${COLOR_END}"

HEADER_VAR =	@echo "${COLOR_CYAN}\
				BINARY NAME: $(NAME) \
				\n CC: $(CC) \
				\n CFLAGS: $(CFLAGS) \
				\n LDFLAGS: $(LDFLAGS) \
				\n${COLOR_END}"

HEADER_COMPIL =	@echo "${COLOR_YELLOW}\
					\n/* ************************************************************************** */\
					\n/*                                 COMPILING...                               */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

HEADER_CLEAN =		@echo "${COLOR_RED}\
					\n/* ************************************************************************** */\
					\n/*                                 CLEANING...                                */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

HEADER_FCLEAN =		@echo "${COLOR_RED}\
					\n/* ************************************************************************** */\
					\n/*                              FORCE CLEANING...                             */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

HEADER_NORM =		@echo "${COLOR_PURPLE}\
					\n/* ************************************************************************** */\
					\n/*                            CHECKING THE NORM...                            */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): FORCE header
	$(HEADER_VAR)
	@echo -n "${COLOR_YELLOW}Compiling : \n[${COLOR_END}"
	@$(MAKE) --no-print-directory --silent $(OBJ)
	@echo -n "${COLOR_YELLOW}]\n\n${COLOR_END}"
	@echo -n "${COLOR_GREEN}Linking : "
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LIBFT_LIB)
	@echo "${COLOR_GREEN}Done. ${COLOR_END}"

FORCE: ;

malloc_test: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -fsanitize=undefined -rdynamic -o $@ $(OBJ) -L. -lmallocator

bonus: $(NAME)

#obj_rule : $(OBJ)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo -n "${COLOR_YELLOW}#${COLOR_END}"
	@$(CC) $(CFLAGS) -c $< -o $@

# $(DEP): | $(DEP_DIR)

# $(DEP_DIR):
# 	mkdir -p $@

# $(DEP): $(SRC_DIR)%.c
# 	$(CC) $(DEPFLAGS) $(CFLAGS) -o $@

header:
	$(HEADER)

cleanobj:
	@rm -f $(OBJ)

cleanobjdir: cleanobj
	@rm -rf $(OBJ_DIR)

clean: header
	@echo "${COLOR_RED}Removing objects.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent cleanobj
	@echo "${COLOR_RED}Removing object directory.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent cleanobjdir

fclean: clean
	@echo "${COLOR_RED}Removing binary file.\n${COLOR_END}"
	@rm -f $(NAME) $(NAME_BONUS)

re: header fclean all

reobj: cleanobj
	make -C .

norm: header
	@echo -n "$(COLOR_GREEN)"
	-python3 -m norminette $(SRC_DIR)
	@echo "$(COLOR_PURPLE)"
	-python3 -m norminette $(INCLUDE_DIR)
	@echo -n "$(COLOR_END)"

.PHONY: all clean fclean re reobj norm header cleanobj bonus obj_rule

# include $(DEP)

# DEP_CFLAGS=-MM -MD
# ALL_CFLAGS=-I ./inc -Wall -Wextra -Werror
# src=$(wildcard *.c)
# dep=$(src:.c=.d)
# 
# ... (other flags, other rules like all etc.)
# 
# %.o:%.c
#     $(CC) -c $< $(ALL_CFLAGS) -o $@
# %.d:%.c
#     $(CC) $< $(DEP_FLAGS) $(ALL_CFLAGS) -o $@
# 
# ... (other rules etc.)
# 
# #This below has to be at the end of the Makefile, else it does not work
-include $(DEP_FILE)