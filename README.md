# Minishell :computer:

## Description
Minishell is a custom Unix shell implementation designed to mimic basic features of bash, providing a lightweight, yet powerful command line interface for interaction with the operating system. It supports command execution, pipelines, redirections, environment variable expansions, and several built-ins, with a focus on minimalism and efficiency.

## Objective
The primary goal of Minishell is to offer an educational insight into the workings of a Unix shell. It aims to challenge the understanding of system calls, process management, and the overall architecture of a shell environment.

## Features
- Display a prompt for new commands with a working history.
- Execute the correct executable using the PATH variable or through relative/absolute paths.
- Includes built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Support for input (`<`), output (`>`), append (`>>`), and heredoc (`<<`) redirections.
- Implement pipes (`|`) to connect command outputs to inputs.
- Handle environment variables and the `$?` special variable.
- Manage signals (`ctrl-C`, `ctrl-D`, `ctrl-\`) similar to bash.
- Limit the use of global variables, focusing on signal handling without accessing main data structures.

## Technical Details
- **External Functions Allowed**: A wide range of system and library functions, including `readline` for input handling and `execve` for command execution.
- **Authorized Library**: `libft` for general utilities.
- **Programming Language**: C

## Getting Started
1. **Prerequisites**: Ensure you have `gcc`, `make`, and `readline` library installed on your system.
2. **Installation**:
    ```shell
    git clone https://github.com/yourrepository/minishell.git
    cd minishell
    make
    ```

## Usage
Execute the shell by running:
```shell
./minishell
```

## Bonus Features
- Logical operators `&&` and `||` with parentheses for priority.
- Wildcard expansion `*` for the current working directory.

## Contributing
Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated. Refer to `CONTRIBUTING.md` for our contribution guidelines.

## License
Distributed under the MIT License. See `LICENSE` for more information.

## Acknowledgments
- Inspired by the concept of creating a learning tool for system programming enthusiasts, Minishell strives to replicate the fundamental features of a Unix shell in a simplified manner.

## Links / Further Information
- [GitHub Repository Link]
- [Documentation]
- [Code Examples]

## Contributors
- Gero Böhm (https://github.com/gero-boehm)
- Christian Meng (https://github.com/Christwelve)
