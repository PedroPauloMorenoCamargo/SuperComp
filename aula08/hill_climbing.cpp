#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono> 
using namespace std;

struct Item {
    int id;
    double peso;
    double valor;
};

// Função para ler o arquivo de entrada
void lerArquivo(const string& nomeArquivo, vector<Item>& itens, int& capacidade, int& nItens) {
    ifstream inputFile(nomeArquivo);
    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return;
    }

    inputFile >> nItens >> capacidade;
    itens.clear();

    double peso, valor;
    for (int i = 0; i < nItens; ++i) {
        inputFile >> peso >> valor;
        itens.push_back({i, peso, valor});
    }

    inputFile.close();
}

// Funções auxiliares para o Hill Climbing
double calculaValor(const vector<Item>& itens, const vector<int>& solucao) {
    double valorTotal = 0;
    for (size_t i = 0; i < itens.size(); ++i) {
        if (solucao[i] == 1) {
            valorTotal += itens[i].valor;
        }
    }
    return valorTotal;
}

double calculaPeso(const vector<Item>& itens, const vector<int>& solucao) {
    double pesoTotal = 0;
    for (size_t i = 0; i < itens.size(); ++i) {
        if (solucao[i] == 1) {
            pesoTotal += itens[i].peso;
        }
    }
    return pesoTotal;
}

vector<int> geraVizinho(const vector<int>& solucaoAtual) {
    vector<int> vizinho = solucaoAtual;
    int pos = rand() % solucaoAtual.size();
    vizinho[pos] = !vizinho[pos]; // Inverte o bit em uma posição aleatória
    return vizinho;
}

// Função de Hill Climbing
vector<int> hillClimbing(const vector<Item>& itens, int capacidade) {
    // Solução inicial aleatória
    vector<int> solucaoAtual(itens.size(), 0);

    double valorAtual = calculaValor(itens, solucaoAtual);
    double pesoAtual = calculaPeso(itens, solucaoAtual);

    bool melhorou = true;
    double valorVizinho, pesoVizinho;

    while (melhorou) {
        melhorou = false;
        vector<int> melhorVizinho = solucaoAtual;

        for (int i = 0; i < solucaoAtual.size(); ++i) {
            vector<int> vizinho = solucaoAtual;
            vizinho[i] = !vizinho[i]; // Gera vizinho modificando um bit

            pesoVizinho = calculaPeso(itens, vizinho);
            valorVizinho = calculaValor(itens, vizinho);

            if (pesoVizinho <= capacidade && valorVizinho > valorAtual) {
                melhorVizinho = vizinho;
                valorAtual = valorVizinho;
                pesoAtual = pesoVizinho;
                melhorou = true;
            }
        }

        solucaoAtual = melhorVizinho;
    }

    return solucaoAtual;
}

int main() {
    vector<Item> itens;
    int capacidade = 0, nItens = 0;

    // Ler o arquivo de entrada
    lerArquivo("entrada3.txt", itens, capacidade, nItens);

    // Executar Hill Climbing
    auto inicio = chrono::high_resolution_clock::now();
    vector<int> solucao = hillClimbing(itens, capacidade);
    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> duracao = fim - inicio;
    for (int bit : solucao) {
        cout << bit << " ";
    }
    cout << "\nValor total: " << calculaValor(itens, solucao) << "\n";
    cout << "Peso total: " << calculaPeso(itens, solucao) << "\n";
    cout << "Tempo de execucaoo: " << duracao.count() << " segundos" << endl;

    return 0;
}
