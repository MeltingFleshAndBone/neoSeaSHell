# SeaSHell

**SeaSHell** is a basic shell program written in C.

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
https://github.com/MeltingFleshAndBone/SeaSHell

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

While it's not recommended, you can make it the default shell with
```shell
# Change into the build binary directory
cd SeaSHell/build/bin

# Moving the binary into usr/bin/ (optional)
sudo mv SeaSHell /usr/bin

# Setting it as the default shell
sudo chsh $USER
# Then type the path for the shell binary (e.g. /usr/bin/SeaSHell)
```
