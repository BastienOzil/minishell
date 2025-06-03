.SILENT:

YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=adress -g3

LFLAGS = -lreadline 

SRC_DIR = srcs

OBJS_DIR = objs

LIBFT_DIR = utils/libft

# par ordre alphabetique, sauf main
SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/executor.c \
	$(SRC_DIR)/lexer.c \
	$(SRC_DIR)/lexer_cmd.c \
	$(SRC_DIR)/print_token.c \
	$(SRC_DIR)/prompt.c \
	$(SRC_DIR)/utils.c \
	#$(SRC_DIR)/parser.c \#

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)


GHOST_ANIMATION = \
	bash -c '\
		lines=10; cols=110; \
		for ((i=0; i<$$lines; i++)); do \
			line=""; \
			for ((j=0; j<$$cols; j++)); do \
				char=$$(echo $$((RANDOM%2))); \
				line="$$line$$char"; \
			done; \
			echo "$$line"; \
			sleep 0.05; \
		done; \
	'

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)"
	@$(GHOST_ANIMATION)



# $(NAME): $(OBJS) $(LIBFT)
# 	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LFLAGS)
# 	@echo "$(GREEN)";
	@sleep 0.1; echo " ▗▄▄▖▗▖ ▗▖ ▗▄▖  ▗▄▄▖▗▄▄▄▖    ▗▄▄▄▖▗▖  ▗▖    ▗▄▄▄▖▗▖ ▗▖▗▄▄▄▖    ▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖   ";
	@sleep 0.1; echo "▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌     █        █  ▐▛▚▖▐▌      █  ▐▌ ▐▌▐▌       ▐▛▚▞▜▌  █  ▐▛▚▖▐▌  █  ▐▌   ▐▌ ▐▌▐▌   ▐▌   ▐▌   ";
	@sleep 0.1; echo "▐▌▝▜▌▐▛▀▜▌▐▌ ▐▌ ▝▀▚▖  █        █  ▐▌ ▝▜▌      █  ▐▛▀▜▌▐▛▀▀▘    ▐▌  ▐▌  █  ▐▌ ▝▜▌  █   ▝▀▚▖▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌   ";
	@sleep 0.1; echo "▝▚▄▞▘▐▌ ▐▌▝▚▄▞▘▗▄▄▞▘  █      ▗▄█▄▖▐▌  ▐▌      █  ▐▌ ▐▌▐▙▄▄▖    ▐▌  ▐▌▗▄█▄▖▐▌  ▐▌▗▄█▄▖▗▄▄▞▘▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖";
	@sleep 0.1; echo "                                                                                                              ";
	@echo "$(RESET)"

$(LIBFT):
	@make -s -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make clean -s -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re


re: fclean all

.PHONY: all clean fclean re
