//
//  Sequence.cpp
//  Project2
//
//  Created by Jonathan on 4/21/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence()
{
    // creates an empty linklist
    head=nullptr;
    m_size=0;
}
Sequence::Sequence( const Sequence&  other)
{
    
    head =nullptr;
    m_size =0;
    // copy everything
    Node *p = other.head;
    int pos=0;
    while( p != nullptr)
    {
        ItemType value;
        other.get(pos,value);
        insert(pos, value);
        pos++;
        p=p->next;
    }
}
Sequence& Sequence::operator=( const Sequence&  other)
{
    // first check if copying itself
    if( this != &other)
    {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}
Sequence::~Sequence()
{
    Node* p = head;
    if( head == nullptr)
        return;
    // traverse down
    while( p != nullptr)
    {
        Node* newHead = p->next;
        delete p;
        m_size--;
        p = newHead;
    }
}
bool Sequence::empty() const
{
    return (head==nullptr && size() == 0);
}
int Sequence::size() const
{
    return m_size;
}
int Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos > size())
        return -1;
    
    // valid position allocate a new Node
    // can't get wrong from now
    Node* newNode = new Node;
    newNode->value = value;

    // case 1 where linklist is empty
    if( head == nullptr) // addtoFront
    {
        head=newNode;
    }else if( pos == 0 ) // to be more effienct
    {
        newNode->next= head;
        newNode->previous = nullptr;
        head->previous=newNode;
        head=newNode;
    }else if( pos == size())// addtorear
    {
        Node* p = head;
        while( p->next != nullptr)
            p=p->next;
        newNode->next=nullptr;
        newNode->previous=p;
        p->next=newNode;
    }else{ //add to middle
        // travers down to the pos
        Node*p =head;
        for( int i =0 ; i < pos ; i++)
        {
            if(p != nullptr)
                p = p->next;
        }
        // found the positon
        if( p != nullptr) // never access p wihout checking
        {
            newNode->next = p;
            newNode->previous=p->previous;
            p->previous->next=newNode;
            p->previous = newNode;
        }
        
    }
    m_size++;
    return pos;
}
int Sequence::insert(const ItemType& value)
{
    // travers to find the right pos
    Node* temp = head;
    int pos=0;
    while( temp != nullptr)
    {
        if( temp->value >= value)
            break;
        pos++;
        temp=temp->next;
    }
    insert( pos , value);
    return pos;
}
bool Sequence::erase(int pos)
{
    if (pos < 0  ||  pos >= size())
        return false;
    Node* p = head;
    if(head == nullptr)
        return false;
    else if( pos == 0)
    {
         Node* killme = head;
         head= killme->next;
        delete killme;
    }
    else
    {
        for( int i =0 ; i < pos ; i++)
            p = p->next;
        // gets to pos of delete node
        //cout<<"killing pos "<<pos<<endl;
        Node* killme = p;
        killme->previous->next = killme->next;
        killme->next->previous = killme->previous;
        delete killme;
    }
    m_size--;
    return true;
}
int Sequence::remove(const ItemType& value)
{
    int count = 0 ;
//    for(int i =0 ; i < size() ; i++)
//    {
//        if( erase(find(value)))
//            count++;
//    }
    while( erase(find(value)))
    {
        count++;
    }
    return count;
}
bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0  ||  pos >= size())
        return false;
    Node* p =head;
    int counter =0 ;
    while( p!= nullptr)
    {
        if( counter == pos)
            break;
        p=p->next;
        counter++;
    }
    if( p != nullptr && counter == pos)
    {
        value = p->value;
        return true;
    }else
        return false; // there might be some bad things happenning
}
bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos >= size())
        return false;
    Node* p =head;
    int counter =0 ;
    while( p!= nullptr)
    {
        if( counter == pos)
            break;
        p=p->next;
        counter++;
    }
    if( p != nullptr && counter == pos)
    {
        p->value = value;
        return true;
    }else
        return false; // there might be some bad things happenning
}
int Sequence::find(const ItemType& value) const
{
    Node* p = head;
    for( int pos = 0 ; pos < size() ; pos++)
    {
        if( p != nullptr && (p->value == value))
            return pos;
        p = p ->next;
    }
    return -1;
}
void Sequence::swap(Sequence& other)
{
    // this is easy becuase
    // we can simply exchange the head of each list
    Node* temp = other.head;
    other.head = head;
    head= temp;

    int tempSize = other.size();
    other.m_size = size();
    m_size = tempSize;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    // get the frist elemet in seq2
    if( !seq2.empty() && (seq2.size()  <= seq1.size()))
    {
        // get the first element of seq2
        ItemType value;
        seq2.get(0, value);
        // find the first pos in seq1 of this vlaue
        int startexam = seq1.find(value);
        if(startexam == -1 )
            return -1;
        for( int i = startexam ; i < seq1.size(); i++)
        {
            bool foundSeq = true;
            ItemType e1, e2;
            // for each possible
            for( int j = 0 ; j < seq2.size() ; j++)
            {
                seq1.get(i+j, e1);
                seq2.get(j, e2);
                if( e1 != e2)
                {
                    foundSeq=false;
                    break;
                }
            }
            if( foundSeq)
            {
                return i;

            }
        }
    }
    return -1;
}
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    int size1 = seq1.size();
    int size2 = seq2.size();
    while( !result.empty())
    {
        result.erase(0);
    }
    if( size1 || size2)
    {
        int length= size1;
        if( (size2-size1 ) > 0) // size2>size1
            length=size2;
        int start=0;
        for( int i =0 ; i < length ;i++)
        {
            ItemType value;
            if(seq1.get(i, value)){
                result.insert(start, value);
                start++;
            }
            if(seq2.get(i, value)){
                result.insert(start, value);
                start++;
            }
        }
    }
}

//void Sequence:: dump()
//{
//    Node* p = head;
//    while( p != nullptr)
//    {
//        cerr<< p->value<<", ";
//        p=p->next;
//    }
//    cerr<<"\n";
//}


