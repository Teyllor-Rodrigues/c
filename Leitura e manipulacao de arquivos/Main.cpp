#include <iostream>
#include <fstream>
using namespace std;

void criaArquivo(int *vet, int n , char * nomeArquivo)
{
    ofstream arquivo;
    arquivo.open(nomeArquivo, ios::binary);
    if(!arquivo)
    {
        cout << "Erro ao criar arquivo !!" << endl;
        return;
    }

    for (int i = 0 ; i < n; i++)
    {
        arquivo.write((char *) &vet[i] , sizeof(int));
    }

    arquivo.close();
}

int main(){

    // int vetor[10] = {16,71,40,2,8,9,35,12,21,1};
    // criaArquivo(vetor, 10 , "Numeros.bin");

    ifstream fin;
    fin.open("Numeros.bin");
    if(!fin)
    {
        cout << "Erro ao criar arquivo !!" << endl;
        return 0;
    }

    int valor;
    // enquanto ler consegue processar o dado
    while (fin.read((char *)&valor , sizeof(int)))
    {
        cout << valor << " ";
    }

    return 0;
}
