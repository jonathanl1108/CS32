//
//  testSequence.cpp
//  Homework1
//
//  Created by Jonathan on 4/13/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//
//
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void testString()
{
//    Sequence s;
//    s.insert(0, "a");
//    s.insert(1, "b");
//    s.insert(2, "c");
//    s.insert(3, "b");
//    s.insert(4, "e");
//    s.insert(5, "f");
//    s.insert(6, "g");
//    //s.insert(7, "g");
//    // insertion test
//    cout<<" ++++++insertion test++++++\n\n";
//    //if 0 <= pos <= size()
//    cout<< "before insertion set size is"<<s.size()<<endl;
//    s.dump();
//    if( s.insert(s.size(), "test") == -1 )
//    cout<<"faile insetion test1"<<endl;
//    else
//    {
//        cout<<" inserted at pos == size()\n";
//        s.dump();
//        cout<<"pass capacity full with max 8 item \n";
//    }
//
//    cout<<s.size()<<endl;
//    cout<<s.insert(1, "fail1") <<endl;
//
//    if(s.insert(1, "fail1") != -1)
//    {
//        cout<<"faile insetion test2"<<endl;
//        s.dump();
//    }
//    else
//    {
//        cout<< "pass full cap insertion test1"<<endl;
//        s.dump();
//    }
//
//    if(s.insert(s.size(), "fail1") != -1)
//    {
//        cout<<"faile insetion test3"<<endl;
//        s.dump();
//    }
//    else
//    {
//        cout<< "pass full cap insertion test2"<<endl;
//        s.dump();
//    }
//    cout<<" ----- pass insertion test ------\n\n";
//    s.remove("g");
//    s.remove("f");
//    s.remove("b");
//    s.remove("test");
//    cout<<"remove all g ,f ,b size should be 3 \n";
//    assert( s.size() == 3);
//    s.dump();
//    cout<<" ----- pass remove test ------ \n";
//    cout<<" ++++++insert( value ) test++++++\n\n";
//    cout<< "where value z is max "<<endl;
//    assert( s.insert("z") == s.size()-1);
//    s.dump();
//    cout<<"\n";
//    cout<< "insert duplicate a,b,d,y "<<endl;
//    s.insert("a");
//
//    assert(s.insert( "b") == 2);
//    assert(s.insert( "d")== 4);
//    assert(s.insert("y") == s.size()-2);
//    s.dump();
//    cout<<"\n";
//
//    s.set(0, "a");
//    s.set(1, "b");
//    s.set(2, "c");
//    s.set(3, "b");
//    s.set(4, "e");
//    s.set(5, "f");
//    s.set(6, "g");
//    s.set(7, "h");
//    cout<< s.size()<<endl;
//    s.dump();
//    assert(s.set(8, "i") == false);
//    cout<< s.size()<<endl;
//    cout<<" ----- pass set test ------"<<endl;
//
//    s.erase(0);
//    assert( s.find("a") == -1);
//    s.erase(1);
//    assert(s.find("c") == -1);
//    s.dump();
//    assert(s.find("h") == 5);
//    assert(s.find("g") == 4);
//    assert(s.remove("b") == 2);
//    cout<<" ------ pass find remove erase test ------ \n";
//
//    s.set(0, "a");
//    s.set(1, "b");
//    s.set(2, "c");
//    s.set(3, "b");
//    //    s.insert(0, "a");
//    //    s.insert(1, "b");
//    //    s.insert(2, "c");
//    //    s.insert(3, "b");
//    s.insert(4, "e");
//    s.insert(5, "f");
//    s.insert(6, "g");
//    s.insert(7, "g");
//    s.dump();
//
//    ItemType value = "xxx";
//    assert(!s.get(s.size(), value) && value=="xxx");
//    assert(s.get(0, value) && value=="a");
//    assert(s.get(1, value) && value=="b");
//    assert(s.get(2, value) && value=="c");
//    assert(s.get(3, value) && value=="b");
//    assert(s.get(4, value) && value=="e");
//    assert(s.get(5, value) && value=="f");
//    assert(s.get(6, value) && value=="g");
//    assert(s.get(7, value) && value=="g");
//    assert(!s.get(8, value) && value=="g");
//    cout<<" ----- pass get test ----- \n";
//
//    while(!s.empty())
//    {
//        s.erase(0);
//        cout<<"curr size "<<s.size()<<endl;
//    }
//    assert(s.empty());
//    s.insert(0, "a");
//    s.insert(1, "b");
//    s.insert(2, "c");
//    s.insert(3, "d");
//    s.insert(4, "e");
//    s.insert(5, "f");
//    s.insert(6, "h");
//    s.insert(6, "g");
//    Sequence a;
//    a.insert("1");
//    a.insert("2");
//    a.insert("3");
//    a.insert("4");
//    a.insert("5");
//    a.insert("6");
//    a.insert("7");
//    a.insert("8");
//    cout << "+++++same size swap test+++++"<<endl;
//    cout<< "before swap s is "<<endl;
//    s.dump();
//    cout<< "before swap a is "<<endl;
//    a.dump();
//
//    s.swap(a);
//    cout<< "After swap s is "<<endl;
//    s.dump();
//    cout<< "After swap a is "<<endl;
//    a.dump();
//    assert( a.find("a") == 0);
//    assert( a.find("b") == 1);
//    assert( a.find("c") == 2);
//    assert( a.find("d") == 3);
//    assert( a.find("e") == 4);
//    assert( a.find("f") == 5);
//    assert( a.find("g") == 6);
//    assert( a.find("h") == 7);
//
//    assert(s.find("1") == 0);
//    assert(s.find("2") == 1);
//    assert(s.find("3") == 2);
//    assert(s.find("4") == 3);
//    assert(s.find("5") == 4);
//    assert(s.find("6") == 5);
//    assert(s.find("7") == 6);
//    assert(s.find("8") == 7);
//    cout << "----- pass same size swap test ----\n"<<endl;
//    cout<<" ++++++different size test++++++\n\n";
//
//    a.remove("a");
//    a.remove("b");
//    a.remove("c");
//    int abeforsize= a.size();
//    int sbeforsize= s.size();
//    cout<< "before swap s with size "<<s.size() <<endl;
//    s.dump();
//    cout<< "before swap a with size "<<a.size() <<endl;
//    a.dump();
//
//    s.swap(a);
//    cout<< "after swap s with size "<<s.size() <<endl;
//    s.dump();
//    cout<< "after swap a with size "<<a.size() <<endl;
//    a.dump();
//    assert(s.size()==abeforsize);
//    assert(a.size()==sbeforsize);
//    cout<<" ----- pass different size test -----\n\n";
//    while(!s.empty())
//    {
//        s.erase(0);
//        cout<<"curr size "<<s.size()<<endl;
//    }
//    cout<<" +++++  0 size swap test +++++\n";
//    cout<< "before swap s with size "<<s.size() <<endl;
//    s.dump();
//    cout<< "before swap a with size "<<a.size() <<endl;
//    a.dump();
//
//    s.swap(a);
//    cout<< "after swap s with size "<<s.size() <<endl;
//    s.dump();
//    cout<< "after swap a with size "<<a.size() <<endl;
//    a.dump();
//    assert(s.size()==8);
//    assert(a.size()==0);
//    cout<<" ----- pass 0 size swap test -----\n\n";
//
//    cout<<"pass all test"<<endl;

}
void testUSlong()
{
        Sequence s;
        s.insert(0, 10);
        s.insert(1, 20);
        s.insert(2, 30);
        s.insert(3, 20);
        s.insert(4, 50);
        s.insert(5, 60);
        s.insert(6, 70);
        //s.insert(7, "g");
        // insertion test
        cout<<" ++++++insertion test++++++\n\n";
        //if 0 <= pos <= size()
        cout<< "before insertion set size is"<<s.size()<<endl;
        s.dump();
        if( s.insert(s.size(), 100) == -1 )
            cout<<"faile insetion test1"<<endl;
        else
        {
            cout<<" inserted at pos == size()\n";
            s.dump();
            cout<<"pass capacity full with max 8 item \n";
        }

        cout<<s.size()<<endl;
        cout<<s.insert(1, 404) <<endl;

        if(s.insert(1, 404) != -1)
        {
            cout<<"faile insetion test2"<<endl;
            s.dump();
        }
        else
        {
            cout<< "pass full cap insertion test1"<<endl;
            s.dump();
        }

        if(s.insert(s.size(), 404) != -1)
        {
            cout<<"faile insetion test3"<<endl;
            s.dump();
        }
        else
        {
            cout<< "pass full cap insertion test2"<<endl;
            s.dump();
        }
         cout<<" ----- pass insertion test ------\n\n";
        s.remove(70);
        s.remove(60);
        s.remove(20);
        s.remove(100);
        cout<<"remove all g ,f ,b size should be 3 \n";
        assert( s.size() == 3);
        s.dump();
        cout<<" ----- pass remove test ------ \n";
        cout<<" ++++++insert( value ) test++++++\n\n";
        cout<< "where value z is max "<<endl;
        assert( s.insert(1000) == s.size()-1);
        s.dump();
        cout<<"\n";
        cout<< "insert duplicate a,b,d,y "<<endl;
        s.insert(10);

        assert(s.insert( 20) == 2);
        assert(s.insert( 40)== 4);
        assert(s.insert(999) == s.size()-2);
        s.dump();
        cout<<"\n";

        s.set(0, 10);
        s.set(1, 20);
        s.set(2, 30);
        s.set(3, 20);
        s.set(4, 50);
        s.set(5, 60);
        s.set(6, 70);
        s.set(7, 80);
        cout<< s.size()<<endl;
        s.dump();
        assert(s.set(8, 111) == false);
        cout<< s.size()<<endl;
        cout<<" ----- pass set test ------"<<endl;

        s.erase(0);
        assert( s.find(10) == -1);
        s.erase(1);
        assert(s.find(30) == -1);
        s.dump();
        assert(s.find(80) == 5);
        assert(s.find(70) == 4);
        assert(s.remove(20) == 2);
        cout<<" ------ pass find remove erase test ------ \n";

        s.set(0, 10);
        s.set(1, 20);
        s.set(2, 30);
        s.set(3, 20);
    //    s.insert(0, "a");
    //    s.insert(1, "b");
    //    s.insert(2, "c");
    //    s.insert(3, "b");
        s.insert(4, 50);
        s.insert(5, 60);
        s.insert(6, 70);
        s.insert(7, 70);
        s.dump();

        ItemType value = 777;
        assert(!s.get(s.size(), value) && value==777);
        assert(s.get(0, value) && value==10);
        assert(s.get(1, value) && value==20);
        assert(s.get(2, value) && value==30);
        assert(s.get(3, value) && value==20);
        assert(s.get(4, value) && value==50);
        assert(s.get(5, value) && value==60);
        assert(s.get(6, value) && value==70);
        assert(s.get(7, value) && value==70);
        assert(!s.get(8, value) && value==70);
        cout<<" ----- pass get test ----- \n";

        while(!s.empty())
        {
            s.erase(0);
            cout<<"curr size "<<s.size()<<endl;
        }
        assert(s.empty());
        s.insert(0, 10);
        s.insert(1, 20);
        s.insert(2, 30);
        s.insert(3, 40);
        s.insert(4, 50);
        s.insert(5, 60);
        s.insert(6, 80);
        s.insert(6, 70);
         Sequence a;
         a.insert(1);
         a.insert(2);
         a.insert(3);
         a.insert(4);
         a.insert(5);
         a.insert(6);
         a.insert(7);
         a.insert(8);
        cout << "+++++same size swap test+++++"<<endl;
        cout<< "before swap s is "<<endl;
        s.dump();
        cout<< "before swap a is "<<endl;
        a.dump();

        s.swap(a);
        cout<< "After swap s is "<<endl;
        s.dump();
        cout<< "After swap a is "<<endl;
        a.dump();
         assert( a.find(10) == 0);
         assert( a.find(20) == 1);
         assert( a.find(30) == 2);
         assert( a.find(40) == 3);
         assert( a.find(50) == 4);
         assert( a.find(60) == 5);
         assert( a.find(70) == 6);
         assert( a.find(80) == 7);

        assert(s.find(1) == 0);
        assert(s.find(2) == 1);
        assert(s.find(3) == 2);
        assert(s.find(4) == 3);
        assert(s.find(5) == 4);
        assert(s.find(6) == 5);
        assert(s.find(7) == 6);
        assert(s.find(8) == 7);
        cout << "----- pass same size swap test ----\n"<<endl;
        cout<<" ++++++different size test++++++\n\n";

        a.remove(10);
        a.remove(20);
        a.remove(30);
        int abeforsize= a.size();
        int sbeforsize= s.size();
        cout<< "before swap s with size "<<s.size() <<endl;
        s.dump();
        cout<< "before swap a with size "<<a.size() <<endl;
        a.dump();

        s.swap(a);
        cout<< "after swap s with size "<<s.size() <<endl;
        s.dump();
        cout<< "after swap a with size "<<a.size() <<endl;
        a.dump();
        assert(s.size()==abeforsize);
        assert(a.size()==sbeforsize);
        cout<<" ----- pass different size test -----\n\n";
        while(!s.empty())
        {
            s.erase(0);
            cout<<"curr size "<<s.size()<<endl;
        }
        cout<<" +++++  0 size swap test +++++\n";
        cout<< "before swap s with size "<<s.size() <<endl;
        s.dump();
        cout<< "before swap a with size "<<a.size() <<endl;
        a.dump();

        s.swap(a);
        cout<< "after swap s with size "<<s.size() <<endl;
        s.dump();
        cout<< "after swap a with size "<<a.size() <<endl;
        a.dump();
        assert(s.size()==8);
        assert(a.size()==0);
        cout<<" ----- pass 0 size swap test -----\n\n";

        cout<<"pass all test"<<endl;

}

void test()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
}

int main()
{
    test();
    //testString();
    //testUSlong();
//    Sequence s1;
//    s1.insert(0, "paratha");
//    s1.insert(0, "focaccia");
//    Sequence s2;
//    s2.insert(0, "roti");
//    s1.swap(s2);
//    assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
//           s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
    cout << "Passed all tests" << endl;
}

