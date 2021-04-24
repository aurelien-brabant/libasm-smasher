LIBASM_PATH	=	../

NASM			= nasm
ASM_FLAGS		= -felf64 -g
LD				= clang -g 
LD_FLAGS		= -L$(LIBASM_PATH) -lasm
CC				= clang -g -Iinclude 
CFLAGS			= -Wall -Werror -Wextra
RM				= /bin/rm -rf 

SRCS			= $(addprefix src/, check_reg.s assert.c					\
				module_ft_strlen.c module_ft_strcmp.c module_ft_strcpy.c	\
				module_ft_strdup.c module_ft_read.c module_ft_write.c)	

TMPOBJS			= $(SRCS:%.s=%.o)
OBJS			= $(TMPOBJS:%.c=%.o)

BSRCS			= $(addprefix src/, module_ft_atoi_base.c)
BOBJS			= $(BSRCS:%.c=%.o)

TARGET			= smasher
TARGET_BONUS	= smasher.bonus

all: $(TARGET)

$(TARGET): $(OBJS) src/main.o
	make re -C $(LIBASM_PATH)
	$(LD) $(OBJS) src/main.o $(LD_FLAGS) -o $(TARGET)

$(TARGET_BONUS): $(OBJS) $(BSRCS:%.c=%.o) src/main_bonus.o
	make fclean -C $(LIBASM_PATH)
	make bonus -C $(LIBASM_PATH)
	$(LD) $(OBJS) $(BOBJS) src/main_bonus.o $(LD_FLAGS) -o $(TARGET_BONUS)

clean:
	$(RM) $(OBJS)

cleanbonus: clean
	$(RM) $(BOBJS)

fclean: clean
	$(RM) $(TARGET)

fcleanbonus: cleanbonus
	$(RM) $(TARGET_BONUS)

re: fclean $(TARGET)

rebonus: fcleanbonus $(TARGET_BONUS)

test: all
	./smasher
	@$(RM) ./smasher

%.o: %.s
	$(NASM) $(ASM_FLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
