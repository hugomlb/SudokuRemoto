# Sudoku Remoto - Trabajo para Taller de Programacion I (75.42)

Implementacion de un sistema cliente-servidor para jugar al Sudoku de manera remota. El programa se puede ejecutar en dos modos: 
- Cliente
- Servidor
El servidor acepta unicamente una conexion.

## Servidor

Para ejecutar el servidor, se debe iniciar el programa indicando el modo correspondiente e indicar en que puero debe escuchar las conexiones
```
./tp <modo> <puerto>
```
  
  Por ejemplo:
  
  ```
./tp server 7777
```
  
  ## Cliente
  
  El cliente se ejecuta de manera similar pero tambien se debera indicar el hostname del servidor
  
```
./tp <modo> <hostname-servidor> <puerto>
```
  
  Un ejemplo seria:
```
./tp client localhost 7777
```
 
 ## Codigos de Retorno
 
 En ambos modos, se retorna 0 ante una ejecucion exitosa y 1 ante cualquier error que impida la correcta ejecucion del programa.
 
 ## Uso de Entradas y Salidas Estandar
  El cliente no hace uso ni de la salida estandar ni de la entrada estandar. El cliente, al contrario, utiliza la entrada estandar para ingresar los comandos y en la salida estandar se imprimen las respuestas provenientes del servidor o los errores especificados en cada comando.
  
  ## Representacion del Tablero
 El servidor lee el tablero a partir de un archivo llamado "board.txt" ubicado en l acarpeta donde esta situada la consola en la que se ejecute. Dicho archivo contara de nueve lineas de numeros separados por espacios, donde cada numero positivo representara el calor de una celda prefijada y las celdas vacias deberan ser representadas con un 0. Por ejemplo:

```
3 0 5 0 0 8 0 1 0
0 0 7 0 0 0 5 0 8
1 2 0 7 5 0 0 9 0
0 0 9 0 7 0 0 0 4
0 0 4 3 0 5 9 0 0
7 0 0 0 9 0 8 0 0 
0 3 0 0 4 6 0 5 7
4 0 6 0 0 0 1 0 0
0 7 0 5 0 0 6 0 9
```

Con el tablero mostrado en el ejemplo, el cliente vera lo siguiente:

```
U===========U===========U===========U
U 3 |   | 5 U   |   | 8 U   | 1 | 0 U
U---+---+---U---+---+---U---+---+---U
U   |   | 7 U   |   |   U 5 |   | 8 U
U---+---+---U---+---+---U---+---+---U
U 1 | 2 |   U 7 | 5 |   U   | 9 |   U
U===========U===========U===========U
U   |   | 9 U   | 7 |   U   |   | 4 U
U---+---+---U---+---+---U---+---+---U
U   |   | 4 U 3 |   | 5 U 9 |   |   U
U---+---+---U---+---+---U---+---+---U
U 7 |   |   U   | 9 |   U 8 |   |   U 
U===========U===========U===========U
U   | 3 |   U   | 4 | 6 U   | 5 | 7 U
U---+---+---U---+---+---U---+---+---U
U 4 |   | 6 U   |   |   U 1 |   |   U
U---+---+---U---+---+---U---+---+---U
U   | 7 |   U 5 |   |   U 6 |   | 9 U
U===========U===========U===========U
```

## Comandos

### Put: 
Este comando sirve para ubicar un numero en una posicion del tablero. Desde el cliente se tiene que mandar por la entrada estandar un texto como el siguiente:

```
put <numero> in <fila>,<columna>
```
por ejemplo: 
```
put 4 in 9,9
```
Los indices de filas y columnas van del 1 al 9.
(agregar posibles salidas del comando) ......

### Verify: 
Este comando se utiliza para verificar si los valores actuales cumplen con todas las reglas. Desde el cliente se tiene que mandar por la entrada estandar un texto como el siguiente:
```
verify
```
Si se estan cumplento con todas las reglas se devuelve un "OK" caso contrario se devuelve un "ERROR"

### Reset: 
Este comando sirve para restablecer todas las celdas modificables, es decir, volver al comienzo del juego. Desde el cliente se tiene que mandar por la entrada estandar un texto como el siguiente:
```
reset
```
Se devuelve una representacion del tablero por salida estandar
### Get: 
Se utiliza para  obtener el tablero.  Desde el cliente se tiene que mandar por la entrada estandar un texto como el siguiente:
```
get
```




