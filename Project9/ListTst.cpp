#include <iostream>
using namespace std;

#include "List.h"

int main()
{
    //Static list 
    List lst;

    for (int i = 0; i < 5; i++)
        lst.PutItemH(i);
    
    lst.Print();
    cout << endl;
    cout << "List Length: " << lst.GetLength() << endl;
    cout << endl;

    lst.DeleteItemH();

    lst.Print();
    cout << endl;

    cout << "Instances of 3: " << lst.Find(3) << endl;
    cout << "List Length: " << lst.GetLength() << endl;
    cout << "Item at Head: " << lst.GetItemH() << endl;
    cout << lst.DeleteItem(2) << endl;
    lst.Print();
    cout << endl << endl;

    //Dynamic list 
    List* lst1 = new List;
    for (int i = 0; i < 5; i++)
        lst1->PutItemH(10*i);
    
    lst1->Print();
    cout << endl;
    cout << "List Length: " << lst1->GetLength() << endl;
    cout << endl;

    lst1->DeleteItemH();

    lst1->Print();
    cout << endl;

    cout << "Instances of 3: " << lst1->Find(3) << endl;
    cout << "List Length: " << lst1->GetLength() << endl;
    cout << "Item at Head: " << lst1->GetItemH() << endl;
    cout << lst1->DeleteItem(20) << endl;
    lst1->Print();
    cout << endl << endl;

    delete lst1; //necessary to invoke destructor on dynamic list
    return 0;
}