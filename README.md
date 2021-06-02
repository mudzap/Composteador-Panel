# Panel de control del compostador de la DICyT

## Arquitectura

Las tareas se manejaran a través de FreeRTOS, estas de dividiran de la siguiente forma:

- Comunicación con modulos de sensores a través de CAN.
- Comunicación externa por USB.
- Interfaz y controles.
- Almacenamiento en la memoria flash (para calibración).
- Control y procesamiento de datos.

Los datos de los sensores se almacenaran en 4 floats, siendo el tamaño de los datos enviados por el bus CAN de 32 bytes.
Gran parte de los parametros importantes se definiran a través de defines en el compilador.

## Integrantes

- Iván Peña (mudzap)
- ...

