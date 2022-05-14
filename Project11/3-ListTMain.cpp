#include <iostream>
using namespace std;

#include "3-ListT.h"

int main()
{
    // STATIC LIST TESTING
    cout << endl << "**********STATIC TESTING**********" << endl;
    ListT lst;

    // PutItemH and Print testing
    for (int i = 0; i < 8; i++)
        lst.PutItemH(i);
    lst.Print();
    cout << endl;    

    // GetLength testing
    cout << "List Length: " << lst.GetLength() << endl;
    cout << endl;

    // DeleteItemH testing
    cout << "Deleted Item Head:" << endl;
    lst.DeleteItemH();
    lst.Print();
    cout << endl;

    // FindItem test
    cout << "Instances of 3: " << lst.FindItem(3) << endl;

    // GetLength test
    cout << "List Length: " << lst.GetLength() << endl;

    // GetItemH test
    cout << "Item at Head: " << lst.GetItemH() << endl << endl;

    // DeleteItem test
    cout << "Delete Item test (2):" << endl;
    cout << "Instances of Item Deleted: " << lst.DeleteItem(2) << endl;
    lst.Print();
    cout << endl;

    // DeleteItem tail test
    cout << "Delete Item tail (0)" << endl;
    lst.DeleteItem(0);
    lst.Print();
    cout << endl;

    // PutItemT and GetItemH test
    lst.PutItemT(88);
    cout << "Item at Tail: " << lst.GetItemT() << endl;
    lst.Print();
    cout << endl;

    // DeleteItemT test
    cout << "Deleted Item Tail:" << endl;
    lst.DeleteItemT();
    lst.Print();
    cout << endl;

    // DYNAMIC LIST TESTING
    cout << "**********DYNAMIC TESTING**********" << endl;
    ListT* lst1 = new ListT;

    // PutItemH and Print testing
    for (int i = 0; i < 8; i++)
        lst1->PutItemH(10*i);
    lst1->Print();
    cout << endl;

    // GetLength testing
    cout << "List Length: " << lst1->GetLength() << endl;
    cout << endl;

    // DeleteItemH testing
    cout << "Deleted Item Head:" << endl;
    lst1->DeleteItemH();
    lst1->Print();
    cout << endl;

    // FindItem test
    cout << "Instances of 30: " << lst1->FindItem(30) << endl;

    // GetLength test
    cout << "List Length: " << lst1->GetLength() << endl;

    // GetItemH test
    cout << "Item at Head: " << lst1->GetItemH() << endl << endl;

    // DeleteItem test
    cout << "Delete Item test (20):" << endl;
    cout << "Instances of Item Deleted: " << lst1->DeleteItem(20) << endl;
    lst1->Print();
    cout << endl;

    // DeleteItem tail test
    cout << "Delete Item tail (0)" << endl;
    lst1->DeleteItem(0);
    lst1->Print();
    cout << endl;

    // PutItemT and GetItemH test
    lst1->PutItemT(88);
    cout << "Item at Tail: " << lst1->GetItemT() << endl;
    lst1->Print();
    cout << endl;

    // DeleteItemT test
    cout << "Deleted Item Tail:" << endl;
    lst1->DeleteItemT();
    lst1->Print();
    cout << endl;

    delete lst1; //necessary to invoke destructor on dynamic list
    return 0;
}