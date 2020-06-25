# ush
Zsh-like shell It's a command-line interpreter

## Content

- [Installation](#installation)
- [Description](#description)
- [Implemented functionality](#implemented-functionality)
- [Additional functionality](#additional-functionality)
- [Tested systems](#tested-systems)
- [License]($license)

## Description:
Implementation of basic command-line interpreter (based on ```zsh``` and ```bash```), using the C programming language.

## Installation:
>**1. git clone https://github.com/Hvvang/ush**  
>**2. make**  
>**3. ./ush**

### Rules of Makefile:
- `make` or `make all` compilation of binary executable
- `make install` do `make all` and `make clean` compilation of binary executable
- `make clean` delete all .o files
- `make uninstall` do `make clean` and delete all modules (\*.a) files created during installing and also executable file ./ush
- `make reinstall` do `make uninstall` and `make`

## Implemented functionality

### Builtins-table:

| Builtin |                       Description                      |
|:-------:|:------------------------------------------------------:|
| cd      | change the working directory                           |
| unset   | unset values and attributes of variables and functions |
| pwd     | return working directory name                          |
| export  | set the export attribute for variables                 |
| fg      | run jobs in the foreground                             |
| jobs    | print all existing suspended foreground processes      |
| history | print commands that was previously used                |
| which   | locate a command and display its pathname or alias     |
| echo    | write arguments to standard output                     |
| env     | set the environment for command invocation             |
| true    | set value of exit status equal 0                       |
| false   | set value of exit status equal 1                       |
| bye     | same as exit                                           |
| color   | change foreground and background color.                |
| exit    | cause the shell to exit                                |

### Characters escaping
Next characters can be escaped to be used literally: `space`, `'`, `"`, `$`, `(`, `)`, `\`, ``` ` ```, `{`, `}`.

### Tilde expansions
Tilde expansions ~ with the following tilde-prefixes:
  - `~`;
  - `~/dir_name`;
  - `~username/dir_name`;
  - `~+/dir_name`;
  - `~-/dir_name`.

### Parameter expansions
  - only basic form - `${parameter}` or `$parameter`

### Command substitutions of next forms
  - `command`
  - `$(command)`
Nested command substitutions also supported.

## Additional functionality

  - job control system (only for foreground jobs and processes);
  - command history using `Arrow keys` or `Pg Up/Pg Dn`;
  - command editing, cursor motion using `Arrow keys`;
  - prompt changing using `§` key;
  - the `;` command line separator;
  - errors management;
  - user environment management.

## Tested systems:
  - MacOS
  - Ubuntu

## License
Collision is an open-sourced software licensed under the [MIT license](LICENSE).
