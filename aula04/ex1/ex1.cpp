#include <iostream>   // Inclui a biblioteca padrão de entrada e saída, usada para operações como std::cout.
#include <fstream>    // Inclui a biblioteca para manipulação de arquivos, usada para ler e escrever arquivos.
#include <vector>     // Inclui a biblioteca de vetores, usada para armazenar e manipular listas de números.
#include <cctype>
// Declaração de funções:

// Função que lê números de um arquivo e os armazena em um vetor.
void lerArquivo(const std::string& nomeArquivo, std::vector<int>& numeros);

// Função que dobra os valores de um vetor de números, passando o vetor original por referência.
void dobrarValoresReferencia(const std::vector<int>& numerosOriginais, std::vector<int>& numerosDobrados);

// Função que dobra os valores de um vetor de números, passando o vetor original por ponteiro.
void dobrarValoresPonteiro(const std::vector<int>* numerosOriginais, std::vector<int>* numerosDobrados);

// Função que escreve os números de um vetor em um arquivo.
void escreverArquivo(const std::string& nomeArquivo, const std::vector<int>& numeros);

// Implementação das funções...

void lerArquivo(const std::string& nomeArquivo, std::vector<int>& numeros){
    // Read from the text file
    std::ifstream inputFile(nomeArquivo);

    numeros.clear();

    // Check if the file was opened successfully 
    if (!inputFile) { 
        std::cout << "Unable to open file"; 
    } 

    char c;
    int i = 0;
    while (inputFile.get(c)){
        int num = (int)c -48;
        numeros.push_back(num);
    }

    inputFile.close();

}

// Implementação das funções...

void escreverArquivo(const std::string& nomeArquivo, std::vector<int>& numeros){
    // Read from the text file
    std::ofstream outputFile(nomeArquivo);

    // Check if the file was opened successfully 
    if (!outputFile) { 
        std::cout << "Unable to open file"; 
    } 

    // Dobra os valores e armazena no vetor de destino
    for (size_t i = 0; i < numeros.size(); ++i) {
        outputFile << numeros[i];
    }

    outputFile.close();

}


// Função que dobra os valores de um vetor de números, passando o vetor original por referência.
void dobrarValoresReferencia(const std::vector<int>& numerosOriginais, std::vector<int>& numerosDobrados){
    // Limpa o vetor de destino para garantir que não haja dados antigos
    numerosDobrados.clear();
    
    // Redimensiona o vetor de destino para ter o mesmo tamanho que o vetor original
    numerosDobrados.resize(numerosOriginais.size());
    
    // Dobra os valores e armazena no vetor de destino
    for (size_t i = 0; i < numerosOriginais.size(); ++i) {
        numerosDobrados[i] = numerosOriginais[i] * 2;
    }
}

void dobrarValoresPonteiro(const std::vector<int>* numerosOriginais, std::vector<int>* numerosDobrados){
    if (numerosOriginais == nullptr || numerosDobrados == nullptr) {
        std::cerr << "Erro: Ponteiro nulo passado para a função." << std::endl;
        return;
    }

    // Limpa o vetor de destino para garantir que não haja dados antigos
    numerosDobrados->clear();

    // Itera sobre cada elemento no vetor original
    for (const int& num : *numerosOriginais) {
        // Dobra o valor e adiciona ao vetor de destino
        numerosDobrados->push_back(num * 2);
    }
}


int main() {
    // Declaração de dois vetores de inteiros: um para armazenar os números lidos do arquivo e outro para armazenar os números dobrados.
    std::vector<int> numeros, numerosDobrados;

    // Chama a função para ler os números do arquivo "entrada.txt" e armazena-os no vetor 'numeros'.
    lerArquivo("entrada.txt", numeros);

    // Chama a função que dobra os valores do vetor 'numeros' usando passagem por referência e armazena o resultado no vetor 'numerosDobrados'.
    dobrarValoresReferencia(numeros, numerosDobrados);

    // Chama a função que escreve os números do vetor 'numerosDobrados' no arquivo "saida_referencia.txt".
    escreverArquivo("saida_referencia.txt", numerosDobrados);
    // Chama a função que dobra os valores do vetor 'numeros' usando passagem por ponteiro e armazena o resultado no vetor 'numerosDobrados'.
    dobrarValoresPonteiro(&numeros, &numerosDobrados);

    // Chama a função que escreve os números do vetor 'numerosDobrados' no arquivo "saida_ponteiro.txt".
    escreverArquivo("saida_ponteiro.txt", numerosDobrados);
    // Retorna 0, indicando que o programa terminou com sucesso.
    return 0;
}