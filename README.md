Implementación de Tensor en C++

Este proyecto implementa una clase ¨Tensor¨ en C++ desde cero, incluyendo operaciones básicas, transformaciones y una simulación simple de una red neuronal.
```
Estructura del proyecto:
├── Tensor.h
├── Tensor.cpp
├── TensorTransform.h
├── ReLU.h
├── Sigmoid.h
├── main.cpp
└── README.md
```
Requisitos:
Compilador de C++
Soporte para C++11 o superior

Compilacion:

En la terminal, ubicarse en la carpeta del proyecto y ejecutar:
```
g++ -std=c++11 Tensor.cpp main.cpp -o programa

```
Ejecucion:
Luego de compilar:
```
./programa
```
Descripcion:
El programa realiza:
* Creación de tensores
* Operaciones básicas (+, -, *)
* Multiplicación de matrices (¨matmul¨)
* Aplicación de funciones de activación (ReLU y Sigmoid)
* Simulación de una red neuronal de 2 capas (forward pass)


Ejemplo de ejecucion:
El ¨main.cpp¨ implementa una red neuronal simple:

1. Capa 1:
   * Entrada: (1x3)
   * Pesos: (3x2)
   * Activación: ReLU

2. Capa 2:
   * Entrada: (1x2)
   * Pesos: (2x1)
   * Activación: Sigmoid

Salida esperada:
```
Red neuronal ejecutada correctamente
```


