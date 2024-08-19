#include <iostream>
using namespace std;

int diagonal(int arr[], int n) {
    int soma = 0;
    for (int i = 0; i < n; i+=4) {
        soma += arr[i];
    }
    return soma;
}

void printArray(int arr[], int size) {
    int soma = 0;
    for (int i = 0; i < size; i++){
        cout << arr[i] << " ";
        if ((i+1) % 3 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

int main() {
    int arr[9];
    cout << "Digite os elementos da matriz 3x3: \n";
    for (int i = 0; i < 9; i++) {
        cin >> arr[i];
    }
    cout << "Vetor: \n";
    printArray(arr, 9);
    int soma = diagonal(arr, 9);
    cout << "Soma Diagonal: \n" << soma << std::endl;
    return 0;
}