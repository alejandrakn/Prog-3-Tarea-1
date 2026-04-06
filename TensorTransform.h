#ifndef TENSOR_TRANSFORM_H
#define TENSOR_TRANSFORM_H

class TensorTransform {
public:
    virtual double apply(double x) const = 0;
    virtual ~TensorTransform() {}
};

#endif