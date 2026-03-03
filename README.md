*This project has been created as part of the 42 curriculum by caide-so, marcudos.*

# Minishell
> *As beautiful as a shell*

---

## Description

Minishell is a simplified Unix shell implementation built as part of the 42 School curriculum. The goal is to recreate the core behavior of **bash**, gaining hands-on understanding of how shells work under the hood — from parsing user input to managing processes, file descriptors, and signals.

This project covers the entire pipeline of a shell:

- **Tokenization** — breaking raw input into meaningful tokens
- **Syntax analysis** — validating token structure before execution
- **AST (Abstract Syntax Tree) construction** — representing command logic as a tree
- **Expansion** — handling environment variables, `$?`, wildcards, and quote rules
- **Execution** — running builtins, external commands, pipes, redirections, and subshells
- **Signal handling** — responding correctly to `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`

---

## Features

### Mandatory

- Interactive prompt with command history
- Executable lookup via `PATH`, relative, and absolute paths
- Single and double quote handling
- Environment variable expansion (`$VAR`, `$?`)
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Pipes (`|`) connecting command outputs to inputs
- Signal handling: `Ctrl-C`, `Ctrl-D`, `Ctrl-\`
- Built-in commands:
  - `echo` (with `-n`)
  - `cd` (relative and absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

### Bonus

- Logical operators `&&` and `||` with parenthesis-based priority
- Wildcard `*` expansion in the current working directory

---

## Instructions

### Requirements

- GCC compiler
- GNU Make
- `readline` library (libreadline-dev on Debian/Ubuntu)

### Compilation

```bash
# Clone the repository
git clone  minishell
cd minishell

# Build the project
make

# Build with bonus features
make bonus
```

### Running

```bash
./minishell
```

### Cleanup

```bash
# Remove object files
make clean

# Remove object files and binary
make fclean

# Full recompile
make re
```

### Memory Check (optional)

A `readline.supp` valgrind suppression file is included to filter readline's known leaks:

```bash
make leak
```

---

## Project Structure

```
minishell/
├── include/
│   ├── minishell.h       # Main header with all function prototypes
│   ├── structs.h         # All struct and enum definitions
│   └── colors.h          # ANSI color macros for the prompt
├── src/
│   ├── main.c            # Entry point, prompt loop, parser
│   ├── tokenizer/        # Input → token list
│   ├── syntax/           # Token validation
│   ├── ast/              # Token list → AST
│   ├── expansion/        # Variable, wildcard, and quote expansion
│   ├── executor/         # AST execution, pipes, redirections
│   ├── builtin/          # Built-in command implementations
│   ├── heredoc/          # Heredoc input processing
│   ├── signal/           # Signal handler setup
│   ├── env/              # Environment variable management
│   ├── prompt/           # Prompt string construction
│   └── clean/            # Memory cleanup utilities
├── libft/                # Personal C utility library
└── Makefile
```

---

## Resources

### Official Documentation

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — the primary reference for expected behavior
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — documentation for `readline`, `add_history`, and related functions
- [POSIX Shell Specification](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — formal shell grammar and behavior

### Articles & Tutorials

- [Writing a Unix Shell (Part I, II, III) — Indradhanush Gupta](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/) — excellent walkthrough of shell internals
- [Building a Shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — concise practical guide
- [Abstract Syntax Trees — Wikipedia](https://en.wikipedia.org/wiki/Abstract_syntax_tree) — background on AST concepts
- [Linux `man` pages](https://man7.org/linux/man-pages/) — for all syscalls used: `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `sigaction`, etc.

### 42-Specific References

- [42 Norm](https://github.com/42School/norminette) — coding style enforced on all source files
- [Valgrind Documentation](https://valgrind.org/docs/manual/quick-start.html) — used for memory leak detection during development

---

## AI Usage

AI tools (primarily Claude) were used during this project in the following ways:

- **Debugging assistance** — describing unexpected behaviors and getting suggestions on where to investigate (e.g., signal handling edge cases, heredoc fd management)
- **Documentation drafting** — generating initial function comment blocks, which were then reviewed, corrected, and adapted to match actual implementation
- **Prompt refinement** — asking targeted questions about specific POSIX/bash behaviors (e.g., how `$?` expands inside heredocs, expected exit codes for signals)
- **README structure** — this file was drafted with AI assistance and reviewed to ensure accuracy

In all cases, AI-generated content was critically reviewed before use. No logic or implementation was copied from AI output without full understanding — all core algorithms (tokenizer, parser, AST, expander, executor) were written and reasoned through by the authors.

---

## Authors

- **caide-so** — [caide-so@student.42sp.org.br](mailto:caide-so@student.42sp.org.br)
- **marcudos** — [marcudos@student.42sp.org.br](mailto:marcudos@student.42sp.org.br)
