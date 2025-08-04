# libasm (School 42)

## Description

`libasm` is a School 42 project focused on implementing standard C library functions in x86_64 assembly (NASM, Intel syntax) and building them into a static library. The project develops low-level programming skills, understanding of memory management, calling conventions, and C/assembly interoperability.

## Project Goals

- Implement standard C functions in assembly (`strlen`, `strcpy`, `strcmp`, `write`, `read`, `strdup`)
- Implement bonus list functions (`atoi_base`, `list_push_front`, `list_size`, `list_sort`, `list_remove_if`)
- Build the `libasm.a` static library
- Provide comprehensive C tests for each function

## Project Structure

```
assembly-kick-off/
├── inc/                # Header files (libasm.h, libasm_bonus.h)
├── src/                # Core assembly functions
│   ├── ft_strlen.s
│   ├── ft_strcpy.s
│   ├── ft_strcmp.s
│   ├── ft_write.s
│   ├── ft_read.s
│   └── ft_strdup.s
│   └── bonus/          # Bonus assembly functions
│       ├── ft_atoi_base.s
│       ├── ft_list_push_front.s
│       ├── ft_list_size.s
│       ├── ft_list_sort.s
│       └── ft_list_remove_if.s
├── main.c              # C tests for core functions
├── main_bonus.c        # C tests for bonus functions
├── Makefile            # Build system for library and tests
└── README.md           # Project documentation
```

## Build Instructions

Requirements:

- NASM (assembler)
- GCC (C compiler)

Install NASM (if not already installed):

```sh
sudo apt update && sudo apt install nasm
```

Build the core library:

```sh
make
```

Build bonus functions:

```sh
make bonus
```

Clean all build artifacts:

```sh
make fclean
```

## Running Tests

### Core Functions

- **strlen**
  ```sh
  make test_strlen
  ./test_strlen
  ```
- **strcpy**
  ```sh
  make test_strcpy
  ./test_strcpy
  ```
- **strcmp**
  ```sh
  make test_strcmp
  ./test_strcmp
  ```
- **write**
  ```sh
  make test_write
  ./test_write
  ```
- **read**
  ```sh
  make test_read
  ./test_read
  ```
- **strdup**
  ```sh
  make test_strdup
  ./test_strdup
  ```

### Bonus Functions

- **ft_atoi_base**
  ```sh
  make test_atoi_base
  ./test_atoi_base
  ```
- **ft_list_push_front**
  ```sh
  make test_list_push_front
  ./test_list_push_front
  ```
- **ft_list_size**
  ```sh
  make test_list_size
  ./test_list_size
  ```
- **ft_list_sort**
  ```sh
  make test_list_sort
  ./test_list_sort
  ```
- **ft_list_remove_if**
  ```sh
  make test_list_remove_if
  ./test_list_remove_if
  ```

## Usage

1. Build the library:
   ```sh
   make
   ```
2. Include the header file `inc/libasm.h` or `inc/libasm_bonus.h` in your C project.
3. Link with `libasm.a`:
   ```sh
   gcc your_program.c -L. -lasm -o your_program
   ```
4. Use the implemented functions as regular C functions.

## Authors & License

This project is part of the [Ecole 42](https://42.fr/) curriculum.

---

**Happy low-level coding!**

## Useful x86-64 Assembly References

- [x86_64 NASM Assembly Quick Reference (Cheat Sheet)](https://www.cs.uaf.edu/2017/fall/cs301/reference/x86_64.html) — register table, instructions, calling conventions, memory, syntax
- [x64 Cheat Sheet (PDF)](https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf) — registers, instructions, operands, stack, function calls
- [x64 NASM Cheat Sheet (GitHub Gist)](https://gist.github.com/justinian/385c70347db8aca7ba93e87db90fc9a6) — concise NASM cheat sheet
- [x86 Instruction Reference by Felix Cloutier](https://www.felixcloutier.com/x86/) — full x86/x86-64 instruction reference
