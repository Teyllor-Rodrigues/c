#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    vector<int>numeros_a ,numeros_b;

    ifstream a, b;
    a.open("run1.txt");
    b.open("run2.txt");
    int i = 0;
    int x, y;
    while(!a && !b)
    {
        a >> x;
        numeros_a.push_back(x);

        b >> y;
        numeros_b.push_back(y);
        cout << i << endl;
        i++;
    }

   cout << "tamnho " << numeros_a.size() ;
    numeros_b.size();

    // ofstream saida;
    // saida.open("saida.txt");

    // if (!a || !b || !saida)
    // {
    //     cout << "Erro ao tentar acessar o arquivo !!" << endl;
    //     return 1;
    // }

    // int x, y;

    // bool tem_x = (bool)(a >> x);
    // bool tem_y = (bool)(b >> y);

    // while (tem_x && tem_y)
    // {
    //     if (x <= y)
    //     {
    //         saida << x << endl;
    //         tem_x = (bool)(a >> x);
    //     }
    //     else
    //     {
    //         saida << y << endl;
    //         tem_y = (bool)(b >> y);
    //     }
    // }

    // while (tem_x)
    // {
    //     saida << x << endl;
    //     tem_x = (bool)(a >> x);
    // }

    // while (tem_y)
    // {
    //     saida << y << endl;
    //     tem_y = (bool)(b >> y);
    // }

    // saida.close();
}