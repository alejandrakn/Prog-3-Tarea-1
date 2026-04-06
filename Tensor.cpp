#include "Tensor.h"
#include <iostream>
#include <random>
#include "TensorTransform.h"

//compute size
size_t Tensor::compute_size(const std::vector<size_t>& shape) const {
    size_t size = 1;

    for (size_t dim : shape) {
        size *= dim;
    }

    return size;
}

//principal const
Tensor::Tensor(const std::vector<size_t>& shape,
               const std::vector<double>& values) {

    this->shape = shape;//gurdalo
    total_size = compute_size(shape);

    if (values.size() != total_size) {
        std::cerr << "Error: Tamano\n";//murio
        data = nullptr;
        total_size = 0;
        return;
    }

    data = new double[total_size];//reservar memo

    for (size_t i = 0; i < total_size; i++) {
        data[i] = values[i];
    }
}
Tensor::~Tensor() {
    delete[] data;
}

//DEEP copy
Tensor::Tensor(const Tensor& other) {
    shape = other.shape;
    total_size = other.total_size;

    data = new double[total_size];

    for (size_t i = 0; i < total_size; i++) {
        data[i] = other.data[i];
    }
}
//para memo
Tensor::Tensor(Tensor&& other) noexcept {
    shape = other.shape;
    total_size = other.total_size;
    data = other.data;

    other.data = nullptr;
    other.total_size = 0;
}
//COPY ASSIGNMENT
Tensor& Tensor::operator=(const Tensor& other) {
    if (this == &other) return *this;

    delete[] data;

    shape = other.shape;
    total_size = other.total_size;
    if (other.data) {
        data = new double[total_size];
        for (size_t i = 0; i < total_size; i++) {
            data[i] = other.data[i];
        }
    } else {
        data = nullptr;
    }

    return *this;
}
//MOVE ASSIGNMENT
Tensor& Tensor::operator=(Tensor&& other) noexcept {
    if (this == &other) return *this;

    delete[] data;

    shape = other.shape;
    total_size = other.total_size;
    data = other.data;

    other.data = nullptr;
    other.total_size = 0;

    return *this;
}



//ZEROS
Tensor Tensor::zeros(const std::vector<size_t>& shape) {
    size_t total = 1;

    for (size_t dim : shape) {
        total *= dim;
    }

    std::vector<double> values(total, 0.0);

    return Tensor(shape, values);
}
//ONES
Tensor Tensor::ones(const std::vector<size_t>& shape) {
    size_t total = 1;

    for (size_t dim : shape) {
        total *= dim;
    }

    std::vector<double> values(total, 1.0);

    return Tensor(shape, values);
}
//ARANGE
Tensor Tensor::arange(int start, int end) {
    if (end <= start) {
        throw std::invalid_argument("Rango invalido");
    }

    size_t size = end - start;

    std::vector<size_t> shape = {size};
    std::vector<double> values(size);

    for (int i = 0; i < size; i++) {
        values[i] = start + i;
    }

    return Tensor(shape, values);
}
//RANDOM
Tensor Tensor::random(const std::vector<size_t>& shape, double min, double max) {
    size_t total = 1;

    for (size_t dim : shape) {
        total *= dim;
    }

    std::vector<double> values(total);

    //generador aleatorio
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min, max);

    for (size_t i = 0; i < total; i++) {
        values[i] = dist(gen);
    }

    return Tensor(shape, values);
}

