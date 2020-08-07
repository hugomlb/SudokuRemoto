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
 El servidor lee el tablero a partir de un archivo llamado "board.txt" ubicado en l acarpeta donde esta situada la consola en la que se ejecute. Dicho archivo contara de nueve lineas de numeros separados por espacios