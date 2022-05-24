//
//  Sequence.cpp
//  Homework1
//
//  Created by Jonathan on 4/13/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#include "Sequence.h"
using namespace std;
Sequence::Sequence()// Create an empty sequence (i.e., one with no items)
:m_size(0)
{}
// Return true if the sequence is empty, otherwise false.
bool Sequence::empty()const
{
    return size()==0;
}
// Return the number of items in the sequence.
int Sequence::size() const
{
    return m_size;
}

// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
int Sequence::insert(int pos, const ItemType& value)
{
    if( (pos < 0 || pos > size() ) ||  size() >= DEFAULT_MAX_ITEMS )
        return -1;
    
    // do a right shift from pos
    for( int i = size() ; i > pos ; i--)
    {
        m_sequence[i]= m_sequence[i-1];
    }
    m_sequence[pos]= value;
    m_size++;
    return pos;
}

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).

int Sequence::insert(const ItemType& value)
{
    if( size() == DEFAULT_MAX_ITEMS)
        return -1;
    
    int tgPos=size();
    for( int i=0 ; i < size() ; i++)
    {
        if( value <= m_sequence[i])
        {
            tgPos=i;
            break;
        }
    }
    insert(tgPos, value);
    return tgPos;
}

// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos)
{
    if( 0 > pos || pos > size())
        return false;
    for( int i = pos ; i < size()-1 ; i++)
    {
        m_sequence[i]=m_sequence[i+1];
    }
    m_size--;
    return true;
}

// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value)
{
    int count = 0 ;
    for(int i =0 ; i < size() ; i++)
    {
       if( erase(find(value)))
           count++;
    }
    return count;
}

// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const
{
    if( 0 > pos || pos >= size())
        return false;
    value= m_sequence[pos];
    return true;
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value)
{
    if( 0 > pos || pos >= size())
        return false;
    m_sequence[pos] = value;
    return true;
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const
{
    for( int p =0 ; p < size() ; p++)
    {
        if(m_sequence[p] == value)
            return p;
    }
    return -1;
}

// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other)
{
    int length = size();
    if( other.size() > size())
        length=other.size();
    
    int temp = other.m_size;
    other.m_size = size();
    m_size = temp;
    
    for( int i =0 ; i < length ; i++)
    {
        ItemType temp = m_sequence[i];
        m_sequence[i] = other.m_sequence[i];
        other.m_sequence[i]= temp;
    }
   
}

void Sequence::rotateRight( int pos, int size, ItemType source[])
{
    for( int i = pos ; i < size ; i++)
    {
        source[i+1]=source[i];
    }
}
void Sequence::dump() const
{
    for( int i =0 ; i < size() ; i++)
        cerr<<m_sequence[i]<<endl;
}
