#include <iostream>
using namespace std;

#include "list.h"

// Public member functions
List::List()
{
    head = NULL;       
}

List::~List()
{
    // Empty list parameter
    if (head == NULL)
    {      
        delete head;
        return;
    }

    // Run recursion to delete nodes and then delete head
    Destructor(head);
    delete head;
}

bool List::IsEmpty()
{
    // Empty list parameter
    if (GetLength() == 0)
        return true;

    return false;
}

itemType List::GetItemH()
{
    return head->item;
}

void List::PutItemH(itemType item)
{
    // Use temp node to hold new item while pointers are moved
    node* temp = new node;
    temp->item = item;
    temp->next = head;
    head = temp;

    // Null and delete temp after use
    temp = NULL;
    delete temp;
}

void List::DeleteItemH()
{
    // Use two temporary nodes to delete item head and
    // point head to the next value in the list
    node* temp = new node;
    temp = head;

    node* nextValue = new node;
    nextValue = temp->next;
    head = nextValue;

    // null and delete temporary nodes afterwards
    temp = NULL;
    delete temp;
    nextValue = NULL;
    delete nextValue;
}

void List::Print()
{
    // Empty list parameter
    if (IsEmpty())
        return;

    // Recursion implementation
    Print(head);
}

void List::PrintRev()
{
    // Empty list parameter
    if (IsEmpty())
        return;

    // Recursion implementation
    PrintRev(head);
}

int List::GetLength()
{
    // Empty list parameter
    if (head == NULL)
        return 0;
    
    // Recursion implementation
    return GetLength(head);
}

// Private member functions
void List::Print(node* cur)
{
    cout << cur->item << endl;

    // Stopping case: once end of list reached
    if (cur->next != NULL)
        Print(cur->next);
}

void List::PrintRev(node* cur)
{
    // Stopping case: once end of list reached
    if (cur->next != NULL)
        PrintRev(cur->next);

    cout << cur->item << endl;  
}

void List::Destructor(node* cur)
{
    // Stopping case: once end of list reached
    if (cur->next != NULL)
        Destructor(cur->next);
    
    // Delete each node in the list
    DeleteItemH();
}

int List::GetLength(node* cur)
{
    // Stopping case: once end of list reached
    if (cur->next == NULL)
        return 1;
    
    // Continue adding one after each call to increase length
    return 1 + GetLength(cur->next);
}