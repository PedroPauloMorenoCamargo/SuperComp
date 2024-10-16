#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random> // Para gerar números aleatórios
#include <chrono>
using namespace std;

struct item {
    int id;
    double peso;
    double valor;
};

void lerArquivo(const std::string& nomeArquivo, vector<double>& peso, vector<double>& valor, int& capacidade, int& nItens) {
    ifstream inputFile(nomeArquivo);
    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return;
    }

    // Lendo a primeira linha para definir nItens e capacidade
    inputFile >> nItens >> capacidade;
    peso.clear();
    valor.clear();

    int x, y;
    while (inputFile >> x >> y) {
        peso.push_back(x);
        valor.push_back(y);
    }

    inputFile.close();
}

int main(int argc, char const *argv[]) {
    vector<double> pesos;
    vector<double> valores;
    int capacidade = 0, nItens = 0;
    vector<int> itensSelecionados;


    lerArquivo("entrada1.txt", pesos, valores, capacidade, nItens);


    vector<item> itens(nItens);
    for (int i = 0; i < nItens; ++i) {
        itens[i] = {i, pesos[i], valores[i]};
    }


    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);


    int pesoTotal = 0;
    int valorTotal = 0;
    double limiar = 0.5; 
    auto inicio = chrono::high_resolution_clock::now();

    for (const auto& it : itens) {
        double probabilidade = dis(gen); 

        if (probabilidade > limiar) {
            if (pesoTotal + it.peso <= capacidade) {
                pesoTotal += it.peso;
                valorTotal += it.valor;
                itensSelecionados.push_back(it.id); 
            }
        }
        if(pesoTotal == capacidade) {
            break;
        }
    }

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> duracao = fim - inicio;

    cout << "Valor maximo que pode ser carregado na mochila: " << valorTotal << endl;
    cout << "Peso total da mochila: " << pesoTotal << endl;
    cout << "Itens selecionados (baseado em indice 0): ";
    for (int i = 0; i < itensSelecionados.size(); i++) {
        cout << itensSelecionados[i] << " ";
    }
    cout << endl;


    cout << "Tempo de execucao: " << duracao.count() << " segundos" << endl;

    return 0;
}
