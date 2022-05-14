#include <iostream>
using namespace std;

#include "3-ListT.h"

ListT::ListT()
{
    length = 0;
    head = NULL;
    tail = NULL;
}

ListT::~ListT()
{
    delete []head;
    delete []tail;
}

bool ListT::IsEmpty() const
{
    // If-statement checks length to determine if empty
    if (length == 0)
        return true;
    else
        return false;
}

int ListT::GetLength() const
{
    return length;
}

void ListT::PutItemH(itemType item)
{
    // Make a temporary node to hold item and assign
    // pointers so that it is the new start of list
    node* tmp = new node;
    tmp->item = item;
    tmp->next = head;
    head = tmp;

    // Condition where it is the first node 
    if (length == 0)
        tail = tmp;
        tail->next = NULL; 

    // Null out unnecessary node pointers and increase length 
    length++;
    tmp = NULL;

    // Delete unused node pointers to free up memory
    delete tmp;
}

itemType ListT::GetItemH() const
{
    // Uses head to find item and return
    itemType itemH = head->item;
    return itemH;
}

void ListT::DeleteItemH()
{
    // temporary node assigned to head
    node* temp = new node;
    temp = head;

    // nextValue node assigned to pointer on node to be deleted
    // becomes new head
    node* nextValue = new node;
    nextValue = temp->next;
    head = nextValue;

    // Null and delete unnecessary node pointers
    temp = NULL;
    nextValue = NULL;
    delete temp;
    delete nextValue;
    length--;
}

void ListT::PutItemT(const itemType itemIn)
{
    // Create two temporary nodes to insert ItemIN
    node* temp = new node;
    node* newTail = new node;
    
    temp = tail;
    tail = newTail;

    // assign the next pointer to tail
    // using the tail, insert ItemIn
    temp->next = tail;
    tail->item = itemIn;

    // Null out any unnecessary pointers and increase length
    tail->next = NULL;
    temp = NULL;
    newTail = NULL;
    length++;
    delete temp;
    delete newTail;
}

itemType ListT::GetItemT() const
{
    itemType itemT = tail->item;
    return itemT;
}

void ListT::DeleteItemT()
{
    // Create two temp nodes that traverse through to the end
    // of the list using a while loop
    node* curr = head->next;
    node* prev = head;

    while (curr != tail)
    {
        prev = curr;
        curr = curr->next;
    }

    // Assign tail the node before last node and null its next
    tail = prev;
    prev->next = NULL;
    delete curr;

    // Null out any unnecessary pointers and decrease length
    prev = NULL;
    delete prev;
    length--;
}

void ListT::Print() const
{
    // Create new node to traverse through list
    node* cur = head;

    //Print out each item in list
    while(cur != NULL)
    {
        cout << cur->item << endl;
        cur = cur->next;
    }
}

int ListT::FindItem(const itemType target) const
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
    delete temp;
    return targetNumber;
}

int ListT::DeleteItem(const itemType target)
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

    // Deal with the tail pointer parameter
    headerCheck = tail->item;
    if (headerCheck == target)
    {
        DeleteItemT();
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
            delete curr;

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

    prev = NULL;
    delete prev;
    return nodesDeleted;
}