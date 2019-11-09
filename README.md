# Consolidated-Firmware
A consolidated repository for gathering all firmware under one roof.

## Table of Content
- [Project Setup](#project-setup)
  - [Environment Dependencies](#environment-dependencies)
    - [Python Package Dependencies](#python-package-dependencies)
  - [CLion](#clion)
      - [Configure arm-none-eabi-gdb (For Windows Only)](#configure-arm-none-eabi-gdb-for-windows-only)
      - [Configure J-Link GDB Server (For Windows Only)](#configure-j-link-gdb-server-for-windows-only)
- [Continuous Integration (CI)](#continuous-integration-ci)
    - [CommentPragmas](#commentpragmas)
- [Conventions](#conventions)
  - [Github Conventions](#github-conventions)
  - [Pull Requests Conventions](#pull-requests-conventions)
  - [Coding Conventions](#coding-conventions)
- [CAN Bus](#can-bus)
  - [Ubuntu 18.04](#ubuntu-1804)
- [Periodic Task Scheduling](#periodic-task-scheduling)
- [CMakeLists](#cmakelists)

## Project Setup

### Environment Dependencies
Follow these steps so you can compile the code in **CLion**:
1. **Install Dependencies**: There are several dependencies required in order to mimic what CI is doing.
  * GNU Make: http://gnuwin32.sourceforge.net/packages/make.htm
  * CMake: https://cmake.org/install/
  * Python 3+ (*Python < 3 will NOT work*): https://www.python.org/downloads/
  * ARM GNU Embedded Toolchain: https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads (Check `install_gcc_arm_none_eabi.sh` for which version to download)
  * J-Link Software and Documentation Pack: https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack
  * OpenOCD
    * Ubuntu 18.04: `sudo apt-get install openocd`
  * STM32CubeMX: https://www.st.com/en/development-tools/stm32cubemx.html
  * MinGW (**for Windows only**): https://sourceforge.net/projects/mingw-w64/ (**select 32-bit verison/i686 architecture**)
2. **Modify your `PATH` Environment Variable**: Make sure to add the binary executables to `PATH`.

For Ubuntu 18.04, modify the `PATH` variable using the syntax below
```
export PATH="$PATH:/path/to/arm-none-eabi-gcc"
export PATH="$PATH:/path/to/STM32CubeMX"
...
```

For Windows, find `Environment Variables` in your start menu and then add the appropriate paths to `PATH`:
```
C:\Program Files (x86)\GNU Tools Arm Embedded\<VERSION>\bin
C:\Program Files (x86)\GnuWin32\bin
C:\Program FIles (x86)\...\path\to\STM32CubeMX
...
```

(*These paths should include wherever the `cmake`, `make`, `arm-none-eabi-gcc`, and STM32CubeMX binaries have been installed.*)

#### Python Package Dependencies
We use python both for CI (see below), and to generate C code from the `.dbc` defining messages passed over CAN. Python dependencies are managed via [pipenv](https://pipenv.readthedocs.io/en/latest/). To install all required dependencies in a [python virtual environment](https://realpython.com/python-virtual-environments-a-primer/), navigate to the root of this repository and run `pipenv install`.

### CLion
We edit, compile, and debug our code using [CLion](https://www.jetbrains.com/clion/). Students can obtain a CLion educational license [here](https://www.jetbrains.com/shop/eform/students). To open an existing project, open any one of the board-specific folders under `boards/` (e.g. `boards/DCM`) in **CLion**.

In each project, there will be two configurations to use: `<board>_SeggerGDB.elf` and `OCD <board>`. Either one can be used for flashing and debugging, but the `<board>_SeggerGDB.elf` has unlimited flash breakpoints among some other extra functionalities. Use `<board>_SeggerGDB.elf` whenever possible.

##### Configure arm-none-eabi-gdb (For Windows Only)
Under **File->Settings->Build, Execution, Deployment...->Toolchains**:
Set the default toolchain to be MinGW and provide the file path to the 32-bit version of MinGW, ie:
```
C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32
```
Next, set the debugger to be ARM GDB, ie:
```
C:\Program Files (x86)\GNU Tools ARM Embedded\8 2019-q3-update\bin\arm-none-eabi-gdb.exe
```

##### Configure J-Link GDB Server (For Windows Only)
For each project under **Run->Edit Configurations->Embedded GDB Server**, select `<board_name>_SeggerGDB`:
Then set the GDB Server to be JLinkGDBServer, ie:
```
C:\Program Files (x86)\SEGGER\JLink\JLinkGDBServer.exe
```
## Continuous Integration (CI)
We run (and require) continuous integration on every pull request before it is merged. This automatically makes sure the code builds, and checks for formatting errors.

1. **Build Check**: If the code compiles in CLion, it should also compile in CI.
2. **Formatting Check**: Run the following commands (starting from the **root directory** of this project) to fix formatting (CI runs this and then checks if any code was modified):
  * *Windows and Ubuntu 18.04:*
  ```
  python clang_format/fix_formatting.py
  ```

#### CommentPragmas
In `.clang-format`, the line `CommentPragmas: '\/\*(\*(?!\/_|[^*])*\*\/'` is ineffective because it's being preempted by `ReflowComments`. We are hoping that the next version of `clang-format` will resolve this.

## Conventions

### Github Conventions
- We follow the Forking Workflow:
    - [what it is](https://www.atlassian.com/git/tutorials/comparing-workflows#forking-workflow)
    - [how to use it](https://gist.github.com/Chaser324/ce0505fbed06b947d962)
- Only commit files that are essential for the system to run; do not put any photos or videos in here.
- Once your pull request has been reviewed and revised until it looks good from both your and the reviewers' sides, go ahead and Squash and Merge it, which will squash all the commits on your pull request into one and merge it to the target branch.

### Pull Requests Conventions
- Before opening a pull request, quickly run through the [pull request checklist](.github/pull_request_template.md) and make sure you've satisfied everything.
- Once your pull request has been approved, please proceed to merge and close the pull request yourself.
- When your pull requests receive comments, please reply to each comment individually.
- If there were any fixes that were specific to resources you found (eg. stackoverflow thread), please comment them into the PR for future reference.
- On a similar note, if you made design decisions, please document them in the comments of the PR. We often go back to close PRs to look at why things were done a certain way. It is very helpful for us to know how you came up with your solution when reading through the PR.

### Coding Conventions
- Every and **.h** file should start with
```
/**
 * @brief A quick description of what this file does/is for
 */
```

- Functions comments (below) should be directly above every function in the **header** file:
```
/**
 * @brief A quick descrption
 * @param param_one The first parameter of the function
 * @param param_two The second parameter of the function whose
 *                  description goes longer than one line
 * @return what the function returns if it returns anything
 */
```

- Variables are **non_camel_case**
- Constants are **ALL_CAPS_WITH_UNDERSCORES**
- Structs, Enums, Unions are **PascalCase**
- Filenames are **PascalCase** and follow the format **{AbstractionPrefix}_{Name}**
  - **{AbstractionPrefix}** may be **App** for application code or **Io** for hardware-specific code
  - **{Name}** is a descriptive name
  - An example would be **Io_Can.h**, which describes CAN hardware drivers
- Functions are **PascalCase** and follow the the format **{HeaderName}_{FunctionName}**
  - An example would be **struct CanMaskFilterConfig Io_Can_GetCanMaskFilters(void)**
- Static Functions are **PascalCase** and don't require a **{HeaderName}** prefix

- Indentations are 4 spaces

- Do **not** typedef structs and enums unless you have a good reason to make an opaque type

## CAN Bus
Our microcontrollers use CAN bus to pass messages between each other. It is useful to set up your host machine to view the messages on CAN bus.
### Ubuntu 18.04
1. Connect a PCAN dongle between your host machine and the microcontroller. The required `socketcan` driver comes with the Ubuntu 18.04 LTS distribution so there is no driver to install.
2. Bring up the CAN interface with the baudrate set to 500kHz.
```
sudo ip link set can0 type can bitrate 500000
sudo ip link set up can0
```
3. Verify that `can0` shows up in `ifconfig`.
4. Use `candump` and `cantools` to sniff the packets with DBC decoding.
- Display CAN messages on `stdout` with DBC decoding and delta-time as timestamps:
```
candump can0 -c -t d | cantools decode --single-line boards/shared/CanMsgs/CanMsgs.dbc
```
- Monitor CAN traffic in a text-based user interface:
```
cantools monitor boards/shared/CAN/CanMsgs.dbc -b socketcan -c can0 -B 500000
```
## Periodic Task Scheduling
We follow rate-monotonic scheduling to assign priorities to periodic tasks. This priority-assignment algorithm rules that every periodic task must have higher priority than other periodic tasks with longer cycle duration than itself. For example, if we have a 1Hz task and a 10Hz task, the 10Hz task must have a higher priority than the 1Hz task. The exact priority value isn't important, as long as the relative priorities follow rate-monotonic scheduling.

It is conventional for the frequency of periodic tasks in embedded systems to be a power of 10. For us, we should only ever need to use 1Hz, 10Hz, 100Hz, and 1kHz. Here's a table you can follow to assign priority values for periodic tasks in CMSIS-RTOS:

| Frequency     | Priority              |
| ------------- | --------------------- |
| 1Hz           | osPriorityLow         |
| 10Hz          | osPriorityBelowNormal |
| 100Hz         | osPriorityNormal      |
| 1000Hz        | osPriorityAboveNormal |

## CMakeLists
- Each board project (e.g. PDM, FSM) shall have its `CMakeLists.txt` and linker directives generated by a **STM32CubeMX** project in **CLion**. Here is a guide: https://blog.jetbrains.com/clion/2019/02/clion-2019-1-eap-clion-for-embedded-development-part-iii/.
- If applicable, compile a static library (e.g. `.a` file) and place the code and `CMakeLists.txt` under `lib/`. The developer is responsible for writing their own `CMakeLists.txt` for the static library.