//operadores
Tensor Tensor::operator+(const Tensor& other) const {

    // verificar que tengan la misma forma
    if (shape != other.shape) {
        std::cerr << "Error: Forma\n";
        return Tensor({0}, {});
    }

    std::vector<double> values(total_size);

    for (size_t i = 0; i < total_size; i++) {
        values[i] = data[i] + other.data[i];
    }

    return Tensor(shape, values);
}
Tensor Tensor::operator-(const Tensor& other) const {

    if (shape != other.shape) {
        std::cerr << "Error: Forma\n";
        return Tensor({0}, {});
    }

    std::vector<double> values(total_size);

    for (size_t i = 0; i < total_size; i++) {
        values[i] = data[i] - other.data[i];
    }

    return Tensor(shape, values);
}
Tensor Tensor::operator*(double scalar) const { //este es escalar

    std::vector<double> values(total_size);

    for (size_t i = 0; i < total_size; i++) {
        values[i] = data[i] * scalar;
    }

    return Tensor(shape, values);
}
Tensor Tensor::operator*(const Tensor& other) const {//este es elm x elm

    if (shape != other.shape) {
        std::cerr << "Error: Forma\n";
        return Tensor({0}, {});
    }

    std::vector<double> values(total_size);

    for (size_t i = 0; i < total_size; i++) {
        values[i] = data[i] * other.data[i];
    }

    return Tensor(shape, values);
}
//APPLY
Tensor Tensor::apply(const TensorTransform& transform) const {

    std::vector<double> values(total_size);

    for (size_t i = 0; i < total_size; i++) {
        values[i] = transform.apply(data[i]);
    }

    return Tensor(shape, values);
}


//view
Tensor Tensor::view(const std::vector<size_t>& new_shape) const {

    size_t new_size = compute_size(new_shape);

    if (new_size != total_size) {
        std::cerr << "Error\n";//muere
        return Tensor({0}, {});
    }

    std::vector<double> values(total_size);

    for (size_t i = 0; i < total_size; i++) {
        values[i] = data[i];
    }

    return Tensor(new_shape, values);
}

//unsqueeze
Tensor Tensor::unsqueeze(size_t dim) const {

    if (dim > shape.size()) {
        std::cerr << "Error: Dimension invalida\n";
        return Tensor({0}, {});
    }

    std::vector<size_t> new_shape = shape;

    new_shape.insert(new_shape.begin() + dim, 1);

    std::vector<double> values(total_size);

    for (size_t i = 0; i < total_size; i++) {
        values[i] = data[i];
    }

    return Tensor(new_shape, values);
}
//DOT
Tensor dot(const Tensor& a, const Tensor& b) {

    if (a.shape.size() != 1 || b.shape.size() != 1) {
        std::cerr << "Error: dot solo soporta tensores de 1D \n";
        return Tensor({0}, {});
    }

    if (a.shape[0] != b.shape[0]) {
        std::cerr << "Error: Tamano\n";
        return Tensor({0}, {});
    }

    double result = 0.0;

    for (size_t i = 0; i < a.shape[0]; i++) {
        result += a.data[i] * b.data[i];
    }

    return Tensor({1}, {result});
}

//MATMUL
Tensor matmul(const Tensor& a, const Tensor& b) {

    //verificar que sean 2D
    if (a.shape.size() != 2 || b.shape.size() != 2) {
        std::cerr << "Error: matmul solo 2D\n";
        return Tensor({0}, {});
    }

    //dimensiones
    size_t m = a.shape[0]; //filas de A
    size_t n = a.shape[1]; //columnas de A
    size_t n2 = b.shape[0]; //filas de B
    size_t p = b.shape[1]; // columnas de B

    //verifica que pueda x
    if (n != n2) {
        std::cerr << "Error: dimensiones no compatibles\n";
        return Tensor({0}, {});
    }

    //nueva forma m x p
    std::vector<size_t> new_shape = {m, p};

    //vector resultado inicio en 0
    std::vector<double> values(m * p, 0.0);

    //se viene
    for (size_t i = 0; i < m; i++) {        //fa
        for (size_t j = 0; j < p; j++) {    //cb

            double sum = 0.0;
            for (size_t k = 0; k < n; k++) {
                //A(i,k)=i*n+k
                //B(k,j)=k*p+j
                sum += a.data[i * n + k] * b.data[k * p + j];
            }
            values[i * p + j] = sum;
        }
    }
    return Tensor(new_shape, values);
}
