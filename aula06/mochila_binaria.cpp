#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct item {
    int id;
    double peso;
    double valor;
};

int mochila(const vector<int>& pesos, const vector<int>& valores, int capacidade, int n, vector<int>& itensSelecionados) {
    if (capacidade == 0 || n == 0) {
        return 0;
    }

    if (pesos[n - 1] > capacidade) {
        return mochila(pesos, valores, capacidade, n - 1, itensSelecionados);
    } else {
        // Vetores temporários para rastrear os itens selecionados
        vector<int> incluiItens, excluiItens;

        // Valor ao incluir o item atual
        int inclui = valores[n - 1] + mochila(pesos, valores, capacidade - pesos[n - 1], n - 1, incluiItens);
        
        // Valor ao não incluir o item atual
        int exclui = mochila(pesos, valores, capacidade, n - 1, excluiItens);

        // Decisão de incluir ou não o item atual baseado no valor máximo
        if (inclui > exclui) {
            incluiItens.push_back(n - 1);  // Adiciona o item atual (indexado de 0)
            itensSelecionados = incluiItens;  // Atualiza a lista de itens selecionados
            return inclui;
        } else {
            itensSelecionados = excluiItens;  // Atualiza a lista de itens selecionados
            return exclui;
        }
    }
}

void lerArquivo(const std::string& nomeArquivo, vector<int>& peso, vector<int>& valor, int& capacidade, int& nItens) {
    // Read from the text file
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
    vector<int> pesos;
    vector<int> valores;
    int capacidade = 0, nItens = 0;
    vector<int> itensSelecionados;

    // Ajuste o nome do arquivo para corresponder ao seu arquivo de entrada
    lerArquivo("entrada4.txt", pesos, valores, capacidade, nItens);

    int valorMaximo = mochila(pesos, valores, capacidade, nItens, itensSelecionados);

    cout << "Valor máximo que pode ser carregado na mochila: " << valorMaximo << endl;

    cout << "Itens selecionados (baseado em índice 0): ";
    for (int i = 0; i < itensSelecionados.size(); i++) {
        cout << itensSelecionados[i] << " ";
    }
    cout << endl;

    return 0;
}


