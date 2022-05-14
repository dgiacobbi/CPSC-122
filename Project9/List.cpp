#include <iostream>
using namespace std;

#include "List.h"

//Class-related functions
//Constructor
List::List()
{       
    length = 0;
    head = NULL;
}

//Destructor
List::~List()
{
    delete []head;
}

//Head-related functions
void List::PutItemH(itemType itemIn)
{
    // Make a temporary node to hold itemIn and assign
    // pointers so that it is the new start of list
    node* temp = new node;
    temp->item = itemIn;
    temp->next = head;
    head = temp;

    // Null out unnecessary node pointers and increase length
    temp = NULL;
    length++;
}

int List::Find(const itemType target) const
{
    // Declare int to count times target is found
    // Declare temp node to traverse through list
    int targetNumber = 0;
    node* temp = new node;
    temp = head;

    // For loop checks every value in list for target
    // moves temp as it goes down the list
    for (int i = 0; i < length; i++)
    {
        itemType value = temp->item;
        if (value == target)
            targetNumber++;
        temp = temp->next;
    }

    // Null unnecessary node pointers and return targetNumber
    temp = NULL;
    return targetNumber;
}

itemType List::GetItemH() const
{
    // Uses head to find item and return
    itemType itemH = head->item;
    return itemH;
}

void List::DeleteItemH()
{
    // temporary node assigned to head
    node* temp = new node;
    temp = head;

    // nextValue node assigned to pointer on node to be deleted
    // becomes new head
    node* nextValue = new node;
    nextValue = temp->next;
    head = nextValue;

    temp = NULL;
    nextValue = NULL;
    length--;
}

//General operations on the class
int List::DeleteItem(const itemType target)
{
    // Declare int to keep track of amount of nodes deleted
    // Declare prev node to assign to head
    int nodesDeleted = 0;
    node* prev = head;

    // headerCheck is used to see if first item is target
    itemType headerCheck = prev->item;
    if (headerCheck == target)
    {
        DeleteItemH();
        nodesDeleted++;
        length--;
    }

    // For loop traverses loop checking each list element for target
    for (int i = 1; i < length; i++)
    {
        // curr and nextNode created to remove nodes with item target
        node* curr = prev->next;
        node* nextNode = curr->next;

        // value used to check if current element is the target
        itemType value = curr->item;

        if (value == target)
        {
            // Assign next to nextNode to drop current item
            prev->next = nextNode;

            // Increment count and decrement length
            nodesDeleted++;
            length--;
        }
        // If not target, keep traversing list
        else
        {
            prev = curr;
            curr = nextNode;
            nextNode = nextNode->next;
        }
            
    }

    delete []prev;
    return nodesDeleted;
}

void List::Print() const
{
    // Assign temp node to head
    node* temp = new node;
    temp = head;

    // As temp traverses list, print the item temp points to
    for (int i = 0; i < length; i++)
    {
        itemType value = temp->item;
        cout << value << endl;
        temp = temp->next;
    }

    temp = NULL;
}

bool List::IsEmpty() const
{
    // If-statement checks length to determine if empty
    if (length == 0)
        return true;
    else
        return false;
}

int List::GetLength() const
{
    return length;
}