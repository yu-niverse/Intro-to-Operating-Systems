# include <iostream>
# include <thread>
# include <unistd.h>
using namespace std;

# define MAX 500

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication
long long add_sum[4];
long long mul_sum[4];


void *cal(void * index) {
    int n = *(int *)index;

    for (int i = 125 * n; i < 125 * (n + 1); i++) {
        for (int j = 0; j < MAX; j++) {
            // Addition -> matC
            matC[i][j] = matA[i][j] + matB[i][j];
            add_sum[n] += matC[i][j];

            // Multiplication -> matD
            matD[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
            mul_sum[n] += matD[i][j];
        }
    }

    return NULL;
}

int main() {

    // get input
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) 
            cin >> matA[i][j];
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) 
            cin >> matB[i][j];
    }

    // Addition & Multiplication
    pthread_t threads[4];
    int args[4];
    for (int i = 0; i < 4; i++) {
        args[i] = i;
        pthread_create(&threads[i], NULL, cal, &args[i]);
    }
    for (int i = 0; i < 4; i++) pthread_join(threads[i], NULL);

    long long sum_C = 0;
    long long sum_D = 0;
    for (int i = 0; i < 4; i++) {
        sum_C += add_sum[i];
        sum_D += mul_sum[i];
    }
    
    cout << sum_C << "\n";
    cout << sum_D << "\n";

    return 0;
}