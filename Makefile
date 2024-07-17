NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBMLX	:= ./MLX42
LIBFT	:= ./libft

HEADERS		:= -I ./include -I $(LIBMLX)/include
LIBS		:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -g
SRCS		:= ./src/main.c ./src/check_arguments.c ./src/init.c ./src/utils.c ./src/fractol.c \
			   ./src/maths.c ./src/mouse_and_keyboard.c ./src/colors.c
OBJS		:= ${SRCS:.c=.o}

all: libmlx $(NAME)

.libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@touch .libmlx;

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	make -C $(LIBFT)
	$(CC) $(OBJS) $(LIBS) ./libft/libft.a $(HEADERS) -o $(NAME)

libmlx: .libmlx

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build
	@rm -rf .libmlx

fclean: clean
	make -C $(LIBFT) fclean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
