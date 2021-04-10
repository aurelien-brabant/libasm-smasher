# libasm-smasher

![](https://i.imgur.com/qMOFb6a.png)

`libasm-smasher` is a tester for the 42 network's project called `libasm`.

Many tests are performed to ensure that functions work properly and that
the assembly code respects the most fundamental aspects of the
[System V AMD64 ABI](https://en.wikipedia.org/wiki/X86_calling_conventions#System_V_AMD64_ABI) calling convention.

## Features

- Complete test modules for mandatory part (`ft_write`, `ft_read`, `ft_strcpy`, `ft_strdup`, `ft_strcmp`, `ft_strlen`).
- The tester checks if callee saved registers are well restored, as specified by the calling convention. This should NOT happen in any ASM code. Note that `rbp` is not checked. 
- Comprehensive logging of errors (error messages and/or diff files for some tests).

**Note**: Bonus part is not covered BUT coverage will probably come soon. 

## Requirements

**This tester is made for the GNU/Linux and can't be used on MacOS**.

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
