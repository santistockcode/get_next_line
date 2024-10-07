## TESTS 

la estática mantiene toda la info de un read y por h o por b sabrá al menos lo más básico de memoria (¿hay variables que liberar?)

la función read es gratis, gnl lee por bloques de BUFFER_SIZE y puede mandar todo el flujo del programa (excepto la memoria, vamos) pero es la herramienta más importante

la reserva de memoria manda y organiza todo el código, sé lo que hay en el heap y en el stack en todo momento y no las mezclo (recuerdo que M(R(S)))


NO PASA ESTE TEST: en el sentido en que el read y la memoria no están sincronizadas cuando voy por el flujo a la izquierda (bueno ni en el primer paso tampoco)
tips: meaningfull and efficient
(este test es más de lo que me pide el ejercicio, pero claro, yo soy un pijo)

## BRAINSTORMING

la lectura por bloques / read (una función que copia contenido de x en y hasta number bytes y devuelve los bytes leídos) está desacoplada de la estática, significando: 
   either la estática depends on read o bien read depends on la estática.
   se me ocurre: el read antes de actuar depende de lo que haya en la estática SUENA BASTANTE A INVERSIÓN DE DEPENDENCIAS => todo a utils

   se me ocurre una de estas dos
      1: la gestión de memoria antes de actuar depende bastante de lo que haya en el read
      2: la gestión de la estática antes de actuar depende bastante de cómo se maneje la memoria (malloc etc)

identifico 3 funcionalidades: la de manejo de memoria, capa del read, capa de static

CONCLUSIÓN: 
la estática le tiene que dar igual la string que está manejando del read, el read que sea que venga de donde quiera
al read le tiene que dar igual los punteros que esté manejando, el manejo de memoria que venga de donde sea que yo ya sé (si hay hueco, si hay cosas, si termina en 0, sé todo de ese puntero)
