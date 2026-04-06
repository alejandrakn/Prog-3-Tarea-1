#include "Tensor.h"
#include "ReLU.h"
#include "Sigmoid.h"
#include <iostream>
using namespace std;

int main() {

    Tensor input({1, 3}, {1.0, 2.0, 3.0});

    //capa 1
    Tensor W1({3, 2}, {
        0.5, 0.2,
        0.1, 0.7,
        0.3, 0.9
    });
    Tensor b1({1, 2}, {0.1, 0.1});
    ReLU relu;
    Tensor out1 = matmul(input, W1) + b1;
    out1 = out1.apply(relu);

    //capa 2
    Tensor W2({2, 1}, {
        0.4,
        0.6
    });
    Tensor b2({1, 1}, {0.2});
    Sigmoid sig;
    Tensor out2 = matmul(out1, W2) + b2;
    out2 = out2.apply(sig);

    cout << "Red neuronal ejecutada correctamente\n";

    return 0;
}