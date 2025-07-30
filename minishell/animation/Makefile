NAME = animation.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes

SRCDIR = src
OBJDIR = obj
INCDIR = includes

SOURCES = animation.c \
	screen_utils.c \
	matrix_effects.c \
	title_display.c \
	prompt_utils.c \
	run_animation.c

SRCS = $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
