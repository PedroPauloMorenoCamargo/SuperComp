#include <iostream>
#include <vector>

class Vector {
public:
    Vector(int tamanho){
        dados = new int[tamanho];
        capacidade = tamanho;
        tam = 0;
    };
    ~Vector(){
        delete[] dados;
    };
    void inicializa(int valor){
        for (int i = 0; i < capacidade; i++){
            dados[i] = valor;
        }
        tam = capacidade;
    };
    int get(int index) const{
        if (index>=0 && index<tam){
            return dados[index];
        }
        throw std::out_of_range("Índice fora do intervalo");
    };
    void set(int index, int valor){
        if (index>=0 && index<tam){
            dados[index] = valor;
        }
        else{
            throw std::out_of_range("Índice fora do intervalo");
        }
    };
    void inserir(int index, int valor){
        if (index < 0 || index > tam) {
            throw std::out_of_range("Índice fora do intervalo"); 
        }
        if (tam == capacidade){
            redimensiona(2*capacidade);
        }
        for (int i = tam; i > index; i--){
            dados[i] = dados[i-1];
        }
        dados[index] = valor;
        tam++;

    };
    void remover(int index){
        if (index < 0 || index >= tam) {
            throw std::out_of_range("Índice fora do intervalo"); 
        }
        for (int i = index; i < tam-1; i++){
            dados[i] = dados[i+1];
        }
        tam--;
        if (tam > 0 && tam == capacidade/4){
            redimensiona(capacidade/2);
        }
    };
    void imprime() const{
        for (int i = 0; i < tam; i++){
            std::cout << dados[i] << " ";
        }
        std::cout << std::endl;
    };
    void multiplicar_escalar(int escalar){
        for (int i = 0; i < tam; i++){
            dados[i] *= escalar;
        }
    };

private:
    int* dados;
    int tam;
    int capacidade;
    void redimensiona(int novaCapacidade){
        int* novo = new int[novaCapacidade];
        for (int i = 0; i < tam; i++){
            novo[i] = dados[i];
        }
        delete[] dados;
        dados = novo;
        capacidade = novaCapacidade;
    };
};

// Implementação das funções...

int main() {
    Vector vec(5);       // Cria um vetor com capacidade inicial de 5 elementos
    vec.inicializa(0);   // Inicializa todos os elementos do vetor com o valor 0
    vec.imprime();       // Imprime os elementos do vetor

    vec.inserir(2, 10);  // Insere o valor 10 no índice 2
    vec.imprime();       // Imprime os elementos do vetor

    vec.set(0, 5);       // Define o valor do primeiro elemento como 5
    vec.imprime();       // Imprime os elementos do vetor

    vec.remover(1);      // Remove o elemento no índice 1
    vec.imprime();       // Imprime os elementos do vetor

    vec.multiplicar_escalar(2);  // Multiplica todos os elementos por 2
    vec.imprime();               // Imprime os elementos do vetor


    return 0;
}