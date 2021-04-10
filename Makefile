NASM		= nasm
ASM_FLAGS	= -felf64 -g
LD			= clang -g
CC			= clang -g -Iinclude 
CFLAGS		= -Wall -Werror -Wextra
RM			= /bin/rm -rf 

SRCS		= $(addprefix src/, test_unpreserved.s check_reg.s main.c assert.c module_ft_strlen.c)
TMP			= $(SRCS:%.c=%.o)
OBJS		= $(TMP:%.s=%.o)
TARGET		= smasher

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) -o $(TARGET)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

%.o: %.s
	$(NASM) $(ASM_FLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@