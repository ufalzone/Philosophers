# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 18:16:42 by ufalzone          #+#    #+#              #
#    Updated: 2025/02/27 15:42:17 by ufalzone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Couleurs
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
CYAN = \033[36m
RESET = \033[0m

# Nom de l'exécutable
NAME = philo

# Répertoires
SRC_DIR = src
INCLUDE_DIR = includes
OBJ_DIR = obj

# Fichiers sources et objets
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_FILES_BONUS = $(SRC_FILES_BONUS:%.c=$(OBJ_DIR)/%.o)
DEP_FILES = $(OBJ_FILES:.o=.d) $(OBJ_FILES_BONUS:.o=.d)

# Flags de compilation
CC = cc
CFLAGS = -I$(INCLUDE_DIR) -g3

# Règles
.PHONY: all clean fclean re

# Compilation principale
all: $(OBJ_DIR) $(NAME)
	@echo "$(YELLOW)✨ Tout est à jour !$(RESET)"

# Création du dossier obj et ses sous-dossiers
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJ_FILES))

# Compile le projet push_swap
$(NAME): $(OBJ_FILES)
	@printf "$(GREEN)🚀 Compilation de $(NAME)...$(RESET)                                                                \r"
	@$(CC) $(OBJ_FILES) $(CFLAGS) -o $(NAME)
	@printf "\n$(YELLOW)🚀 Compilation fini ! $(GREEN)$(NAME) $(YELLOW)est prêt !$(RESET)                            \n"

# Règle de compilation des fichiers objets
$(OBJ_DIR)/%.o: %.c
	@printf "$(CYAN)🔄 Compilation de $<...$(RESET)\r"
	@$(CC) $(CFLAGS) -c $< -o $@

# #Regle bonus
# bonus: fclean $(OBJ_DIR) $(OBJ_FILES_BONUS)
# 	@printf "$(GREEN)🚀 Compilation de $(NAME) (bonus)...$(RESET)\r"
# 	@$(CC) $(OBJ_FILES_BONUS) $(CFLAGS) -o $(NAME)
# 	@printf "\n$(YELLOW)🚀 Compilation bonus fini ! $(GREEN)$(NAME) $(YELLOW)est prêt !$(RESET)\n"

# Nettoyage complet
fclean: clean
	@echo "$(RED)🗑️  Suppression de $(NAME)...$(RESET)"
	@rm -f $(NAME)

# Recompile tout
re: fclean all

-include $(DEP_FILES)
