//
//  BSTTREE.cpp
//  Project4
//
//  Created by Jonathan on 6/5/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
struct record
{
    // hold my pattern
    string m_pattern;
    int count=0;
    // hold my offset
    int m_offset;
    vector<int>otSet;
    // remember my parent
    record* leftchild;
    record* rightchild;
    int getCount()
    {
        return count;
    }
};
class BSTtree
{
public:
    BSTtree();
    ~BSTtree();
    int search( string substring, record& returnNode);
    void insert( string substring, int offset);
    void inorderprint();

private:
    void deleteTree( record* head );
    void insert( string sub, int offset,record* node);
    int search( string sub, record& returnNode,record*node);
    void inorderprint(record * node);
    record* root;
};


BSTtree::BSTtree()
{
    root = nullptr;
}
BSTtree::~BSTtree()
{
    deleteTree(root);
}
void BSTtree::deleteTree(record* head)
{
    if( head == nullptr)
        return;
    // kill left child
    deleteTree( head->leftchild);
    deleteTree( head->rightchild);
    // kill my self
    delete head;
}
void BSTtree::insert(string substring, int offset, record* root )
{
    // the root
    {
        // so we have a root
        // compare keys
        if( substring > root->m_pattern )
        {
            // goes to right child
            if( root->rightchild == nullptr)
            {
                root->rightchild = new record;
                //set value
                root->rightchild->m_pattern = substring;
                root->rightchild->m_offset = offset;
                root->rightchild->otSet.push_back(offset);
                root->rightchild->count++;
                root->rightchild->leftchild=nullptr;
                root->rightchild->rightchild=nullptr;
                
            }
            else
                insert( substring, offset, root->rightchild);
        }else if( substring < root->m_pattern )
        {
            //goes to left child
            if( root->leftchild == nullptr)
            {
                root->leftchild = new record;
                //set value
                root->leftchild->m_pattern = substring;
                root->leftchild->m_offset = offset;
                root->leftchild->otSet.push_back(offset);
                root->leftchild->count++;
                root->leftchild->leftchild=nullptr;
                root->leftchild->rightchild=nullptr;
            }
            else
                insert( substring, offset, root->leftchild);
        }else
        {
            root->count++;
            root->otSet.push_back(offset);
        }
    }
}
void BSTtree::insert(string substring, int offset)
{
    if( root == nullptr)
    {
        root = new record;
        //set value
        root->m_pattern = substring;
        root->m_offset = offset;
        root->otSet.push_back(offset);
        root->count++;
        root->leftchild=nullptr;
        root->rightchild=nullptr;
    }else
        insert( substring, offset, root);
}

int BSTtree::search( string substring, record& returnNode,record* node)
{
    if( node == nullptr)
        return -1;
    if( substring == node->m_pattern)
    {
        returnNode = *node;
        return node->m_offset;
    }
    else if( substring > node->m_pattern)
    {
        return search(substring, returnNode, node->rightchild);
    }else
        return search(substring, returnNode, node->leftchild);

}

int BSTtree::search( string substring, record& returnNode)
{
    return search(substring,returnNode, root);
}

void BSTtree::inorderprint()
{
    inorderprint(root);
}

void BSTtree::inorderprint(record * node){
    if(node != NULL){
        inorderprint(node->leftchild);
        cout << node->m_pattern << ",";
        cout<< node->m_offset<<endl;
        inorderprint(node->rightchild);
    }
}

//int main(int argc, const char * argv[])
//{
//    BSTtree *tree = new BSTtree();
//    tree->insert("j",1);
//    tree->insert("k",2);
//    tree->insert("a",3);
//    tree->insert("b",4);
//    tree->insert("z",5);
//    tree->insert("i",6);
//    tree->insert("j",7);
//    tree->inorderprint();
//    record returnNode;
//    cout<<tree->search("a",returnNode );
//    cout<<returnNode.m_pattern<<endl;
//    delete tree;
//}






