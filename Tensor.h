#ifndef TAREA_1_TENSOR_H
#define TAREA_1_TENSOR_H


#include <vector>
#include <iostream>
#include <stdexcept>

class TensorTransform;
//para apply

class Tensor {
private:
    std::vector<size_t> shape; //dimensiones
    double* data; //array manual
    size_t total_size;

    size_t compute_size(const std::vector<size_t>& shape) const; //multiplica dimensiones

public:
    //constructor
    Tensor(const std::vector<size_t>& shape,
           const std::vector<double>& values);

    //copia const
    Tensor(const Tensor& other);
    //movimiento
    Tensor(Tensor&& other) noexcept;
    //paar asignar la; copia
    Tensor& operator=(const Tensor& other);
    //asiganr el moviemnto
    Tensor& operator=(Tensor&& other) noexcept;
    ~Tensor();

    //crean tensores sin usar constructor directo
    static Tensor zeros(const std::vector<size_t>& shape);
    static Tensor ones(const std::vector<size_t>& shape);
    static Tensor arange(int start, int end);

    Tensor operator+(const Tensor& other) const;
    Tensor operator-(const Tensor& other) const;
    Tensor operator*(const Tensor& other) const;
    Tensor operator*(double scalar) const;

    // polimorfismo para que objetos x respndan al mismo metodo
    Tensor apply(const TensorTransform& transform) const;

    //reorganiza const para qiue modifique el og
    Tensor view(const std::vector<size_t>& new_shape)const;

    //este es el random que falto
    static Tensor random(const std::vector<size_t>& shape, double min, double max);

    //dimension de tamaño 1
    Tensor unsqueeze(size_t dim)const;
    //no modifica el og

    //producto . friemd para acceder a data
    friend Tensor dot(const Tensor& a, const Tensor& b);
    // multiplicacion matricial
    friend Tensor matmul(const Tensor& a, const Tensor& b);
};

#endif