.SILENT:

YELLOW = \033[1;33m
GREEN  = \033[1;32m
RESET  = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline

# Répertoires
OBJ_DIR = objs
LIBFT_DIR = utils/libft
ANIMATION_DIR = animation

# Fichiers source (avec chemins)
SRCS = main.c \
	srcs/exec/executor.c \
	srcs/exec/redirect.c \
	srcs/exec/pipe.c \
	srcs/exec/exec_builtins.c
	# srcs/parse/lexer.c \
	# srcs/parse/lexer_cmd.c \
	# srcs/parse/print_token.c \
	# srcs/parse/prompt.c

# On garde juste les noms des fichiers pour les .o
OBJ_FILES = $(notdir $(SRCS:.c=.o))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Librairies
LIBFT = $(LIBFT_DIR)/libft.a
ANIMATION_LIB = $(ANIMATION_DIR)/animation.a

# Cible principale
all: $(NAME)

# Link final
$(NAME): $(OBJS) $(LIBFT) $(ANIMATION_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(ANIMATION_LIB) -o $(NAME) $(LFLAGS)
	echo "$(GREEN)"
	echo "                   /\\                     "
	echo "      G H O S T   /in\\   M I N I S H E L L"
	echo "                 / The\\                   "

# Création du dossier objs/ si nécessaire
$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: srcs/exec/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: srcs/parse/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

# Compilation des dépendances
$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(ANIMATION_LIB):
	@make -s -C $(ANIMATION_DIR)

# Nettoyage
clean:
	@rm -rf $(OBJ_DIR)
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(ANIMATION_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@make fclean -s -C $(ANIMATION_DIR)

re: fclean all

.PHONY: all clean fclean re
