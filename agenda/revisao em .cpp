#include <iostream>
using namespace std;

/*
 * Estrutura que representa um nó da lista duplamente encadeada.
 *
 * Cada nó armazena:
 * - um elemento;
 * - um ponteiro para o nó anterior;
 * - um ponteiro para o próximo nó.
 */
struct Node
{
    int item;
    Node *prev;
    Node *next;
};

/*
 * Classe que implementa uma lista duplamente encadeada.
 *
 * A lista mantém:
 * - head: primeiro nó da lista;
 * - tail: último nó da lista;
 * - n: quantidade de elementos armazenados.
 */
class List
{
private:
    Node *head;
    Node *tail;
    int n;

    /*
     * Localizar o nó que ocupa determinada posição.
     */
    Node* getNode(int pos)
    {
        Node *t;

        // Percorrer a partir do início da lista.
        if (pos < this->n - pos)
        {
            int i = 0;
            t = this->head;

            while (i < pos)
            {
                t = t->next;
                i++;
            }
        }
        else
        {
            // Percorrer a partir do final da lista.
            int i = this->n - 1;
            t = this->tail;

            while (i > pos)
            {
                t = t->prev;
                i--;
            }
        }

        return t;
    }

public:

    /*
     * Inicializar uma lista vazia.
     */
    List()
    {
        this->head = NULL;
        this->tail = NULL;
        this->n = 0;
    }

    /*
     * Liberar a memória utilizada pelos nós da lista.
     */
    ~List()
    {
        this->clear();
    }

    /*
     * Inserir um elemento no início da lista.
     */
    void pushFront(int item)
    {
        Node *nn = new Node();

        nn->item = item;
        nn->prev = NULL;
        nn->next = NULL;

        // Caso a lista esteja vazia, o novo nó será
        // simultaneamente o primeiro e o último elemento.
        if (this->isEmpty())
        {
            this->head = nn;
            this->tail = nn;
        }
        else
        {
            // O novo nó passa a apontar para o antigo primeiro nó.
            nn->next = this->head;

            // O antigo primeiro nó passa a apontar para o novo nó.
            this->head->prev = nn;

            // Atualizar o início da lista.
            this->head = nn;
        }

        this->n++;
    }

    /*
     * Inserir um elemento no final da lista.
     */
    void pushBack(int item)
    {
        // Se a lista estiver vazia, utilizar a operação
        // de inserção no início.
        if (this->isEmpty())
        {
            this->pushFront(item);
        }
        else
        {
            Node *nn = new Node();

            nn->item = item;
            nn->next = NULL;

            // O novo nó será precedido pelo atual último nó.
            nn->prev = this->tail;

            // O atual último nó passa a apontar para o novo nó.
            this->tail->next = nn;

            // Atualizar o final da lista.
            this->tail = nn;

            this->n++;
        }
    }

    /*
     * Inserir um elemento em uma posição específica da lista.
     *
     * As posições válidas para inserção estão entre 0 e n.
     */
    void pushAt(int item, int pos)
    {
        // Verificar se a posição é válida.
        if (pos < 0 || pos > this->n)
        {
            cout << "Erro: indice invalido!!\n";
            return;
        }

        // Inserir no início.
        if (pos == 0)
        {
            this->pushFront(item);
        }

        // Inserir no final.
        else if (pos == this->n)
        {
            this->pushBack(item);
        }

        // Inserir entre dois nós existentes.
        else
        {
            Node *t = this->getNode(pos);
            Node *nn = new Node();

            nn->item = item;

            // Estabelecer os dois novos vínculos.
            nn->prev = t->prev;
            nn->next = t;

            // Atualizar os vínculos dos nós vizinhos.
            t->prev->next = nn;
            t->prev = nn;

            this->n++;
        }
    }

    /*
     * Remover e retornar o elemento que está no início da lista.
     */
    int popFront()
    {
        // Não é possível remover elementos de uma lista vazia.
        if (this->isEmpty())
        {
            cout << "Erro: Lista vazia\n";
            return -1;
        }

        int item = this->head->item;

        // Caso exista apenas um elemento na lista.
        if (this->n == 1)
        {
            delete this->head;

            this->head = NULL;
            this->tail = NULL;
        }
        else
        {
            Node *t = this->head;

            // O segundo nó passa a ser o primeiro.
            this->head = this->head->next;

            // O novo primeiro nó não possui antecessor.
            this->head->prev = NULL;

            delete t;
        }

        this->n--;

        return item;
    }

