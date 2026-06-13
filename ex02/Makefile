SHELL := /bin/bash

NAME        = PmergeMe

OBJ_DIR     = objs

RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
CYAN	= \033[0;36m
RESET	= \033[0m

SRCS        = main.cpp\
			PmergeMe.cpp

OBJS        = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	@echo -e "$(CYAN)🔧 Linking: $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo -e "$(GREEN)✅ Compilation terminée avec succès !$(RESET)"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo -e "$(YELLOW)📝 Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo -e "$(YELLOW)🧹 Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo -e "$(RED)🗑️  Full clean...$(RESET)"
	@rm -f $(NAME)

re: fclean all
	@echo -e "$(GREEN)♻️  Rebuilding project...$(RESET)"

.PHONY: all clean fclean re
