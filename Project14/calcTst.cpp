#include <iostream>
using namespace std;

#include "calc.h"

int main(int argc, char* argv[])
{
    Calc* C = new Calc(argv[1]);
    C->DisplayInFix();
    C->DisplayPostFix();
    cout << C->Evaluate() << endl;

    delete C;
    return 0;
}