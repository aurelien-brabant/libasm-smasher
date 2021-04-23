FROM	ubuntu:18.04
 
RUN		apt-get update -y &&				\
		apt-get upgrade -y &&			\
		apt-get install -y	nasm		\
							clang-9		\
							make

# Compile without bonus support by default, must be modified at runtime by using -e option
ENV		BONUS=0

# alias gcc and clang to clang-9
RUN		ln -sf $(which clang-9) /usr/bin/clang && ln -sf $(which clang-9) /usr/bin/gcc

WORKDIR	/smasher

COPY	. .
RUN		chmod +x init.sh

CMD		[ "./init.sh" ]
