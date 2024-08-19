#include <iostream>  // Include necessary header for input/output

// Main function
int main() {
    //Cria um vetor de 10 posicoes
    float vetor[10];
    for (int i = 0; i < 10; i++){
        std::cout << "Digite um numero: ";
        std::cin >> vetor[i];
    }

    //Loopa pelo vetor e soma os valores
    int maior = 0;
    int size = sizeof(vetor)/sizeof(vetor[0]);

    for (int i = 0; i < size; i++){
        if (vetor[i] > maior){
            maior = vetor[i];
        }
    }

    // Print "Hello, World!" to the console
    std::cout << "Maior item do vetor: " << maior << std::endl;

    // Return 0 to indicate successful execution
    return 0;
}
