#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

struct Contato
{
    int codigo;
    char nome[50];
    char telefone[20];
};

class Agenda
{
private:
    Contato contatos[100];
    int quantidade;

public:
    Agenda()
    {
        quantidade = 0;
    }

    void carregar_dados(char *nomearquivo)
    {

        ifstream fin;
        fin.open(nomearquivo, ios::binary);

        if (!fin)
        {
            cout << "Erro ao tentar abrir o arquivo !!" << endl;
            return;
        }

        // Formatacao mais facil
        fin.read((char *)this, sizeof(Agenda));
        fin.close();

        // fin.read( (char *) &this->quantidade , sizeof(quantidade));
        // for (int i = 0 ; i < this->quantidade; i++)
        // {
        //     fin.read( (char*) this->contatos, sizeof (contatos));
        // }
    }

    void salvar_dados(char *nomearquivo)
    {
        ofstream fout;
        fout.open(nomearquivo, ios::binary);

        if (!fout)
        {
            cout << "Erro ao tentar abrir o arquivo !!" << endl;
            return;
        }

        // Formatacao mais facil

        fout.write((char *)this, sizeof(Agenda));
        fout.close();

        // fout.write( (char *) &this->quantidade , sizeof(quantidade));
        // for (int i = 0 ; i < this->quantidade; i++)
        // {
        //     fout.write( (char*) this->contatos, sizeof (contatos));
        // }
    }

    void salvaHTML(char *nomearquivo)
    {
        ofstream fout;
        fout.open(nomearquivo);

        if (!fout)
        {
            cout << "Erro ao criar arquivo HTML";
            return;
        }

        fout << "<html>";

        fout << "<head>";
        fout << "<title> Este é um título </title>";

        fout << "</head>";

        fout << "<body>";
        fout << "<h1> Lista de contatos </h1>";
        fout << "</body>";
        fout << "</html>";
    }

    void inserir()
    {
        if (quantidade >= 100)
        {
            cout << "Limite de 100 contatos atingido!\n";
            return;
        }

        cout << "Codigo: ";
        cin >> contatos[quantidade].codigo;

        cout << "Nome: ";
        cin.ignore();
        cin.getline(contatos[quantidade].nome, 50);

        cout << "Telefone: ";
        cin >> contatos[quantidade].telefone;

        quantidade++;

        cout << "\nContato inserido com sucesso!\n";
    }

    void alterar()
    {
        int codigo;
        int posicao = -1;

        cout << "Digite o codigo do contato: ";
        cin >> codigo;

        for (int i = 0; i < quantidade; i++)
        {
            if (contatos[i].codigo == codigo)
            {
                posicao = i;
                break;
            }
        }

        if (posicao == -1)
        {
            cout << "\nContato nao encontrado!\n";
            return;
        }

        cout << "\nNovo nome: ";
        cin.ignore();
        cin.getline(contatos[posicao].nome, 50);

        cout << "Novo telefone: ";
        cin >> contatos[posicao].telefone;

        cout << "\nContato alterado com sucesso!\n";
    }

    void excluir()
    {
        int codigo;
        int posicao = -1;

        cout << "Digite o codigo do contato: ";
        cin >> codigo;

        for (int i = 0; i < quantidade; i++)
        {
            if (contatos[i].codigo == codigo)
            {
                posicao = i;
                break;
            }
        }

        if (posicao == -1)
        {
            cout << "\nContato nao encontrado!\n";
            return;
        }

        for (int i = posicao; i < quantidade - 1; i++)
        {
            contatos[i] = contatos[i + 1];
        }

        quantidade--;

        cout << "\nContato excluido com sucesso!\n";
    }

    void mostrarTodos()
    {
        if (quantidade == 0)
        {
            cout << "Nenhum contato cadastrado!\n";
            return;
        }

        cout << "===== CONTATOS =====\n\n";

        for (int i = 0; i < quantidade; i++)
        {
            cout << "Codigo: " << contatos[i].codigo << endl;
            cout << "Nome: " << contatos[i].nome << endl;
            cout << "Telefone: " << contatos[i].telefone << endl;
            cout << "-------------------------\n";
        }
    }

    void loop()
    {
        int opcao;

        do
        {
            system("cls");

            cout << "=============================\n";
            cout << "       AGENDA DE CONTATOS\n";
            cout << "=============================\n";
            cout << "1 - Inserir contato\n";
            cout << "2 - Alterar contato\n";
            cout << "3 - Excluir contato\n";
            cout << "4 - Mostrar todos\n";
            cout << "5 - Inserir em HTML\n";
            cout << "0 - Sair\n";
            cout << "=============================\n";
            cout << "Digite uma opcao: ";

            cin >> opcao;

            system("cls");

            switch (opcao)
            {
            case 1:
                inserir();
                break;

            case 2:
                alterar();
                break;

            case 3:
                excluir();
                break;

            case 4:
                mostrarTodos();
                break;

            case 0:
                cout << "Programa encerrado.\n";
                break;

            default:
                cout << "Opcao invalida!\n";
            }

            if (opcao != 0)
            {
                system("pause");
            }

        } while (opcao != 0);
    }
};

int main()
{
    Agenda agenda;
    agenda.carregar_dados("dados.bin");
    agenda.loop();
    agenda.salvar_dados("dados.bin");
    return 0;
}