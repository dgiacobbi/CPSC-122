#include <iostream>
#include <climits>
using namespace std;

#include "4-ListD.h"

template <typename T>
ListD<T>::ListD()
{
    InitializeVars();
}

template <typename T>
ListD<T>::ListD(ListD<T>* lst)
{
    InitializeVars();

    //returns a pointer to the first node, which is what we want here
    doubleNode<T>* cur = lst->FindPosition(2);
    for (int i = 1; i <= lst->length; i++)
    {
        cout << cur->item << endl;
        Insert(cur->item,i);
        cur = cur->next;
    }
}

template <typename T>
void ListD<T>::InitializeVars()
{
    length = 0;

    //create dummy nodes;
    head = new doubleNode<T>;
    tail = new doubleNode<T>;

    //set values for head dummy node;
    head->prev = NULL;
    head->item = INT_MIN;
    head->next = tail;

    //set values for tail dummy node;
    tail->prev = head; 
    tail->item = INT_MAX;
    tail->next = NULL;
}

template <typename T>
ListD<T>::~ListD()
{
    delete []head;
    delete []tail;
}

template <typename T>
doubleNode<T>* ListD<T>::FindPosition(int pos)
{
    //Inserting at the tail is a special case.
    //It can be made much more efficient than this.
    doubleNode<T>* cur = head;

    int i = 0;  //begin at the dummy node
    while (i < pos - 1)
    {
        cur = cur->next;
        i++;
    }
    return cur;
} 

template <typename T>
void ListD<T>::Insert(T itemIn, int pos)
{
    //new node goes between these two nodes
    doubleNode<T>* insertPtA = FindPosition(pos);  
    doubleNode<T>* insertPtB = insertPtA->next; 

    //create new node and set its values
    doubleNode<T>* tmp = new doubleNode<T>; 
    tmp->prev = insertPtA;
    tmp->item = itemIn;
    tmp->next = insertPtB;

    //set pointers for nodes before and after the insertion point
    insertPtA->next = tmp;
    insertPtB->prev = tmp;

    length++;
}

template <typename T>
void ListD<T>::Delete(int pos)
{
    //If-statement deals with the delete tail parameter
    if (pos == length)
    {
        //declare pointers to the node before and the node to be deleted
        doubleNode<T>* prevNode = FindPosition(pos);
        doubleNode<T>* delNode = prevNode->next;

        //delete the node and assign the tail to the previous node
        delete delNode;
        prevNode->next = NULL;
        tail = prevNode;

        //null out and delete any unnecessary pointers
        prevNode = NULL;
        delete prevNode;
    }
    //Else statement deals with head and middle parameters
    else
    {
        //declare pointers to node to be deleted and before
        doubleNode<T>* prevNode = FindPosition(pos);
        doubleNode<T>* delNode = prevNode->next;
        doubleNode<T>* postNode = delNode->next;

        //delete node and assign prev pointer to post node
        prevNode->next = postNode;
        postNode->prev = prevNode;
        delete delNode;

        //null out and delete any unnecessary pointers
        prevNode = NULL;
        postNode = NULL;
        delete prevNode;
        delete postNode;
    }

    //decrease length
    length--;
}

template <typename T>
int ListD<T>::DeleteAll(T itemIn)
{
    //Initialize variables to traverse nodes to check target
    int nodesDel = 0;
    doubleNode<T>* prevNode = head;
    doubleNode<T>* boundCheck = new doubleNode<T>;

    //If-statement checks head parameter
    boundCheck = head->next;
    if (boundCheck->item == itemIn)
    {
        Delete(1);
        nodesDel++;
    }

    //If-statement checks tail parameter
    boundCheck = tail->prev;
    if (boundCheck->item == itemIn)
    {
        Delete(length);
        nodesDel++;
    }

    //For loop traverses list for middle parameter
    for (int i = 1; i < length; i++)
    {
        //Initialize variables to traverse
        doubleNode<T>* curNode = prevNode->next;
        doubleNode<T>* nextNode = curNode->next;

        //If-statement deletes node if equal to item that needs to be deleted
        if (curNode->item == itemIn)
        {
            delete curNode;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;

            nodesDel++;
            length--;
        }
        //If current node is not equal to itemIn, continue list traverse
        else
        {
            prevNode = curNode;
            curNode = nextNode;
            nextNode = nextNode->next;
        }
    }

    //Null and delete any unnecessary nodes
    prevNode = NULL;
    delete prevNode;

    return nodesDel;
}

template <typename T>
void ListD<T>::PrintForward()
{
    //Node used to traverse list for printing
    doubleNode<T>*  cur = head->next;

    int i = 0;
    while (i < length)
    {
        cout << cur->item << endl;
        cur = cur->next;
        i++;
    }
}

template <typename T>
void ListD<T>::PrintBackward()
{
    //Node used to traverse list starting at tail
    doubleNode<T>* cur = tail->prev;
    
    //Print each node item through traverse
    for (int i = length; i > 0; i--)
    {
        cout << cur->item << endl;
        cur = cur->prev;
    }
}

template <typename T>
void ListD<T>::Sort()
{
    //Initialize variables to selection sort nodes
    int pass = 0;
    int start = 1;
    doubleNode<T>* smallNode = new doubleNode<T>;

    //While loop passes through loop to find smallest node and swap
    while (start < length)
    {
        //Anytime smaller node value is found, it is swapped to the top
        smallNode = findSmall(start);
        Swap(start, smallNode);
        start++;
        pass++;
    }
}

template <typename T>
doubleNode<T>* ListD<T>::findSmall(int start)
{
    //Initialize variables to traverse list from starting point
    int next = start + 1;
    doubleNode<T>* smallNode = FindPosition(start + 1);
    doubleNode<T>* nextNode = smallNode->next;

    //Go through list from start position and check each node item
    //to see if it is smaller than current node
    while (next < length + 1)
    {
        //If-statement assigns smallNode the current node being checked if smaller
        if (nextNode->item < smallNode->item)
            smallNode = nextNode;
        nextNode = nextNode->next;
        next++;
    }
    return smallNode;
}

template <typename T>
void ListD<T>::Swap(int pos, doubleNode<T>* smallNode)
{
    //Pointers used to find items needed to swap
    doubleNode<T>* swapNode = FindPosition(pos + 1);
    doubleNode<T>* temp = new doubleNode<T>;

    //Temp swap used to switch item values in the two nodes
    temp->item = swapNode->item;
    swapNode->item = smallNode->item;
    smallNode->item = temp->item;

    //Null and delete any unnecessary nodes
    temp = NULL;
    delete temp;
}