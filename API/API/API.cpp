#include <iostream>

using namespace std;

int size(string* arreglo) {
    int res = 0;
    while (arreglo[res] != "") {
        res++;
    }
    return res;
}

int main()
{
    string* a = new string[6]{"ABC","DEF","123","987"};
    cout << size(a);
    return 0;
}
