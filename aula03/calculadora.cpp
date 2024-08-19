#include <iostream>  // Include necessary header for input/output

// Main function
int main() {
    
    //O usuario deve inserir um numero e tranformar em inteiro
    float num1,num2, resultado;
    //Cria uma variavel que recebe uma string
    std::string operacao;

    std::cout << "Digite um numero: ";
    std::cin >> num1;

    std::cout << "Digite um numero: ";
    std::cin >> num2;

    std::cout << "Digite a operacao: ";
    std::cin >> operacao;

    if(operacao == "+"){
        resultado = num1 + num2;
    }
    else if(operacao == "-"){
        resultado = num1 - num2;
    }
    else if(operacao == "*"){
        resultado = num1 * num2;
    }
    else if(operacao == "/"){
        resultado = num1 / num2;
    }
    else{
        std::cout << "Operacao invalida" << std::endl;
        return 1;
    }
    // Print "Hello, World!" to the console
    std::cout << resultado << std::endl;

    // Return 0 to indicate successful execution
    return 0;
}
