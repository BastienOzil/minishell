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

SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/animations.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/error_messages.c \
	$(SRC_DIR)/executor.c \
	$(SRC_DIR)/lexer.c \
	$(SRC_DIR)/lexer_cmd.c \
	$(SRC_DIR)/print_token.c \
	$(SRC_DIR)/prompt.c \
	$(SRC_DIR)/pipe.c \
	$(SRC_DIR)/utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LFLAGS)
	echo "$(GREEN)"
	echo "                   /\\                     "
	echo "      G H O S T   /in\\   M I N I S H E L L"
	echo "                 / The\\                   "

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@make clean -s -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
