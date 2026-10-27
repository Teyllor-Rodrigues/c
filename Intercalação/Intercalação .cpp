#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <stdexcept>
#include <algorithm>
using namespace std;
class IntercalacaoTest
{
private:
    /*
     * Funcao: mostraArquivo
     *
     * Finalidade:
     * Exibir os inteiros armazenados em um arquivo binario.
     *
     * Parametro:
     * nomeArquivo - nome do arquivo que sera exibido.
     *
     * A funcao e privada porque sera utilizada pelos demais
     * metodos da classe para mostrar as runs geradas.
     */
    void mostraArquivo(const char *nomeArquivo)
    {
        ifstream fin(nomeArquivo, ios::binary);
        if (!fin)
        {
            throw runtime_error(
                "Erro ao abrir arquivo para exibicao.");
        }
        int valor;
        bool primeiro = true;
        while (fin.read((char *)&valor, sizeof(valor)))
        {
            if (!primeiro)
            {
                cout << ", ";
            }
            cout << valor;
            primeiro = false;
        }
        if (!fin.eof())
        {
            throw runtime_error(
                "Erro durante a leitura do arquivo.");
        }
        cout << '\n';
    }

    /*
     * Funcao: intercala
     *
     * Finalidade:
     * Intercalar dois arquivos ordenados, produzindo um terceiro
     * arquivo tambem ordenado.
     *
     * Parametros:
     * run1 - primeiro arquivo ordenado.
     * run2 - segundo arquivo ordenado.
     * run_out - arquivo que recebera o resultado.
     *
     * Depois de gerar o arquivo de saida, a funcao o exibe
     * imediatamente na tela.
     */
    
