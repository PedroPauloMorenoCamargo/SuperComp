#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

struct Item {
    int id;
    double peso;
    double valor;
    
};

// Função gulosa para resolver o problema da mochila
double mochila_leve(vector<Item>& itens, double capacidade, vector<int>& itensSelecionados) {
    // Ordenar itens pela razão valor/peso (do maior para o menor)
    sort(itens.begin(), itens.end(), [](const Item& a, const Item& b) {
        return a.peso < b.peso;
    });

    double valorTotal = 0.0;
    double pesoAtual = 0.0;

    for (const auto& item : itens) {
        if (pesoAtual + item.peso <= capacidade) {
            // Adicionar o item inteiro na mochila
            itensSelecionados.push_back(item.id);
            valorTotal += item.valor;
            pesoAtual += item.peso;
        }
        else{
            break;
        }
    }

    return valorTotal;
}

// Função para ler os itens e a capacidade da mochila de um arquivo
void lerArquivo(const string& nomeArquivo, vector<Item>& itens, double& capacidade) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return;
    }

    int nItens;
    arquivo >> nItens >> capacidade;

    itens.clear();
    for (int i = 0; i < nItens; i++) {
        Item item;
        item.id = i;
        arquivo >> item.peso >> item.valor;
        itens.push_back(item);
    }

    arquivo.close();
}

int main(int argc, char const *argv[]) {
    vector<Item> itens;
    double capacidade;
    vector<int> itensSelecionados;

    // Lê o arquivo de entrada
    lerArquivo("entrada2.txt", itens, capacidade);

    // Medir o tempo de execução
    auto inicio = chrono::high_resolution_clock::now();
    
    // Chamar a função gulosa para a mochila
    double valorMaximo = mochila_leve(itens, capacidade, itensSelecionados);

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> duracao = fim - inicio;

    cout << "Valor maximo que pode ser carregado na mochila: " << valorMaximo << endl;
    cout << "Itens selecionados (baseado em indice 0): ";
    for (int id : itensSelecionados) {
        cout << id << " ";
    }
    cout << endl;
    cout << "Tempo de execucao: " << duracao.count() << " segundos" << endl;

    return 0;
}