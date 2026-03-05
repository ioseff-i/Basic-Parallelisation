#include <stdio.h>
#include <math.h>
#include <omp.h>

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double forward(double x, double w, double b) {
    return sigmoid(w*x + b);
}

void backward(double x, double y, double w, double b, double *dw, double *db) {
    double z = w*x + b;
    double a = sigmoid(z);
    double dz = a - y;
    *dw = dz * x;
    *db = dz;
}

int main() {
    double w = 0.5;
    double b = 0.0;
    double lr = 0.1;

    double X[8] = {0,1,2,3,4,5,6,7};   // 8 inputs
    double Y[8] = {0,1,1,0,0,1,1,0};
    int N = 8;

    for(int epoch = 0; epoch < 1000; epoch++) {
        double total_dw = 0.0;
        double total_db = 0.0;
        double total_loss = 0.0;

        #pragma omp parallel for reduction(+:total_dw,total_db,total_loss)
        for(int i = 0; i < N; i++) {
            double dw, db;
            double pred = forward(X[i], w, b);
            total_loss += 0.5 * pow(pred - Y[i], 2);
            backward(X[i], Y[i], w, b, &dw, &db);
            total_dw += dw;
            total_db += db;
        }

        // Update weights (after reduction)
        w -= lr * total_dw;
        b -= lr * total_db;

        if(epoch % 100 == 0)
            printf("Epoch %d: Loss=%.4f, w=%.4f, b=%.4f\n", epoch, total_loss, w, b);
    }

    return 0;
}