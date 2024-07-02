NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Wunreachable-code -Ofast
LIBMLX	:= ./MLX42
LIBFT	:= ./libft

HEADERS		:= -I ./include -I $(LIBMLX)/include
LIBS		:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		:= ./src/main.c
OBJS		:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	make -C $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) ./libft/libft.a $(HEADERS) -o $(NAME)

clean:
	make -C $(LIBFT) clean
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	make -C $(LIBFT) fclean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
