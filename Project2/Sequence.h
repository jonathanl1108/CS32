//
//  Sequence.hpp
//  Project2
//
//  Created by Jonathan on 4/21/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#ifndef Sequence_hpp
#define Sequence_hpp

#include <stdio.h>
#include <string>
using ItemType = std::string;
//using ItemType = unsigned long;
class Sequence
{
public:
    Sequence();
    Sequence( const Sequence& other);
    Sequence& operator=( const Sequence&  other);
    ~Sequence();
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    //void dump();
private:
    struct Node
    {
        Node* next=nullptr;
        Node* previous=nullptr;
        ItemType value;
    };
    Node* head;
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
#endif /* Sequence_hpp */

