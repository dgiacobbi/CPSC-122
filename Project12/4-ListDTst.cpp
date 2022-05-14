#include <iostream>
using namespace std;

#include "4-ListD.cpp"

//All tests are separated by function
void TestInsert();
void TestDelete();
void TestDeleteAll();
void TestPrintBackward();
void TestSort();
void TestCopyConstructor();

int main()
{
    //TestInsert();
    //TestCopyConstructor();
    //TestDelete();
    //TestDeleteAll();
    //TestSort();
    //TestPrintBackward();
}

void TestInsert()
{
    ListD<int>* lst = new ListD<int>;
    for (int i = 1; i <= 5; i++)
        lst->Insert(i,i);
    lst->PrintForward();

    //test general case insert
    cout << "Passed Insert Test 1 if 1 through 5 appear on subsequent lines" << endl;
    lst->PrintForward();
    cout << endl;

    //test insert at the head
    lst->Insert(0,1);
    cout << "Passed Insert Test 2 if 0 appears in position 1" << endl; 
    lst->PrintForward();
    cout << endl;

    //test insert at the tail 
    lst->Insert(100,7);
    cout << "Passed Insert Test 3 if 100 appears in final position" << endl; 
    lst->PrintForward();
    cout << endl;

    //test insert in middle 
    lst->Insert(50,5);
    cout << "Passed Insert Test 4 if 50 appears in middle position" << endl; 
    lst->PrintForward();
    cout << endl;
    //delete lst;
}

void TestDelete()
{
    ListD<int>* lst1 = new ListD<int>;
    for (int i = 1; i <= 8; i++)
        lst1->Insert(i,i);
    lst1->PrintForward();

    //test delete in middle
    lst1->Delete(4);
    cout << "Passed Delete Test 1 if 4 is no longer in the list" << endl;
    lst1->PrintForward();
    cout << endl;

    //test delete at head
    lst1->Delete(1);
    cout << "Passed Delete Test 2 if 1 is no longer in the list" << endl;
    lst1->PrintForward();
    cout << endl;

    //test delete at tail
    lst1->Delete(6);
    cout << "Passed Delete Test 3 if 8 is no longer in the list" << endl;
    lst1->PrintForward();
    cout << endl;
}

void TestDeleteAll()
{
    ListD<int>* lst2 = new ListD<int>;
    for (int i = 1; i <= 8; i++)
        lst2->Insert(i,i);
    lst2->PrintForward();

    //test delete in middle
    lst2->DeleteAll(4);
    cout << "Passed Delete Test 1 if 4 is no longer in the list" << endl;
    lst2->PrintForward();
    cout << endl;

    //test delete at head
    lst2->DeleteAll(1);
    cout << "Passed Delete Test 2 if 1 is no longer in the list" << endl;
    lst2->PrintForward();
    cout << endl;

    //test delete at tail
    lst2->DeleteAll(8);
    cout << "Passed Delete Test 3 if 8 is no longer in the list" << endl;
    lst2->PrintForward();
    cout << endl;
}

void TestPrintBackward()
{
    ListD<int>* lst3 = new ListD<int>;
    for (int i = 1; i <= 8; i++)
        lst3->Insert(i,i);
    lst3->PrintForward();
    cout << endl;

    cout << "Passed Print Backward Test if list prints backwards:" << endl;
    lst3->PrintBackward();
}

void TestSort()
{
    ListD<int>* lst4 = new ListD<int>;
    for (int i = 1; i <= 8; i++)
        lst4->Insert(rand() % 10, i);
    lst4->PrintForward();
    cout << endl;

    cout << "Passed Sort Test 1 if list prints from smallest to largest" << endl;
    lst4->Sort();
    lst4->PrintForward();
    cout << endl;

    ListD<int>* lst5 = new ListD<int>;
    for (int i = 1; i <= 8; i++)
        lst5->Insert(rand() % 10, i);
    lst5->PrintForward();
    cout << endl;

    cout << "Passed Sort Test 2 if list prints from smallest to largest" << endl;
    lst5->Sort();
    lst5->PrintForward();
}

void TestCopyConstructor()
{
    ListD<int>* lst1 = new ListD<int>;
    for (int i = 1; i <= 3; i++)
        lst1->Insert(i,i);

    ListD<int>* lst2(lst1);

    cout << "Traverse lst1" << endl;
    lst1->PrintForward();
    cout << endl;
    cout << "Traverse lst2" << endl;
    lst2->PrintForward();

    //delete lst1;
    //delete lst2;
}