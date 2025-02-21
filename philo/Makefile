# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antauber <antauber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:27:44 by antauber          #+#    #+#              #
#    Updated: 2025/02/21 10:57:57 by antauber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		:=	philo

## ########################################################################## ##
#	INGREDIENTS																  ##
## ########################################################################## ##
# INC			header file locations
#
# SRCS_DIR		source directory
# SRCS			source files
#
# BUILD_DIR		build directory
# OBJS			object files
# DEPS			dependencies files

INC			:=	includes

SRCS_DIR	:=	srcs
SRCS		:=	main.c\
				parse.c\
				utils.c\
				handle_time.c\
				init.c\
				routine.c
SRCS		:=	$(SRCS:%=$(SRCS_DIR)/%)

BUILD_DIR	:=	.build
OBJS		:=	$(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:=	$(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/%.d)

LIB_DIR		=	libft
LIBFT		=	libft/libft.a

## ########################################################################## ##
#	TOOLS																	  ##
## ########################################################################## ##
# CC			compiler
# CFLAGS		compiler flags
#
# RM			force recusfly remove
# DIR_UP		duplicate directory tree

MFLAG		=	--no-print-directory
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -MMD -MP

RM			:=	rm -rf
DIR_DUP		=	mkdir -p $(@D)

# ########################################################################### ##
#	ANSI_CODES																  ##
## ########################################################################## ##

PREV_LINE	:=	\033[A

GREEN		:=	\033[1;32m
BLUE		:=	\033[1;34m
RED			:=	\033[1;31m
YELLOW		:=	\033[1;33m
RESET		:=	\033[0m

## ########################################################################## ##
#	PROGRESS BAR															  ##
## ########################################################################## ##

TOTAL_FILES	:=	$(words $(OBJS))
CURR_FILE	:=	0
BAR_LENGTH	:=	50
NAME_LENGTH	:=	50

define PROGRESS_BAR
	@$(eval CURR_FILE=$(shell echo $$(($(CURR_FILE) + 1))))
	@$(eval PERCENTAGE=$(shell echo $$(($(CURR_FILE) * 100 / $(TOTAL_FILES)))))
	@$(eval FILLED=$(shell echo $$(($(CURR_FILE) * $(BAR_LENGTH) / $(TOTAL_FILES)))))
	@printf "\rCompiling [%d/%d] %-$(NAME_LENGTH)s" $(CURR_FILE) $(TOTAL_FILES) "$(notdir $<)"
	@printf "\n"
	@printf "\r"
	@for i in `seq 1 $(FILLED)`; do printf "█"; done
	@for i in `seq 1 $$(($(BAR_LENGTH) - $(FILLED)))`; do printf "░"; done
	@printf " %3d%%" $(PERCENTAGE)
	@printf "$(PREV_LINE)\r"
endef

## ########################################################################## ##
#	RECIPES																	  ##
## ########################################################################## ##

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n\n${BLUE}Linking objects${RESET}\n"
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "${GREEN}Binary $(NAME) successfully created${RESET}"

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(DIR_DUP)
	$(PROGRESS_BAR)
	@$(CC) -pthread $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	@$(RM) $(BUILD_DIR)
	@echo "${RED}Build directory removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "${RED}Binary $(NAME) removed${RESET}"

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)