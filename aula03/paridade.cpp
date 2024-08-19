#include <iostream>  // Include necessary header for input/output

// Main function
int main() {
    
    //O usuario deve inserir um numero e tranformar em inteiro
    int num1;

    std::cout << "Digite um numero: ";
    std::cin >> num1;
    //Cria uma variavel que recebe uma string
    if (num1 % 2 == 0){
        std::cout << "Par" << std::endl;
    }
    else{
        std::cout << "Impar" << std::endl;
    }
    // Return 0 to indicate successful execution
    return 0;
}
