//Aubrey Jenkins
//Csci271
//File:linklistv2.h
/*This program will is a doubly linked list that uses iterators so basically the list STL but my own version */
#ifndef linklistv2_h
#define linklistv2_h
#include <stddef.h>
#include <cstddef>
#include<iostream>
using namespace std;
template<class t>
class iter;

template<class t>
class Node
{
private:
t datum;//This is the item that will get stored
Node<t>* next;//This is a pointers to the Next
Node<t>* prev;//this is a pointer to the Previous
friend class iter<t>;//this make iterator a friend
public:
  // Constructors
  Node()
  {
    datum=0;
    next=NULL;
    prev=NULL;
  }
  Node(t anItem)
  {
    datum=anItem;
    next=NULL;
    prev=NULL;
  }
  Node(t anItem, Node<t> *nextNodePTR )
  {
    datum=anItem;
    next=nextNodePTR;
    prev=NULL;
  }
  Node(t anItem, Node<t> *nextNodePTR,Node<t> *previousNodePTR)
  {
    datum=anItem;
    next=nextNodePTR;
    prev=previousNodePTR;
  }
  // Set methods
  void setItem(t anItem)
  {
    datum=anItem;
  }
  void setNext(Node<t> *nextNodePTR)
  {
    next=nextNodePTR;
  }
  void setPrev(Node<t> *previousNodePTR)
  {
     prev=previousNodePTR;
  }
  // Get Methods
  Node<t>* getNext()
  {
    return next;
  }
  Node<t>* getPrev()
  {
    return prev;
  }
  t&  getItem()
  {
    return datum;
  }
};

template<class t>
class LinkedList
{
private:
Node<t>* head;//this is a pointer to head
Node<t>* tail;//this is a pointer to tail
int s;//this is the size
friend class iter<t>;
public:
  /*This is the default constructor for the Linked List*/
LinkedList()
{
  head= new Node<t>;//makes a dummy node for head
  tail= new Node<t>;//makes a dummy node for tail
  head->setNext(tail);//sets heads next to tail
  tail->setPrev(head);//sets tails previous to head
  head->setPrev(head);//sets head previous to head
  tail->setNext(tail);//sets tails next to tail
  s=0;//sets size equal to zero
}
/*This is the copy constructor for the Linked List*/
LinkedList(const LinkedList<t> &L)
{
  //constructs the new node again
  head= new Node<t>;
  tail= new Node<t>;
  head->setNext(tail);
  tail->setPrev(head);
  head->setPrev(head);
  tail->setNext(tail);
  s=0;
  //=----------------------------------
  Node<t>* temp;//delcares a temp node
  temp=L.head->getNext();//sets temp node to first item in list
  while(temp!=L.tail)
  {
    push_back(temp->getItem());//puts the items from the second list into the first
    temp=temp->getNext();
  }
}
/*This is the deconstructor is called when the program ends*/
~LinkedList()
{
  clear();
  delete head;
  delete tail;
}
/* This function is called to push things to the front of the list*/
void push_front(t item)
{
  Node<t>* temp=new Node<t>;//creates a pointer to a new nod that is being created
  temp->setNext(head->getNext());//sets temp's next to heads next
  head->getNext()->setPrev(temp);//sets head's next's previous to temp
  head->setNext(temp);//sets heads next to temporary pointer
  temp->setPrev(head);//sets temps previous to head
  temp->setItem(item);//sets the items for temp
  s++;//increments size
}
//pushes the items into the back of the list
void push_back(t item)
{

    Node<t>* temp= new Node<t>;
    temp->setPrev(tail->getPrev());//sets temp's previous to tails previous
    tail->getPrev()->setNext(temp);//sets tail's previous' next to temp
    tail->setPrev(temp);//sets tails previous to temp
    temp->setNext(tail);//sets temps next to tail
    temp->setItem(item);//sets the item
    s++;//increment
}
//removes the first item in the list aznd deletes it to free up space
void pop_front()
{
  if(empty()==true)
  {
    return;
  }
  Node<t>* temp;
  temp=head->getNext();
  head->setNext(head->getNext()->getNext());
  head->getNext()->setPrev(head);
  delete temp;
  s--;
}
//remove the last item from the list and deletes it to free up space
void pop_back()
{
  if(empty()==true)
  {
    return;
  }
  Node<t>* temp;
  temp=tail->getPrev();
  tail->setPrev(tail->getPrev()->getPrev());
  tail->getPrev()->setNext(tail);
  delete temp;
  s--;
}
//clears the function
void clear()
{
  while(s!=0)
  {
    pop_front();
  }
}
//erases the items that the iterator is currently pointing to
void erase(iter<t> itt)
{
   Node<t>* temp;
   temp=itt.cur;
   temp->getNext()->setPrev(temp->getPrev());
   temp->getPrev()->setNext(temp->getNext());
   delete temp;
   s--;
}
//this function returns the reference to the first item in the list
t& front()
{
  return head->getNext()->getItem();
}
//returns a reference to the last item in the list
t& back()
{
  return tail->getPrev()->getItem();
}
//returns an iterator to the front of the list
iter<t> begin()
{
  iter<t> ir;
  ir.cur=head->getNext();
  return ir;
}
//returns a iterator to the item after the last
iter<t> end()
{
  iter<t> ir;
  ir.cur=tail->getNext();
  return ir;
}
//overloads the equal operator so that it can be used with the list class
void operator=(const LinkedList<t>& L)
{
  //constructs the new node again
  head= new Node<t>;
  tail= new Node<t>;
  head->setNext(tail);
  tail->setPrev(head);
  head->setPrev(head);
  tail->setNext(tail);
  s=0;
  //=----------------------------------
  Node<t>* temp;//delcares a temp node
  temp=L.head->getNext();//sets temp node to first item in list
  while(temp!=L.tail)
  {
    push_back(temp->getItem());//puts the items from the second list into the first
    temp=temp->getNext();
  }
}
// this is empty function
bool empty()
{
  return(head->getNext()==tail);//returns true if the heads next equal to next
}
//return ths size of the list
int size()
{
  return s;//return size
}

};
template<class t>

class iter
{
private:
Node<t>* cur;
public:
  friend class LinkedList<t>;
//this is the pre increment function for iterator looks like ++it
iter& operator++()
{
  cur=cur->next;//sets the iterator equal to its Next
  return *this;//returns what the current iteratro is at
}
//this is the post increment looks like it++
iter operator++(int)
{
  iter<t> temp;//makes a temporary iterator
  temp=*this;//sets it equal to the current
  cur=cur->next;//sets the iterator equal to its Next
  return temp;//returns the item before it was incremented
}
/*This is the pre decrement of the iterator looks like --it*/
iter& operator--()
{
  cur=cur->prev;//sets the iterator to it's previous
  return *this;
}
//this is the post decrement looks like it--
iter operator--(int)
{
  iter<t> temp;//makes a temporary iterator
  temp=*this;//sets it equal to the current
  cur=cur->prev;//sets the iterator equal to its previous
  return temp;//returns the item before it was incremented
}
/*This overload the dereference operator so that it can be used with an iterator*/
t operator*()
{
return cur->datum;//returns the item that is stored
}
bool operator!=(iter it)
{
  return cur!=it.cur;//basically says if the current item is equal to the iterator passed then return false else return true
}
bool operator==(iter it)
{
  return cur==it.cur;//basically says if the current item is equal to the iterator passed then return true else return false
}
};
#endif
