LIBASM_PATH	= ../

NASM		= nasm
ASM_FLAGS	= -felf64 -g
LD			= clang -g 
LD_FLAGS	= -L$(LIBASM_PATH) -lasm
CC			= clang -g -Iinclude 
CFLAGS		= -Wall -Werror -Wextra
RM			= /bin/rm -rf 

SRCS		= $(addprefix src/, check_reg.s main.c assert.c						\
				module_ft_strlen.c module_ft_strcmp.c module_ft_strcpy.c		\
				module_ft_strdup.c module_ft_read.c module_ft_write.c)
TMP			= $(SRCS:%.c=%.o)
OBJS		= $(TMP:%.s=%.o)
TARGET		= smasher
TARGET_BONUS  = smasher.bonus

all: $(TARGET)

$(TARGET): $(OBJS)
	make re -C $(LIBASM_PATH)
	$(LD) $(OBJS) $(LD_FLAGS) -o $(TARGET)

$(TARGET_BONUS): $(OBJS)
	make fclean -C $(LIBASM_PATH)
	make bonus -C $(LIBASM_PATH)
	$(LD) $(OBJS) $(LD_FLAGS) -o $(TARGET_BONUS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

test: all
	./smasher
	@$(RM) ./smasher

%.o: %.s
	$(NASM) $(ASM_FLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
