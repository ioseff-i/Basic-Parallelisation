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
    double w = 0.01;
    double b = 0.0;
    double lr = 0.0001;

    double X[10] = {1,2,3,4,5,6,7,8,9,10};   // 10 inputs
    double Y[10] = {0,1,0,1,0,1,0,1,0,1};
    int N = 10;

    for(int epoch = 0; epoch < 10000; epoch++) {
        double total_dw = 0.0;
        double total_db = 0.0;
        double total_loss = 0.0;

        #pragma omp parallel for reduction(+:total_dw,total_db,total_loss)
        for(int i = 0; i < N; i++) {
            double dw, db;
            int tid = omp_get_thread_num();
            double pred = forward(X[i], w, b);
            total_loss += 0.5 * pow(pred - Y[i], 2);
            backward(X[i], Y[i], w, b, &dw, &db);
            total_dw += dw;
            total_db += db;

            // Show each thread's contribution
            printf("Thread %d processing sample %d: dw=%.4f, db=%.4f, pred=%.4f, target=%.1f\n",
                   tid, i, dw, db, pred, Y[i]);
        }

        // Update weights (after reduction)
        w -= lr * total_dw;
        b -= lr * total_db;

        if(epoch % 100 == 0)
            printf("\nEpoch %d: Loss=%.4f, w=%.4f, b=%.4f\n----------------------------\n",
                   epoch, total_loss, w, b);
    }

    return 0;
}