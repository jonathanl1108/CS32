//
//  testnewSequence.cpp
//  Homework1
//
//  Created by Jonathan on 4/14/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

////#include <stdio.h>
////#include <iostream>
////#include "newSequence.h"
////using namespace std;
////int main()
////{
//////    Sequence a(1000);   // a can hold at most 1000 items
//////    Sequence b(5);      // b can hold at most 5 items
//////    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
//////    ItemType v = 5000;
//////
//////    // No failures inserting 5 items into b
//////    for (int k = 0; k < 5; k++)
//////        assert(b.insert(v) != -1);
//////    b.dump();
//////    cout<<b.insert(v)<<endl;
//////    // Failure if we try to insert a sixth item into b
//////    assert(b.insert(v) == -1);
//////
//////    // When two Sequences' contents are swapped, their capacities are
//////    // swapped as well:
//////    a.swap(b);
//////
//////    cout<<"b size "<<b.size();
//////    cout<<b.max()<<endl;
//////    cout<<"a size "<<a.size();
//////    cout<<a.max()<<endl;
//////    cout<<"ll "<<b.insert(v)<<endl;
//////    assert(a.insert(v) == -1  &&  b.insert(v) != -1);
////
////
////    cout<<"pass all test"<<endl;
////}
//
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

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
//        cout<<"faile insetion test1"<<endl;
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
//    cout<<"size: "<< s.size()<<endl;
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
//
//    cout<<" +++++ copy constructor test +++++\n\n";
//
//    Sequence A;
//    A.insert(0, "jonathan");
//    assert(A.insert(2, "jonathan") == -1);
//    A.insert(1, "kevin");
//    A.insert("jammy");
//    A.insert( "katherine");
//    A.insert( "andy");
//    A.insert( "ban");
//    A.insert("family");
//    A.dump();
//    assert(A.size() == 7);
//    A.insert(A.size(), "last");
//    //assert(A.size() == A.max());
//    assert(A.insert("bad me ") == -1);
//    cout<< "construct B with A B(A)"<<endl;
//    Sequence B(A);
//    B.dump();
//    assert(B.size() == A.size());
//    //assert(B.max() == A.max());
//    cout<< "construct C with A C=A"<<endl;
//    Sequence C= A;
//    C.dump();
//    assert(C.size() == A.size());
//    //assert(C.max() == A.max());
//    cout<<" ----- pass copy constructor test -----\n\n";
//    cout<<" +++++ Assignment Operator test +++++\n\n";
//    assert(C.remove("first") == 0) ;
//    assert(C.remove("jonathan") == 1) ;
//    assert(C.remove("andy") == 1) ;
//    while( !C.empty())
//    {
//        C.erase(0);
//    }
//    assert( C.empty());
//    string valueT="xxxxx";
//    assert(!C.get(0, valueT));
//    assert( valueT == "xxxxx");
//    C.insert("11");
//    C.insert("11");
//    C.insert("12");
//    C.insert("13");
//    C.insert("14");
//    assert(C.insert("11") == 0);
//    C.dump();
//    //cout<<"c size "<<C.insert("14");
//    assert( C.insert("14")== C.size()-2);
//    assert(C.insert("15") == C.size()-1);
//    assert(C.insert("15") == -1);
//    assert(C.get(0, valueT) && valueT =="11");
//    assert(C.get(C.size()-1, valueT) && valueT =="15");
//
//    cout<<"Before Assingment opt c is : ";
//    C.dump();
//    cout<<"Before Assingment opt a is : ";
//    A.dump();
//    A=C;
//    cout<<"After Assingment opt c is : ";
//    C.dump();
//    cout<<"After Assingment opt a is : ";
//    A.dump();
//    cout<<"================= some sawp test=================\n";
//    cout<< "Before Swap A and B, A is ";
//    A.dump();
//    cout<< "Before Swap A and B, B is ";
//    B.dump();
//
//    B.swap(A);
//    cout<< "After Swap A and B, A is ";
//    A.dump();
//    cout<< "After Swap A and B, B is ";
//    B.dump();
//
//    string vB="BBB", vC="CCC";
//    assert( B.find("11") == C.find("11"));
//    assert( B.find("13") == C.find("13"));
//    assert( B.find("15") == C.find("15"));
//    for( int i =0 ; i < C.size() ; i++)
//        assert( B.get(i, vB) && C.get(i, vC) && vB==vC);
//    assert( !B.get(B.size(), vB));
//    assert( !B.get(-1, vB) );
//    cout<<" ++++++ Set Test +++++\n";
//
//    assert(B.set( 0, "AB"));
//    assert(B.set( 1, "CD"));
//    assert(B.set( 2, "EF"));
//    assert(B.set( 4, "GH"));
//    assert(B.set( 5, "GH"));
//    assert(B.set( 6, "GH"));
//    assert(B.set( 7, "ZX"));
//    assert(!B.set( B.size(), "XXXXX"));
//    assert(!B.set( -1, "XXXXXX"));
//    B.dump();
//    assert( B.find("11") != C.find("11"));
//    assert( B.find("13") != C.find("13"));
//    assert( B.find("15") != C.find("15"));
//    assert(B.remove("GH") == 3);
//    assert(B.size() == 8-3);
//    B.dump();
//
//    cout<<" Assign B to A "<<endl;
//    cout<<" A was : ";
//    A.dump();
//    cout<<" B was : ";
//    B.dump();
//
//    A=B;
//
//    cout<<" A is : ";
//    A.dump();
//    cout<<" B is : ";
//    B.dump();
//    for( int i =0 ; i < B.size() ; i++)
//        assert( B.get(i, vB) && A.get(i, vC) && vB==vC);
//    assert(!B.erase(C.size()));
//    assert(!B.erase(-1));
//    assert(B.remove("11") == 0);
//    assert(B.remove("12") == 1);
//    assert(A.remove("11") == 0);
//    assert(A.remove("12") == 1);
//    cout<< "After removing 11 and 12 "<<endl;
//    A.dump();
//    B.dump();
//    cout<<" ----- Pass Assignment Operator test -----\n\n";
//    cout << "Passed all tests" << endl;
    
}
void testUSlong()
{
     //THIS TEST IS FOR UNSIGNED LONG TYPE AND UESES
     //   DEFAULT_MAX_SIZE OF 8
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
    
    
            cout<<" +++++ copy constructor test +++++\n\n";
    
            Sequence A;
            A.insert(0, 111);
            assert(A.insert(2, 111) == -1);
            A.insert(1, 51);
            A.insert(110);
            A.insert( 50);
            A.insert( 10);
            A.insert( 20);
            A.insert(30);
            A.dump();
            assert(A.size() == 7);
            A.insert(A.size(), 999);
            //assert(A.size() == A.max());
            assert(A.insert(404) == -1);
            cout<< "construct B with A B(A)"<<endl;
            Sequence B(A);
            B.dump();
            assert(B.size() == A.size());
            //assert(B.max() == A.max());
            cout<< "construct C with A C=A"<<endl;
            Sequence C= A;
            C.dump();
            assert(C.size() == A.size());
            //assert(C.max() == A.max());
            cout<<" ----- pass copy constructor test -----\n\n";
            cout<<" +++++ Assignment Operator test +++++\n\n";
            assert(C.remove(1) == 0) ;
            assert(C.remove(111) == 1) ;
            assert(C.remove(10) == 1) ;
            while( !C.empty())
            {
                C.erase(0);
            }
            assert( C.empty());
            ItemType valueT=777;
            assert(!C.get(0, valueT));
            assert( valueT == 777);
            C.insert(11);
            C.insert(11);
            C.insert(12);
            C.insert(13);
            C.insert(14);
            assert(C.insert(11) == 0);
            C.dump();
            //cout<<"c size "<<C.insert("14");
            assert( C.insert(14)== C.size()-2);
            assert(C.insert(15) == C.size()-1);
            assert(C.insert(15) == -1);
            assert(C.get(0, valueT) && valueT ==11);
            assert(C.get(C.size()-1, valueT) && valueT ==15);
    
            cout<<"Before Assingment opt c is : ";
            C.dump();
            cout<<"Before Assingment opt a is : ";
            A.dump();
            A=C;
            cout<<"After Assingment opt c is : ";
            C.dump();
            cout<<"After Assingment opt a is : ";
            A.dump();
            cout<<"================= some sawp test=================\n";
            cout<< "Before Swap A and B, A is ";
            A.dump();
            cout<< "Before Swap A and B, B is ";
            B.dump();
    
            B.swap(A);
            cout<< "After Swap A and B, A is ";
            A.dump();
            cout<< "After Swap A and B, B is ";
            B.dump();
    
            ItemType vB=222, vC=333;
            assert( B.find(11) == C.find(11));
            assert( B.find(13) == C.find(13));
            assert( B.find(15) == C.find(15));
            for( int i =0 ; i < C.size() ; i++)
                assert( B.get(i, vB) && C.get(i, vC) && vB==vC);
            assert( !B.get(B.size(), vB));
            assert( !B.get(-1, vB) );
            cout<<" ++++++ Set Test +++++\n";
    
            assert(B.set( 0, 55));
            assert(B.set( 1, 66));
            assert(B.set( 2, 77));
            assert(B.set( 4, 88));
            assert(B.set( 5, 88));
            assert(B.set( 6, 88));
            assert(B.set( 7, 99));
            assert(!B.set( B.size(), 4444));
            assert(!B.set( -1, 4444));
            B.dump();
            assert( B.find(11) != C.find(11));
            assert( B.find(13) != C.find(13));
            assert( B.find(15) != C.find(15));
            assert(B.remove(88) == 3);
            assert(B.size() == 8-3);
            B.dump();
    
            cout<<" Assign B to A "<<endl;
            cout<<" A was : ";
            A.dump();
            cout<<" B was : ";
            B.dump();
    
            A=B;
    
            cout<<" A is : ";
            A.dump();
            cout<<" B is : ";
            B.dump();
            for( int i =0 ; i < B.size() ; i++)
                assert( B.get(i, vB) && A.get(i, vC) && vB==vC);
            assert(!B.erase(C.size()));
            assert(!B.erase(-1));
            assert(B.remove(11) == 0);
            assert(B.remove(12) == 1);
            assert(A.remove(11) == 0);
            assert(A.remove(12) == 1);
            cout<< "After removing 11 and 12 "<<endl;
            A.dump();
            B.dump();
            cout<<" ----- Pass Assignment Operator test -----\n\n";
            cout << "Passed all tests" << endl;
    
}
int main()
{
    test();
    //testUSlong();
    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 5000;
    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v+10*k) != -1);
    b.dump();
    cout<<b.insert(v)<<endl;
    // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    
    cout<<"b size "<<b.size()<<endl;;
    cout<<"a size "<<a.size()<<endl;
    assert(b.insert(v)==0);
    assert(a.insert(v) == -1  &&  b.insert(v) != -1);
    cout<<"pass all test"<<endl;
}

