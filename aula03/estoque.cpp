#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Item {
    string nome;
    int quantidade;
};

void adicionarItem(vector<Item>& estoque) {
    Item novoItem;
    cout << "Digite o nome do item: ";
    cin >> novoItem.nome;
    cout << "Digite a quantidade do item: ";
    cin >> novoItem.quantidade;
    estoque.push_back(novoItem);
    cout << "Item adicionado ao estoque.\n";
}

void removerItem(vector<Item>& estoque) {
    string nomeItem;
    cout << "Digite o nome do item a ser removido: ";
    cin >> nomeItem;

    for (auto it = estoque.begin(); it != estoque.end(); ++it) {
        if (it->nome == nomeItem) {
            estoque.erase(it);
            cout << "Item removido do estoque.\n";
            return;
        }
    }

    cout << "Item não encontrado no estoque.\n";
}

void visualizarEstoque(const vector<Item>& estoque) {
    if (estoque.empty()) {
        cout << "O estoque está vazio.\n";
    } else {
        cout << "Estoque atual:\n";
        for (const auto& item : estoque) {
            cout << "Item: " << item.nome << ", Quantidade: " << item.quantidade << endl;
        }
    }
}

int main() {
    vector<Item> estoque;
    int opcao;

    do {
        cout << "\nSistema de Controle de Estoque\n";
        cout << "1. Adicionar item\n";
        cout << "2. Remover item\n";
        cout << "3. Visualizar estoque\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarItem(estoque);
                break;
            case 2:
                removerItem(estoque);
                break;
            case 3:
                visualizarEstoque(estoque);
                break;
            case 4:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    } while (opcao != 4);

    return 0;
}
