FROM	ubuntu:18.04
 
RUN		apt-get update -y && apt-get upgrade -y && apt-get install -y	\
											nasm			\
											clang-9			\
											make

# alias gcc and clang to clang-9
RUN	    ln -sf $(which clang-9) /usr/bin/clang && ln -sf $(which clang-9) /usr/bin/gcc

WORKDIR /smasher

COPY	. .	

CMD [ "make", "test", "LIBASM_PATH=/libasm" ]
