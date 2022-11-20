# DBus Server Calculator (Udacity C++ Capstone project)

[[_TOC_]]
## Description

This project implements a simple calculator with four opearations, addition, subtraction, multiplication and division.

The main point of the project isn't the calculator's opeartions but instead the demonstration of how to implement a basic DBus server project from scratch in modern C++.

To know more about DBus and its importance to the Linux world please take a look at https://www.freedesktop.org/wiki/Software/dbus/.

This project has all the basic utilities and dependencies that is needed to start a new daemon:

- D-Bus support by means of [sdbus-cpp](https://github.com/Kistler-Group/sdbus-cpp). Support for generation based on XML already integrated.
- Log support by means of [spdlog](https://github.com/gabime/spdlog). It has the same log levels and behavior of our internal `libglog`.

### Build
---

In order to make the build process indepented of the host machine where the build happens, `Docker` is used together with `meson`.

I decided to chose `meson` instead of `CMAKE` just to learn a new build system.

Steps to build:
 - Install `docker`. Simple tutorial here: https://docs.docker.com/engine/install/ubuntu/.
 -  On the terminal run :
```sh
./docker-runner.sh "./build.sh"
```
That is all, project is ready to be exectuded.

### Run

Here again to make sure project will just run in any OS or distribution we will make use of Docker to run the
application as an isolated docker container.

To see the help menu run:

```sh
./docker-runner.sh "./run.sh -h"
```

To run the application and start the dbus server run:

```sh
./docker-runner.sh "./run.sh -d"
```

### Testing `DBus Server Calculator` with `dbus-send` tool.
---

In order to test and call our DBus Server Calculator the easiest way is to use `dbus-send` which is a D-Bus client application.

By  default it is installed in all Linux distribution. If it is not installed in your distribution please install it.

Testing the **Addition** operation:

```sh
DBUS_SESSION_BUS_ADDRESS=tcp:host=localhost,port=43210  dbus-send --session --print-reply --type='method_call' --dest=com.cppnd.calculator  /com/cppnd/calculator com.cppnd.calculator.Add array:double:1,2,3,4
```

It computes (1 + 2 + 3 + 4) and returns 10.0.

Testing the **Subtraction** operation:

```sh
DBUS_SESSION_BUS_ADDRESS=tcp:host=localhost,port=43210  dbus-send --session --print-reply --type='method_call' --dest=com.cppnd.calculator  /com/cppnd/calculator com.cppnd.calculator.Sub double:2 double:10
```

It computes (2 - 10) and returns -8.

Testing the **Multiplication** operation:

```sh
DBUS_SESSION_BUS_ADDRESS=tcp:host=localhost,port=43210  dbus-send --session --print-reply --type='method_call' --dest=com.cppnd.calculator  /com/cppnd/calculator com.cppnd.calculator.Add array:double:1,2,3,4
```

It computes (1 x 2 x 3 x 4) and returns 24.

Testing the **Division** operation:

```sh
DBUS_SESSION_BUS_ADDRESS=tcp:host=localhost,port=43210  dbus-send --session --print-reply --type='method_call' --dest=com.cppnd.calculator  /com/cppnd/calculator com.cppnd.calculator.Div double:2 double:10
```

It computes (2 / 10 ) and returns 0.2.

> Note that for whenever each opeartion is called the Server logs some date to the STDOUT.

### Project Rubrics

1. [x] README : this file
2. [x] Compiling and Testing : Docker + Meson and build system.
3. [x] Loops, Functions, I/O:
    - [x] The project demonstrates an understanding of C++ functions and control structures : This is present in **ll classes** and isolated in [dbus_server.cpp](./src/dbus_server.cpp).
    - [x] The project reads data from a file and process the data, or the program writes data to a file: project logs to `stdout` and `Syslog` in all place where `spdlog::` is called. Example lines 29, 35, 49, 55 of [Calculator.cpp](./src/dbus/interfaces/Calculator.cpp)
    - [x] The project accepts user input and processes the input: see line 35 of [dbus_server.cpp](./src/dbus_server.cpp) for the option available.
4. [x] Object Oriented Programming
   - [x] The project uses Object Oriented Programming techniques. See files  [Calculator.cpp](./src/dbus/interfaces/Calculator.cpp) and [Calculator.hpp](./include/dbus/interfaces/Calculator.hpp)
   - [x] Classes use appropriate access specifiers for class members. See lines 13, 17 and 23 in file [Calculator.hpp](./include/dbus/interfaces/Calculator.hpp).
   - [x] Class constructors utilize member initialization lists. See line 8 in [Calculator.cpp](./src/dbus/interfaces/Calculator.cpp)
   - [x] Classes abstract implementation details from their interfaces. See files [Calculator.cpp](./src/dbus/interfaces/Calculator.cpp) and [Server.cpp](./src/dbus/Server.cpp)
   - [x] Classes encapsulate behavior. See files [Calculator.cpp](./src/dbus/interfaces/Calculator.cpp) and [Server.cpp](./src/dbus/Server.cpp)
   - [x] Classes follow an appropriate inheritance hierarchy. See abstract class [IComCppndCalculator.hpp](./introspection/IComCppndCalculator.hpp)
   - [ ] Overloaded functions allow the same function to operate on different parameters.
   - [x] Derived class functions override virtual base class functions. See lines 20, 33, 39, 53 in [Calculator.cpp](./src/dbus/interfaces/Calculator.cpp) and lines 18-21 in [Calculator.hpp](./include/dbus/interfaces/Calculator.hpp)
   - [ ] Templates generalize functions in the project.
5. [x] Memory Management
   - [x] The project makes use of references in function declarations: yes, see classes in almost all function of classes [Calculator.hpp](./include/dbus/interfaces/Calculator.hpp), [App.hpp](./include/util/App.hpp) and [Server.hpp](./include/dbus/Server.hpp).
   - [x] The project uses destructors appropriately. See line 15 in [Calculator.cpp](./src/dbus/interfaces/Calculator.cpp).
   - [x] The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. All classes are implement with that with RAII in mind.
   - [x] The project follows the Rule of 5: Default behavior is ok, so no definition needed.
   - [x] The project uses smart pointers instead of raw pointers. See lines 24-26 in [Server.hpp](./include/dbus/Server.hpp).
6. [x] Concurrency
   - [ ] The project uses multithreading.
   - [x] A promise and future is used in the project. See line 38 in [Calculator.cpp](./src/dbus/interfaces/Calculator.cpp).
   - [ ] A mutex or lock is used in the project.
   - [ ] A condition variable is used in the project.
