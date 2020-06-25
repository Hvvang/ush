# ush
Zsh-like shell It's a command-line interpreter

### Installation:
>**1. git clone https://github.com/Hvvang/ush**  
>**2. make**  
>**3. ./ush**

### Description:
**Implementation of unix shell that is student's project of uCode ITAcademy**

### Rules of Makefile
- `make` or `make all` compilation of binary executable
- `make install` do `make all` and `make clean` compilation of binary executable
- `make clean` delete all .o files
- `make uninstall` do `make clean` and delete all modules (\*.a) files created during instaling and also executeble file ./ush
- `make reinstall` do `make uninstall` and `make`


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

### Tested systems:
  - MacOS
  - Ubuntu

