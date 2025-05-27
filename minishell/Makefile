.SILENT:

YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs

OBJS_DIR = objs

LIBFT_DIR = utils/libft

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/lexer.c $(SRC_DIR)/cleanup.c $(SRC_DIR)/utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)What the shell, it compile!"

$(LIBFT):
	make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re


re: fclean all

.PHONY: all clean fclean re
