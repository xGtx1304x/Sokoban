#include <iostream>
#include "ListaGrid.h"

using namespace std;

int main()
{
    string* nivel = new string[10]{
        "##########",
        "#   @    #",
        "#        #",
        "# .      #",
        "#        #",
        "#      ! #",
        "#        #",
        "##########"
    };
    ListaGrid a(nivel);
    cout << a.toString() << endl;
    return 0;
}
