# Network-scanner
# 🌲 Stealth Node Scanner (C++)

Un escáner de red experimental y sigiloso construido en C++ que utiliza **Árboles Binarios de Búsqueda (BST)** para evadir la detección secuencial de Firewalls y sistemas IDS básicos.

## 🧠 El Concepto
La mayoría de los escáneres de red tradicionales recorren los puertos de forma secuencial (ej. 1, 2, 3, 4...). Esto es altamente predecible y los Firewalls modernos bloquean la IP origen casi de inmediato al detectar este patrón.

Este proyecto resuelve ese problema estructurando los puertos objetivo en un **Árbol Binario de Búsqueda**. Al realizar un escaneo utilizando un algoritmo de recorrido **Pre-Orden** (Raíz -> Izquierda -> Derecha), el escáner "salta" numéricamente de forma caótica a través del espectro de puertos, difuminando la huella del escaneo y haciéndolo menos predecible para un guardia de seguridad digital.

## 🚀 Características (En desarrollo)
- Estructuración de puertos objetivo en un BST personalizado.
- Escaneo asimétrico mediante recorrido Pre-Orden.
- Integración nativa con Sockets POSIX de Linux para conexiones TCP.
- (Próximamente) Implementación de Timeouts (non-blocking sockets) para evadir reglas DROP.

## 🛠️ Cómo compilar y ejecutar
Este proyecto está diseñado para sistemas basados en Linux.

```bash
# Compilar el código
g++ tree.cpp -o scanner

# Ejecutar la herramienta
./scanner
