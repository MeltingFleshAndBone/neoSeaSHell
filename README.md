# SeaSHell

**SeaSHell** is a basic shell program written in C. It implements core shell functionality and is still under development, with plans for additional features and improvements over time.

---

## Prerequisites

Before building SeaSHell, ensure that you have [CMake](https://cmake.org/) installed. Use the following commands to install CMake on your system:

#### Arch Linux

```shell
sudo pacman -S cmake
```

#### Debian-based (Ubuntu, etc.)

```shell
sudo apt install cmake
```

---

## Building SeaSHell

To build SeaSHell from source, follow these steps:

```shell
# Clone the repository
git clone https://github.com/EletricSheeple/SeaSHell.git

# Change into the repository directory
cd SeaSHell

# Create the build directory
mkdir build

# Change into the build directory
cd build

# Generate the Makefile with CMake
cmake ../

# Compile the shell
make
```

After a successful build, the compiled binary will be located in the `build/bin/` directory. To run the shell, simply execute:

```shell
./build/bin/SeaSHell
```

---

## Development Roadmap

Below is the current list of priorities for ongoing development:

1. **Tokenization and Parsing**: Implement functions to handle tokenization, aliasing, and basic parsing of user commands. (Partial Implementation)
2. **Process Management**: Develop functionality to execute system processes and manage child processes. (Partial Implementation)
3. **Built-in Commands**: Add essential shell commands such as `cd`, `pwd`, and others. (Partial Implementation)
4. **Basic Prompt**: A basic shell prompt string will be implemented. (Partial Implementation)
5. **Error Handling**: Create a custom error-handling system to replace the default `perror` function and improve error reporting.
6. **Command History**: Implement a mechanism for tracking and recalling previously executed commands. (Partial Implementation)
7. **Configuration Support**: Add the ability to read and apply configuration settings from a configuration file.
8. **I/O Redirection and Piping**: Implement support for I/O redirection (stdin, stdout) and piping between commands.
9. **Job Control**: Introduce job control features such as `fg`, `bg`, and `jobs` for managing background and foreground processes.
10. **Tab Completion**: Research and implement simple tab completion to enhance the user experience.
11. **Customizable Prompt**: Enable users to configure their shell prompt string for a personalized experience.
