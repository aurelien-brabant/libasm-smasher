# libasm-smasher

![](https://i.imgur.com/qMOFb6a.png)

`libasm-smasher` is a tester for the 42 network's project called `libasm`.

Many tests are performed to ensure that functions work properly and that
the assembly code respects the most fundamental aspects of the
[System V AMD64 ABI](https://en.wikipedia.org/wiki/X86_calling_conventions#System_V_AMD64_ABI) calling convention.

## Requirements

**This tester will not work on MacOS, you need to have an operating system running on the linux kernel**.

- A GNU/Linux based operating system (tested on Gentoo and Xubuntu 18.04, but it should work on any distribution).
- The `clang` C compiler
- The `nasm` ASM compiler
- The `make` build utility

## Run

You can copy paste the following command, assuming that you're at the root of your
`libasm`'s repository:

```bash
git clone https://github.com/aurelien-brabant/libasm-smasher && cd libasm-smasher && make && ./smasher
```
If you want to specify another path for your `libasm`, feel free to `make` the smasher
using the `make LIBASM_PATH=path/to/your/libasm` syntax. It will override the default
value of the Makefile's variable `LIBASM_PATH`.

## Features

- Complete test modules for mandatory part (`ft_write`, `ft_read`, `ft_strcpy`, `ft_strdup`, `ft_strcmp`, `ft_strlen`).
- The tester checks if callee saved registers are well restored (except `rbp`), as specified by the calling convention.
- Comprehensive logging of errors (error messages and/or diff files for some tests with large outputs such as read tests).

**Note**: Bonus part is not covered BUT coverage will probably come soon. 

## Troubleshooting

> Segfault when running the tester

Then your code is probably faulty. However, my code is obviously not perfect at all, so feel free to open
an issue if you can't figure out why the segfault happens on your system. I also accept pull requests as long as they
fix / add something useful to the project.

> Infinite loop

Same thing than above, your code is probably faulty.

> What does the unpreserved register error means

It means that your code does not respect the System V AMD64 ABI calling convention, which is definitely **BAD**. This is not a warning,
that's an error. It can cause several and unexpected errors after your ASM routines have been called. Some reading about the calling
convention described above will tell you why it is bad, and how to deal with it. 