    void intercala(char *run1, char *run2, char *run_out)
    {
        ifstream fin1(run1, ios::binary);
        ifstream fin2(run2, ios::binary);
        ofstream fout(run_out, ios::binary);
        if (!fin1 || !fin2 || !fout)
        {
            throw runtime_error(
                "Erro ao abrir arquivos para intercalacao.");
        }
        int a, b;
        bool temA = bool(fin1.read((char *)&a, sizeof(a)));
        bool temB = bool(fin2.read((char *)&b, sizeof(b)));
        while (temA && temB)
        {
            if (a <= b)
            {
                fout.write((char *)&a, sizeof(a));
                temA = bool(fin1.read((char *)&a, sizeof(a)));
            }
            else
            {
                fout.write((char *)&b, sizeof(b));
                temB = bool(fin2.read((char *)&b, sizeof(b)));
            }
        }
        while (temA)
        {
            fout.write((char *)&a, sizeof(a));
            temA = bool(fin1.read((char *)&a, sizeof(a)));
        }
        while (temB)
        {
            fout.write((char *)&b, sizeof(b));
            temB = bool(fin2.read((char *)&b, sizeof(b)));
        }
        if (!fout)
        {
            throw runtime_error(

                "Erro ao gravar arquivo intercalado.");
        }
        // Fecha o arquivo antes de tentar le-lo.
        fout.close();
        cout << "\nArquivo temporario gerado: "
             << run_out << '\n';
        cout << "Conteudo: ";
        mostraArquivo(run_out);
    }
    /*
     * Funcao: identificador
     *
     * Finalidade:
     * Extrair a identificacao de uma run a partir do nome.
     *
     * Exemplos:
     * run_1.tmp -> 1
     * run_1_2.tmp -> 1_2
     * run_1_2_3.tmp -> 1_2_3
     */
    string identificador(const string &nome)
    {
        size_t inicio = nome.find("run_");
        size_t fim = nome.rfind(".tmp");
        if (inicio == string::npos ||
            fim == string::npos ||
            fim <= inicio + 4)
        {
            throw runtime_error(
                "Nome de arquivo temporario invalido.");
        }
        return nome.substr(
            inicio + 4,
            fim - (inicio + 4));
    }

public:
    /*
    * Funcao: geraArquivo
    *
    * Finalidade:
    * Gerar um arquivo binario com n inteiros aleatorios.
    *
    * Parametros:
    * nomeArquivo - nome do arquivo a ser criado.
    * n - quantidade de inteiros.

    * min - menor valor possivel.
    * max - maior valor possivel.
    *
    * A funcao inicializa um novo gerador aleatorio a cada
    * chamada e exibe o arquivo depois de grava-lo.
    */
    void geraArquivo(
        char *nomeArquivo,
        int n,
        int min,
        int max)
    {
        if (n < 0 || min > max)
        {
            throw invalid_argument(
                "Parametros invalidos para gerar arquivo.");
        }
        random_device rd;
        mt19937 gerador(rd());
        uniform_int_distribution<int> distribuicao(min, max);
        ofstream fout(nomeArquivo, ios::binary);
        if (!fout)
        {
            throw runtime_error(
                "Erro ao criar arquivo de entrada.");
        }
        for (int i = 0; i < n; i++)
        {
            int valor = distribuicao(gerador);
            fout.write((char *)&valor, sizeof(valor));
        }
        if (!fout)
        {
            throw runtime_error(
                "Erro ao gravar arquivo de entrada.");
        }
        fout.close();
        cout << "\nArquivo gerado: "
             << nomeArquivo << '\n';
        cout << "Conteudo: ";
        mostraArquivo(nomeArquivo);
    }
    /*
    * Funcao: ordenacao
    *

    * Finalidade:
    * Ordenar externamente um arquivo binario.
    *
    * Parametros:
    * in - arquivo de entrada.
    * out - arquivo final ordenado.
    * capacidadeMemoria - quantidade maxima de inteiros
    * armazenados em cada run inicial.
    *
    * Etapas:
    * 1. Ler blocos limitados pela capacidade de memoria.
    * 2. Ordenar cada bloco e grava-lo em uma run.
    * 3. Exibir cada run inicial apos sua criacao.
    * 4. Intercalar pares de runs e exibir os resultados.
    * 5. Copiar a run final para o arquivo de saida.
    */
    void ordenacao(
        char *in,
        char *out,
        int capacidadeMemoria)
    {
        if (capacidadeMemoria <= 0)
        {
            throw invalid_argument(
                "A capacidade da memoria deve ser positiva.");
        }
        ifstream fin(in, ios::binary);
        if (!fin)
        {
            throw runtime_error(
                "Erro ao abrir arquivo de entrada.");
        }
        vector<string> runs;
        vector<int> bloco;
        bloco.reserve(capacidadeMemoria);
        int valor;
        int indice = 1;
        cout << "\nFASE 1: ";
        cout << "Criacao das runs iniciais\n";
        // Le e ordena blocos de ate capacidadeMemoria inteiros.
        while (fin.read((char *)&valor, sizeof(valor)))
        {
            bloco.push_back(valor);
            if ((int)bloco.size() == capacidadeMemoria)
            {
                sort(bloco.begin(), bloco.end());
                string nome =

                    "run_" + to_string(indice++) + ".tmp";
                ofstream fout(nome, ios::binary);
                if (!fout)
                {
                    throw runtime_error(
                        "Erro ao criar run inicial.");
                }
                for (size_t i = 0; i < bloco.size(); i++)
                {
                    fout.write(
                        (char *)&bloco[i], sizeof(bloco[i]));
                }
                if (!fout)
                {
                    throw runtime_error(
                        "Erro ao gravar run inicial.");
                }
                fout.close();
                runs.push_back(nome);
                cout << "\nRun inicial gerada: "
                     << nome << '\n';
                cout << "Conteudo: ";
                mostraArquivo(nome.c_str());
                bloco.clear();
            }
        }
        if (!fin.eof())
        {
            throw runtime_error(
                "Erro durante a leitura do arquivo de entrada.");
        }
        fin.close();
        // Grava o ultimo bloco, caso tenha sobrado algum elemento.
        if (!bloco.empty())
        {
            sort(bloco.begin(), bloco.end());
            string nome =
                "run_" + to_string(indice++) + ".tmp";
            ofstream fout(nome, ios::binary);
            if (!fout)
            {

                throw runtime_error(
                    "Erro ao criar ultima run inicial.");
            }
            for (size_t i = 0; i < bloco.size(); i++)
            {
                fout.write(
                    (char *)&bloco[i], sizeof(bloco[i]));
            }
            if (!fout)
            {
                throw runtime_error(
                    "Erro ao gravar ultima run inicial.");
            }
            fout.close();
            runs.push_back(nome);
            cout << "\nRun inicial gerada: "
                 << nome << '\n';
            cout << "Conteudo: ";
            mostraArquivo(nome.c_str());
        }
        // Trata arquivo de entrada vazio.
        if (runs.empty())
        {
            ofstream fout(out, ios::binary);
            if (!fout)
            {
                throw runtime_error(
                    "Erro ao criar arquivo de saida.");
            }
            fout.close();
            cout << "\nArquivo de saida vazio: "
                 << out << '\n';
            return;
        }
        cout << "\nFASE 2: ";
        cout << "Intercalacao das runs\n";
        // Intercala os arquivos aos pares ate restar uma run.
        while (runs.size() > 1)
        {
            vector<string> proximas;
            for (size_t i = 0; i < runs.size(); i += 2)
            {

                if (i + 1 < runs.size())
                {
                    string id1 = identificador(runs[i]);
                    string id2 = identificador(runs[i + 1]);
                    string nome =
                        "run_" + id1 + "_" + id2 + ".tmp";
                    cout << "\nIntercalando "
                         << runs[i] << " e "
                         << runs[i + 1] << '\n';
                    intercala(
                        (char *)runs[i].c_str(),
                        (char *)runs[i + 1].c_str(),
                        (char *)nome.c_str());
                    proximas.push_back(nome);
                }
                else
                {
                    // Preserva a run que ficou sem par.
                    proximas.push_back(runs[i]);
                }
            }
            runs = proximas;
        }
        // Copia a run final para o arquivo de saida.
        ifstream origem(runs[0], ios::binary);
        ofstream destino(out, ios::binary);
        if (!origem || !destino)
        {
            throw runtime_error(
                "Erro ao abrir arquivos para copia final.");
        }
        char buffer[4096];
        while (origem.read(buffer, sizeof(buffer)))
        {
            destino.write(buffer, origem.gcount());
        }
        if (origem.gcount() > 0)
        {
            destino.write(buffer, origem.gcount());
        }
        if (!origem.eof() || !destino)
        {
            throw runtime_error(
                "Erro durante a copia para o arquivo de saida.");
        }
        destino.close();

        origem.close();
        cout << "\nRESULTADO FINAL\n";
        cout << "Arquivo ordenado: " << out << '\n';
        cout << "Conteudo: ";
        mostraArquivo(out);
    }
};
int main()
{
    try
    {
        IntercalacaoTest teste;
        char entrada[] = "entrada.bin";
        char saida[] = "ordenado.bin";
        int quantidade = 20;
        int capacidadeMemoria = 5;
        teste.geraArquivo(
            entrada,
            quantidade,
            0,
            99);
        cout << "\nCapacidade da memoria: "
             << capacidadeMemoria
             << " numeros por run.\n";
        teste.ordenacao(
            entrada,
            saida,
            capacidadeMemoria);
        cout << "\nOrdenacao concluida.\n";
        cout << "Os arquivos temporarios foram preservados.\n";
    }
    catch (const exception &e)
    {
        cerr << "Erro: " << e.what() << '\n';
        return 1;
    }
    return 0;
}