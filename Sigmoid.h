#ifndef SIGMOID_H
#define SIGMOID_H

#include "TensorTransform.h"
#include <cmath>

class Sigmoid : public TensorTransform {
public:
    double apply(double x) const override {
        return 1.0 / (1.0 + std::exp(-x));
    }
};

#endif