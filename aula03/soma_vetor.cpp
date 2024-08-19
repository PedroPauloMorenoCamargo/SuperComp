#include <iostream>  // Include necessary header for input/output

// Main function
int main() {
    //Cria um vetor de 5 posicoes
    float vetor[5];
    for (int i = 0; i < 5; i++){
        std::cout << "Digite um numero: ";
        std::cin >> vetor[i];
    }

    //Loopa pelo vetor e soma os valores
    int resultado = 0;
    int size = sizeof(vetor)/sizeof(vetor[0]);

    for (int i = 0; i < size; i++){
        resultado += vetor[i];
    }

    // Print "Hello, World!" to the console
    std::cout << "A soma do Vetor resulta em: " << resultado << std::endl;

    // Return 0 to indicate successful execution
    return 0;
}
