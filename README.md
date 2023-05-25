<div align="center">
  <img src="shell.png" alt="hsh - Simple Linux Shell">
</div>

# hsh - Simple Linux Shell

> Your command line companion

hsh is a simple yet powerful Linux shell written in C. It aims to replicate the behavior and error messages of the `/bin/sh` shell, providing a familiar and seamless experience for users.

## Features

- **Interactive Mode**: Execute commands directly within the shell and receive immediate feedback.
- **Non-Interactive Mode**: Run commands from files, allowing for automation and batch processing.
- **Error Handling**: Display clear and concise error messages, mirroring the `/bin/sh` shell for consistency.

## Getting Started

### Project Requirements

- Allowed editors: vi, vim, emacs.
- Compiled on Ubuntu 20.04 LTS using gcc with options -Wall -Werror -Wextra -pedantic -std=gnu89.
- All files end with a new line.
- Follow the Betty style for code formatting.
- No memory leaks in your shell.
- No more than 5 functions per file.
- All header files should be include guarded.
- Use system calls only when necessary.

### Prerequisites

- Linux environment
- GCC compiler

### Installation

1. Clone the repository: git clone https://github.com/adnan-jahbli/simple_shell.git
2. Compile the shell: gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
3. Run the shell in interactive mode: ./hsh
4. Run the shell in non-interactive mode with a command file: ./hsh < commands.txt

## Usage Examples

### Interactive Mode

```shell
$ ./hsh
hsh $ /bin/ls
hsh main.c shell.c
hsh $ exit
$
```

### Non-Interactive Mode

```shell
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
$
$ cat commands.txt
/bin/ls
/bin/pwd
$ ./hsh < commands.txt
hsh main.c shell.c
/home/user/project-directory
```

### Error messages

```shell
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
```

### Contributors

## Authors

- [Neville Soundy](https://github.com/Neville256)
- [Timothy Klose](https://github.com/MadoXZA)
