#include <iostream>  // Include necessary header for input/output

// Main function
int main() {
    
    int contador = 0;
    std::cout << "Digite uma palavra: ";
    //Cria uma variavel que recebe uma string
    std::string palavra;
    std::cin >> palavra;

    for (int i = 0; i < palavra.size(); i++){
        contador +=1;
    }
    std::cout << "A palavra tem " << contador << " letras" << std::endl;
    // Return 0 to indicate successful execution
    return 0;
}
