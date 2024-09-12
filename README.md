# get_next_line

## Conceptos fundamentales

### ¿Qué hace read? 
Devuelve un size_t y necesita que se le pase un fd, un void que es el buffer y un size_t nbyte que es el numero de bits que referenciar del objeto del filedescirtor al buffer. Entonces conceptos: fd que apunta a un objeto, buffer en el que mover los bytes, y nbytes el numero de bytes que mover…  y devuelve: el numero de bites que ha podido mover, si ya ha llegado al final del fichero devuelve 0, si ha habido un problema devuelve -1

### Variables estáticas
https://www.geeksforgeeks.org/static-variables-in-c/

si no tienen valor una variable estática se inicia a 0.

Cuando ponemos static en una función por ejemplo static char *read_from_file(fd): 
The static keyword is about controlling access and visibility. It’s useful for keeping functions private to a file, preventing naming collisions in larger programs. However, since your current use case is entirely within the same file, the behavior of the two versions is identical.

## LLDB

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