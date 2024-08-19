#include <iostream>
using namespace std;

bool palindromo(std::string palavra, int n) {
    bool soma = 0;
    for (int i = 0; i < n/2; i++) {
        if (palavra[i] != palavra[n-i-1]) {
            return false;
        }
    }
    return true;
}

int main() {
    cout << "Digite uma palavra: ";
    std::string palavra;
    cin >> palavra; 
    bool resultado = palindromo(palavra, palavra.size());
    if (resultado) {
        cout << "Palindromo" << endl;
    } else {
        cout << "Nao eh palindromo" << endl;
    }
    return 0;
}