#ifndef RELU_H
#define RELU_H

#include "TensorTransform.h"

class ReLU : public TensorTransform {
public:
    double apply(double x) const override {
        return (x > 0) ? x : 0;
    }
};

#endif