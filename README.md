# LinuxProgramming

## Makefile example

http://mrbook.org/blog/tutorials/make/

```bash
$ make -f Makefile-1
$ make -f Makefile-2
$ make -f Makefile-3
$ make -f Makefile-4
```

## Configure, make, make install examples

https://robots.thoughtbot.com/the-magic-behind-configure-make-make-install

1. Generate Configure and Makefile.in.

```bash
$ aclocal
$ autoconf
$ automake --add-missing
```

2. Distribute the program.

```bash
$ ./configure
$ make dist
``` 

To test the distribution,

```bash
$ make distcheck
```

3. Build the program main.c and install the binary helloworld.

```bash
$ ./configure
$ make
$ make install
```
