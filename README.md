# muShell - A Minimalist Unix Shell Implementation

A lightweight, Unix-like shell implementation written in C.

> **Development Status**: This project is currently under active development and is not yet functional. The shell foundation is in place, but core features like command execution, parsing, and built-in commands are still being implemented.

## About

muShell is an educational project created to get me get back into developing in C and to help understand operating system internals. The goal is to create a clean, minimalist shell implementation that supports essential Unix shell features.

## Planned Features

### Core Functionality
- **Command Execution**: Execute system programs and built-in commands
- **Argument Parsing**: Handle command-line arguments and parameter parsing  
- **Path Resolution**: Support for both absolute and relative paths
- **Environment Variables**: Environment variable expansion

### Built-in Commands
- `cd` - Change directory with support for relative/absolute paths
- `pwd` - Print working directory
- `exit` - Graceful shell termination
- `help` - Display available commands and usage
- `history` - Show command history
- `export` - Set environment variables

### Advanced Features
- **I/O Redirection**: Support for `>`, `>>`, and `<` operators
- **Pipes**: Chain commands with `|` operator  
- **Background Processes**: Execute commands in background with `&`
- **Signal Handling**: Proper handling of Ctrl+C, Ctrl+Z, and other signals
- **Command History**: Navigate through previous commands with arrow keys
- **Tab Completion**: Basic filename and command completion

## Architecture

The shell is built with a modular architecture:

- **Lexer**: Tokenizes user input into commands, arguments, and operators
- **Parser**: Builds command structures and handles operator precedence
- **Executor**: Executes commands with proper process management
- **Built-ins**: Implements shell built-in commands
- **Signal Handler**: Manages process signals and interrupts
