# 🌲 Network Scanner en C++ (BST & Non-Blocking Sockets)

Este proyecto nació por curiosidad: **quería entender cómo funcionan las herramientas de escaneo de red como Nmap**, y decidí aplicar conceptos de estructuras de datos para construir mi propia versión desde cero.

## 🧠 El Concepto: ¿Por qué un Árbol Binario?
La mayoría de los escáneres de red básicos recorren los puertos de forma secuencial (1, 2, 3, 4...). Esto es predecible y fácil de detectar por cualquier Firewall moderno y por meramente curiosidad de usar un árbol binario.

Para evadir este patrón, decidí estructurar los puertos objetivo dentro de un **Árbol Binario de Búsqueda (BST)**. Al realizar el escaneo utilizando un algoritmo de recorrido en **Pre-Orden** (Raíz -> Izquierda -> Derecha), el escáner "salta" matemáticamente a través del espectro de puertos. Esto genera un patrón asimétrico que difumina la huella del escaneo.

## ⚙️ Bajo el capó: La función `check()`
El mayor reto técnico fue evitar que el programa se quedara "congelado" cuando un Firewall enemigo ignoraba nuestras peticiones (lo que se conoce como regla DROP). Para solucionarlo, la función `check` utiliza la API de Sockets de POSIX en Linux con una arquitectura táctica:

1. **Sockets No-Bloqueantes:** Utilizo `fcntl()` para aplicar la bandera `O_NONBLOCK` al socket. Esto permite que el programa envíe la petición de conexión (`connect()`) y continúe su ejecución instantáneamente sin quedarse trabado esperando.
2. **El Vigilante (`select`):** Para controlar el tiempo de espera, le entrego el socket a la función `select()` junto con un reloj (`struct timeval`) configurado estrictamente a 1 segundo de *timeout*. `select` se encarga de vigilar si hay actividad en la red.
3. **Verificación Definitiva (`getsockopt`):** Si `select` detecta que el puerto reaccionó antes de que se acabe el tiempo, interrogo al sistema operativo utilizando `getsockopt()` para buscar errores internos (`SO_ERROR`). Si el error es `0`, confirmo que la conexión fue exitosa y el puerto está abierto.
4. **Limpieza:** Pase lo que pase (timeout, puerto abierto o puerto cerrado), el socket siempre se cierra con `close()` para evitar fugas de memoria (File Descriptor Leaks).

## 🚀 Características
- Escaneo asimétrico mediante recorridos Pre-Orden de un BST personalizado.
- Implementación de Sockets No-Bloqueantes (Non-blocking I/O) en C++ puro.
- Gestión estricta de *timeouts* (1 segundo máximo por puerto) para evadir bloqueos.
- Integración nativa a bajo nivel con la red en Linux (`<sys/socket.h>`, `<arpa/inet.h>`, `<sys/select.h>`).

## 🛠️ Cómo compilar y ejecutar
Este proyecto fue desarrollado y probado en entornos Linux.

```bash
# Compilar el código
g++ code.cpp -o scanner

# Ejecutar la herramienta
./scanner
