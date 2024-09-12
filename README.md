# get_next_line

## Conceptos fundamentales

### ¿Qué hace read? 
Devuelve un size_t y necesita que se le pase un fd, un void que es el buffer y un size_t nbyte que es el numero de bits que referenciar del objeto del filedescirtor al buffer. Entonces conceptos: fd que apunta a un objeto, buffer en el que mover los bytes, y nbytes el numero de bytes que mover…  y devuelve: el numero de bites que ha podido mover, si ya ha llegado al final del fichero devuelve 0, si ha habido un problema devuelve -1

### Variables estáticas
https://www.geeksforgeeks.org/static-variables-in-c/

si no tienen valor una variable estática se inicia a 0.

Cuando ponemos static en una función por ejemplo static char *read_from_file(fd): 
The static keyword is about controlling access and visibility. It’s useful for keeping functions private to a file, preventing naming collisions in larger programs. However, since your current use case is entirely within the same file, the behavior of the two versions is identical.