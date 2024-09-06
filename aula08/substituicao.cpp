#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> // Para std::shuffle
#include <random>    // Para random_device e mt19937
#include <chrono>    // Para medição de tempo

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

    inputFile >> nItens >> capacidade;
    peso.clear();
    valor.clear();

    double x, y;
    while (inputFile >> x >> y) {
        peso.push_back(x);
        valor.push_back(y);
    }

    inputFile.close();
}

// Função para calcular o valor total e o peso total de uma solução
void calcularSolucoes(const vector<item>& mochila, int& valorTotal, int& pesoTotal) {
    valorTotal = 0;
    pesoTotal = 0;
    for (const auto& it : mochila) {
        valorTotal += it.valor;
        pesoTotal += it.peso;
    }
}

// Algoritmo 1: Mochila Cheia
vector<item> mochilaCheia(const vector<item>& itens, int capacidade) {
    vector<item> mochila;
    int pesoTotal = 0;

    for (const auto& it : itens) {
        if (pesoTotal + it.peso <= capacidade) {
            mochila.push_back(it);
            pesoTotal += it.peso;
        }
        if (pesoTotal == capacidade) {
            break;
        }
    }

    return mochila;
}

// Algoritmo 2: Substituição de Objeto
vector<item> substituicaoDeObjeto(const vector<item>& itens, int capacidade) {
    vector<item> mochila = mochilaCheia(itens, capacidade);
    bool melhorou = true;

    while (melhorou) {
        melhorou = false;
        int valorMochila, pesoMochila;
        calcularSolucoes(mochila, valorMochila, pesoMochila);

        for (const auto& itemFora : itens) {
            if (find_if(mochila.begin(), mochila.end(), [&itemFora](const item& i) { return i.id == itemFora.id; }) == mochila.end()) {
                for (auto& itemDentro : mochila) {
                    if (pesoMochila - itemDentro.peso + itemFora.peso <= capacidade && itemFora.valor > itemDentro.valor) {
                        // Faz a troca e recalcula os valores
                        pesoMochila = pesoMochila - itemDentro.peso + itemFora.peso;
                        itemDentro = itemFora;
                        melhorou = true;
                        break;
                    }
                }
                if (melhorou) break; // Recalcular depois de cada troca
            }
        }
    }

    return mochila;
}

int main(int argc, char const *argv[]) {
    vector<double> pesos;
    vector<double> valores;
    int capacidade = 0, nItens = 0;

    // Ajuste o nome do arquivo para corresponder ao seu arquivo de entrada
    lerArquivo("entrada3.txt", pesos, valores, capacidade, nItens);

    // Criar um vetor de itens e preenchê-lo com pesos e valores
    vector<item> itens(nItens);
    for (int i = 0; i < nItens; ++i) {
        itens[i] = {i, pesos[i], valores[i]};
    }

    // Embaralhar o vetor de itens
    random_device rd;
    mt19937 g(rd());
    shuffle(itens.begin(), itens.end(), g);

    // Medir tempo de execução
    auto inicio = chrono::high_resolution_clock::now();

    // Executar o algoritmo de Substituição de Objeto
    vector<item> solucaoSubstituicao = substituicaoDeObjeto(itens, capacidade);

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> duracao = fim - inicio;

    // Mostrar solução da Substituição de Objeto
    int valorSubstituicao, pesoSubstituicao;
    calcularSolucoes(solucaoSubstituicao, valorSubstituicao, pesoSubstituicao);
    cout << "Substituicao de Objeto - Valor: " << valorSubstituicao << ", Peso: " << pesoSubstituicao << endl;

    // Exibir o tempo de execução
    cout << "Tempo de execucaoo: " << duracao.count() << " segundos" << endl;

    return 0;
}
