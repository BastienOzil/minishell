.SILENT:

YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline 

SRC_DIR = srcs
OBJ_DIR = objs
LIBFT_DIR = utils/libft
ANIMATION_DIR = animation

SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/error_messages.c \
	$(SRC_DIR)/expansion.c \
	$(SRC_DIR)/handle_line.c \
	$(SRC_DIR)/lexer_cmd.c \
	$(SRC_DIR)/lexer.c \
	$(SRC_DIR)/logical_ops.c \
	$(SRC_DIR)/parser_utils.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/print_token.c \
	$(SRC_DIR)/quote_parser.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/vanish.c \
	$(SRC_DIR)/wildcard.c \
	
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
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
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(ANIMATION_LIB):
	@make -s -C $(ANIMATION_DIR)

clean:
	@rm -f $(OBJS)
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(ANIMATION_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@make fclean -s -C $(ANIMATION_DIR)

re: fclean all

.PHONY: all clean fclean re
