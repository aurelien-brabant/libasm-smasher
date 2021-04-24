#! /bin/sh

# If BONUS environment variable is set, compile smasher with support for bonuses. BONUS=0 by default.
# NOTE: in all cases, the resulting archive must be EXACTLY called libasm.a. Otherwise the smasher will not compile.

[ $BONUS -eq  1 ] && suffix=bonus || suffix= 

make re$suffix LIBASM_PATH=/libasm
./smasher*
make fclean$suffix LIBASM_PATH=/libasm
