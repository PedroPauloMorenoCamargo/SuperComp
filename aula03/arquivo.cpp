#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Estatisticas {
    int totalPalavras = 0;
    int totalLinhas = 0;
    double mediaPalavrasPorLinha = 0.0;
    string palavraMaisFrequente;
};

vector<string> dividirPalavras(const string& linha) {
    vector<string> palavras;
    stringstream ss(linha);
    string palavra;
    while (ss >> palavra) {
        palavras.push_back(palavra);
    }
    return palavras;
}

Estatisticas calcularEstatisticas(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    Estatisticas est;
    map<string, int> frequenciaPalavras;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return est;
    }

    string linha;
    while (getline(arquivo, linha)) {
        est.totalLinhas++;
        vector<string> palavras = dividirPalavras(linha);
        est.totalPalavras += palavras.size();

        for (const auto& palavra : palavras) {
            frequenciaPalavras[palavra]++;
        }
    }

    if (est.totalLinhas > 0) {
        est.mediaPalavrasPorLinha = static_cast<double>(est.totalPalavras) / est.totalLinhas;
    }

    auto maisFrequente = max_element(frequenciaPalavras.begin(), frequenciaPalavras.end(),
                                     [](const pair<string, int>& a, const pair<string, int>& b) {
                                         return a.second < b.second;
                                     });
    
    if (maisFrequente != frequenciaPalavras.end()) {
        est.palavraMaisFrequente = maisFrequente->first;
    }

    arquivo.close();
    return est;
}

void gravarEstatisticas(const string& nomeArquivoSaida, const Estatisticas& est) {
    ofstream arquivoSaida(nomeArquivoSaida);

    if (!arquivoSaida.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída." << endl;
        return;
    }

    arquivoSaida << "Estatísticas do Texto:\n";
    arquivoSaida << "Número total de palavras: " << est.totalPalavras << endl;
    arquivoSaida << "Número total de linhas: " << est.totalLinhas << endl;
    arquivoSaida << "Número médio de palavras por linha: " << est.mediaPalavrasPorLinha << endl;
    arquivoSaida << "Palavra mais frequente: " << est.palavraMaisFrequente << endl;

    arquivoSaida.close();
    cout << "Estatísticas gravadas no arquivo " << nomeArquivoSaida << endl;
}

int main() {
    string nomeArquivoEntrada, nomeArquivoSaida;

    cout << "Digite o nome do arquivo de entrada: ";
    cin >> nomeArquivoEntrada;

    cout << "Digite o nome do arquivo de saída: ";
    cin >> nomeArquivoSaida;

    Estatisticas est = calcularEstatisticas(nomeArquivoEntrada);
    gravarEstatisticas(nomeArquivoSaida, est);

    return 0;
}
