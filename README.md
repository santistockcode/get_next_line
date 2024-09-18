# get_next_line

## Conceptos fundamentales



### ¿distingue open al abrir un binario o un texto? 

### read interpreta \0 como un EOF o son cosas diferentes

### ¿Qué hace read? 
Devuelve un size_t y necesita que se le pase un fd, un void que es el buffer y un size_t nbyte que es el numero de bits que referenciar del objeto del filedescirtor al buffer. Entonces conceptos: fd que apunta a un objeto, buffer en el que mover los bytes, y nbytes el numero de bytes que mover…  y devuelve: el numero de bites que ha podido mover, si ya ha llegado al final del fichero devuelve 0, si ha habido un problema devuelve -1

### Variables estáticas
https://www.geeksforgeeks.org/static-variables-in-c/

si no tienen valor una variable estática se inicia a 0.

Y necesito este background: https://www.geeksforgeeks.org/memory-layout-of-c-program/

Cuando ponemos static en una función por ejemplo static char *read_from_file(fd): 
The static keyword is about controlling access and visibility. It’s useful for keeping functions private to a file, preventing naming collisions in larger programs. However, since your current use case is entirely within the same file, the behavior of the two versions is identical.

## LLDB

To set up LLDB for debugging your C project in a Linux environment while using Visual Studio Code (VS Code), here’s a detailed guide:

### Step 1: Install LLDB

1. **Open a terminal** and install LLDB by running:
   ```bash
   sudo apt-get update
   sudo apt-get install lldb
   ```
   - Verify the installation by running:
   ```bash
   lldb --version
   ```

### Step 2: Install the Necessary VS Code Extensions

To make debugging easier with LLDB in VS Code, you’ll need a couple of extensions:
1. Open **Visual Studio Code**.
2. Install the following extensions:
   - **C/C++** (by Microsoft) – for IntelliSense, code navigation, and debugging.
   - **CodeLLDB** (by Vadim Chugunov) – for LLDB integration.

### Step 3: Create a `launch.json` File for Debugging

Now you need to set up a configuration file in VS Code so you can run the debugger.

1. Open your C project folder in VS Code.
2. Press **Ctrl+Shift+P**, then type `Debug: Open launch.json` and select **C++ (GDB/LLDB)**.
3. This will generate a `launch.json` file in the `.vscode` directory.

Modify the `launch.json` to fit your project. Below is an example configuration tailored to your "get_next_line" project:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "(lldb) Launch",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/get_next_line",  // Path to your executable
      "args": [],  // You can add any command-line arguments here
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "lldb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "build",
      "miDebuggerPath": "/usr/bin/lldb",  // Path to the lldb binary
      "logging": {
        "trace": true,
        "traceResponse": true,
        "engineLogging": true
      },
      "launchCompleteCommand": "exec-run",
      "targetArchitecture": "x86_64"
    }
  ]
}
```

### Step 4: Set Up the Build Task

Now, you’ll need to set up a build task so that VS Code knows how to compile your project when debugging.

1. Press **Ctrl+Shift+P** again, and type `Tasks: Configure Task`.
2. Choose **Create tasks.json from template** and select **Others**.
3. Modify the `tasks.json` to look something like this:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build",
      "type": "shell",
      "command": "gcc",
      "args": [
        "-g",                      // Add debugging symbols
        "main.c",
        "get_next_line.c",
        "get_next_line_utils.c",
        "-o",
        "get_next_line"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

This `tasks.json` tells VS Code to run `gcc` to compile your project with debugging symbols (`-g` flag).

### Step 5: Run and Debug

1. **Build the project**: You can either use the VS Code terminal to manually compile, or run the task you set up with **Ctrl+Shift+B** to build using the `tasks.json` configuration.
2. **Debug**: Press **F5** to start debugging. LLDB will launch and you can use breakpoints, step through the code, and inspect variables.

### Step 6: Debugging in Terminal

If you prefer debugging directly from the terminal using LLDB, follow these steps:

1. **Compile your project** with debugging symbols:
   ```bash
   gcc -g main.c get_next_line.c get_next_line_utils.c -o get_next_line
   ```

2. **Start LLDB**:
   ```bash
   lldb ./get_next_line
   ```

3. **Set breakpoints** and run the program:
   ```bash
   (lldb) breakpoint set --name main
   (lldb) run
   ```

You can now use LLDB commands like `step`, `next`, `print`, and `continue` to debug your code.

Let me know if you need any further clarification or assistance with the setup!

I'm glad you're enjoying using LLDB in the terminal! Here’s how you can set breakpoints in specific methods and print variable values during debugging:

### 1. **Setting Breakpoints in Specific Functions (e.g., `read_from_file` in `get_next_line.c`)**

To set a breakpoint at a specific function, use the following command while in the LLDB prompt:

```bash
breakpoint set --name read_from_file
```

This sets a breakpoint at the `read_from_file` function, regardless of where it’s defined.

Alternatively, if you want to specify the file as well, you can do:

```bash
breakpoint set --file get_next_line.c --name read_from_file
```

This is particularly useful if the function name is ambiguous (e.g., if there are multiple functions with the same name in different files).

### 2. **Setting Breakpoints at Specific Lines**

If you prefer to set a breakpoint at a specific line in a file, use this command:

```bash
breakpoint set --file get_next_line.c --line 42
```

This sets a breakpoint at line 42 in `get_next_line.c`.

### 3. **Printing Variable Values**

Once you hit a breakpoint and the program is paused, you can inspect variable values using the `print` command.

- **To print a variable's value**, use:
   ```bash
   print variable_name
   ```

   Example:
   ```bash
   (lldb) print buffer
   ```

   This will display the current value of the `buffer` variable.

- **For pointers or complex structures**, you might want to use `*` to dereference pointers:
   ```bash
   print *pointer_variable
   ```

- If you want to **see more detailed information** about a variable, use the `frame variable` command:
   ```bash
   frame variable
   ```
   This command lists all local variables in the current frame.

### 4. **Evaluating Expressions**

You can also evaluate expressions or call functions during a breakpoint:

```bash
print variable_name + 10
```

This can be handy for checking how variables are manipulated or doing quick calculations.

### Summary of Commands:
- Set breakpoint at a function:
   ```bash
   breakpoint set --name function_name
   ```
- Set breakpoint at a specific file and line:
   ```bash
   breakpoint set --file filename --line line_number
   ```
- Print a variable’s value:
   ```bash
   print variable_name
   ```
- Print a dereferenced pointer:
   ```bash
   print *pointer_variable
   ```

Let me know if you need more help with debugging!