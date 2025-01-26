#include <iostream>
using namespace std;
#define MAX 10

int fibo[MAX];

int main() {
    int i;
    fibo[1] = 1;
    fibo[2] = 1;
    for (int i = 3; i <= MAX; i++) {
        fibo[i] = fibo[i - 2] + fibo[i - 1];
    }
    for (int i = 1; i <= MAX; i++) {
        cout << i << ". " << fibo[i] << endl;
    }
}