    /*
     * Remover e retornar o elemento que está no final da lista.
     */
    int popBack()
    {
        // Não é possível remover elementos de uma lista vazia.
        if (this->isEmpty())
        {
            cout << "Erro: Lista vazia\n";
            return -1;
        }

        // Se houver apenas um elemento, utilizar a operação
        // de remoção do início.
        if (this->n == 1)
        {
            return this->popFront();
        }

        Node *t = this->tail;
        int item = this->tail->item;

        // O penúltimo nó passa a ser o último.
        this->tail = this->tail->prev;

        // O novo último nó não possui sucessor.
        this->tail->next = NULL;

        delete t;

        this->n--;

        return item;
    }

    /*
     * Remover e retornar o elemento de uma posição específica.
     */
    int pop(int pos)
    {
        // Não é possível remover elementos de uma lista vazia.
        if (this->isEmpty())
        {
            cout << "Erro: Lista vazia\n";
            return -1;
        }

        // Verificar se a posição existe.
        if (pos < 0 || pos >= this->n)
        {
            cout << "Erro: indice invalido!!\n";
            return -1;
        }

        // Remover o primeiro elemento.
        if (pos == 0)
        {
            return this->popFront();
        }

        // Remover o último elemento.
        if (pos == this->n - 1)
        {
            return this->popBack();
        }

        // Remover um elemento localizado entre dois nós.
        Node *t = this->getNode(pos);
        int item = t->item;

        // Ligar o nó anterior diretamente ao próximo nó.
        t->prev->next = t->next;

        // Ligar o próximo nó diretamente ao nó anterior.
        t->next->prev = t->prev;

        delete t;

        this->n--;

        return item;
    }

    /*
     * Retornar o elemento que está no início da lista,
     * sem removê-lo.
     */
    int getFront()
    {
        if (this->isEmpty())
        {
            cout << "Erro: Lista vazia.\n";
            return -1;
        }

        return this->head->item;
    }

    /*
     * Retornar o elemento que está no final da lista,
     * sem removê-lo.
     */
    int getBack()
    {
        if (this->isEmpty())
        {
            cout << "Erro: Lista vazia.\n";
            return -1;
        }

        return this->tail->item;
    }

    /*
     * Retornar o elemento de uma posição específica,
     * sem removê-lo.
     */
    int get(int pos)
    {
        // Verificar se a posição existe.
        if (pos < 0 || pos >= this->n)
        {
            cout << "Erro: indice invalido!!\n";
            return -1;
        }

        // Consultar o primeiro elemento.
        if (pos == 0)
        {
            return this->getFront();
        }

        // Consultar o último elemento.
        if (pos == this->n - 1)
        {
            return this->getBack();
        }

        // Consultar um elemento intermediário.
        Node *t = this->getNode(pos);

        return t->item;
    }

    /*
     * Retornar a quantidade de elementos armazenados na lista.
     */
    int size()
    {
        return this->n;
    }

    /*
     * Verificar se a lista está vazia.
     */
    bool isEmpty()
    {
        return this->n == 0;
    }

    /*
     * Remover todos os elementos da lista.
     */
    void clear()
    {
        while (!this->isEmpty())
        {
            this->popFront();
        }
    }

    /*
     * Exibir os elementos da lista nos dois sentidos:
     * do início para o final e do final para o início.
     */
    void show()
    {
        cout << "\nList --> ";

        Node *t = this->head;

        // Percorrer a lista do início para o final.
        while (t != NULL)
        {
            cout << t->item << " ";
            t = t->next;
        }

        cout << "\nList <-- ";

        t = this->tail;

        // Percorrer a lista do final para o início.
        while (t != NULL)
        {
            cout << t->item << " ";
            t = t->prev;
        }

        cout << "\nQuantidade de elementos: "
             << this->n << endl;
    }

    /*
     * Alterar o valor armazenado em uma posição específica.
     */
    void set(int item, int pos)
    {
        // Verificar se a posição existe.
        if (pos < 0 || pos >= this->n)
        {
            cout << "Erro: indice invalido!!\n";
            return;
        }

        Node *t = this->getNode(pos);

        t->item = item;
    }
};