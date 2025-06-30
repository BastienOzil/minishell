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

SRCS = main.c \
	srcs/exec/executor.c \
	srcs/exec/redirect.c \
	srcs/exec/pipe.c \
	srcs/exec/exec_builtins.c \
	srcs/parse/cleanup.c \
	srcs/parse/error_messages.c \
	srcs/parse/expansion.c \
	srcs/parse/handle_line.c \
	srcs/parse/lexer_cmd.c \
	srcs/parse/lexer.c \
	srcs/parse/logical_ops.c \
	srcs/parse/parser_utils.c \
	srcs/parse/parser.c \
	srcs/parse/print_token.c \
	srcs/parse/quote_parser.c \
	srcs/parse/utils.c \
	srcs/parse/vanish.c \
	srcs/parse/wildcard.c \
	srcs/builtins/builtin_cd.c \
	srcs/builtins/builtin_echo.c \
	srcs/builtins/builtin_env.c \
	srcs/builtins/builtin_exit.c \
	srcs/builtins/builtin_export.c \
	srcs/builtins/builtin_pwd.c \
	srcs/builtins/builtin_unset.c

OBJ_FILES = $(notdir $(SRCS:.c=.o))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))
	
# OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
ANIMATION_LIB = $(ANIMATION_DIR)/animation.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(ANIMATION_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(ANIMATION_LIB) -o $(NAME) $(LFLAGS)
	echo "$(GREEN)"
	echo "                   /\\                     "
	echo "      G H O S T   /in\\   M I N I S H E L L"
	echo "                 / The\\                   "

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: srcs/builtins/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: srcs/exec/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: srcs/parse/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(ANIMATION_LIB):
	@make -s -C $(ANIMATION_DIR)

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
