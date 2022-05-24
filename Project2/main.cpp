#include "Sequence.h"
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Sequence>::value,
              "Sequence must be default-constructible.");
static_assert(std::is_copy_constructible<Sequence>::value,
              "Sequence must be copy-constructible.");
static_assert(std::is_copy_assignable<Sequence>::value,
              "Sequence must be assignable.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Sequence::empty,      bool (Sequence::*)() const);
    CHECKTYPE(&Sequence::size,       int  (Sequence::*)() const);
    CHECKTYPE(&Sequence::insert,     int (Sequence::*)(int, const ItemType&));
    CHECKTYPE(&Sequence::insert,     int (Sequence::*)(const ItemType&));
    CHECKTYPE(&Sequence::erase,      bool (Sequence::*)(int));
    CHECKTYPE(&Sequence::remove,     int  (Sequence::*)(const ItemType&));
    CHECKTYPE(&Sequence::get,     bool (Sequence::*)(int, ItemType&) const);
    CHECKTYPE(&Sequence::set,     bool (Sequence::*)(int, const ItemType&));
    CHECKTYPE(&Sequence::find,       int  (Sequence::*)(const ItemType&) const);
    CHECKTYPE(&Sequence::swap,       void (Sequence::*)(Sequence&));
    CHECKTYPE(subsequence, int  (*)(const Sequence&, const Sequence&));
    CHECKTYPE(interleave,  void (*)(const Sequence&, const Sequence&, Sequence&));
}
#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
   // thisFunctionWillNeverBeCalled();
    Sequence s;
    assert(s.insert(0, "lavash") == 0);
    assert(s.insert(0, "tortilla") == 0);
    assert(s.size() == 2);
    ItemType x = "injera";
    assert(s.get(0, x)  &&  x == "tortilla");
    assert(s.get(1, x)  &&  x == "lavash");
}
void testString()
{
    Sequence s;
    s.insert(0, "a");
    s.insert(1, "b");
    s.insert(2, "c");
    s.insert(3, "b");
    s.insert(4, "e");
    s.insert(5, "f");
    s.insert(6, "g");
    assert( s.insert(s.size(),"LAST") == s.size()-1);
    s.insert(1, "b1");
    s.insert(2, "c2");
    s.insert(5, "c2");
    s.insert(0, "FIRST");
    cout<<" ++++++insertion test++++++\n\n";
    assert( s.insert(-1, "BAD") == -1);
    assert( s.insert(s.size()+1, "BAD") == -1);
    //if 0 <= pos <= size()
    assert( s.size() == 12);
    cout<<" ----- pass insertion test ------\n\n";
    cout<<"rm g "<<s.remove("g")<<endl;
    cout<<"rm f "<<s.remove("f")<<endl;
    cout<<"rm b "<<s.remove("b")<<endl;
    s.dump();
    //cout<<s.size()<<endl;
    cout<<"remove all g ,f ,b size should be 3 \n";
    assert( s.size() == 8);
    s.dump();
    s.remove("c2");
    assert( s.size() == 12-6);
    cout<<" ----- pass remove test ------ \n";
    cout<<" ++++++insert( value ) test++++++\n\n";
    cout<< "where value z is max "<<endl;
//    cout<<s.insert("z")<<endl;
//    s.dump();
//     cout<<s.size()<<endl;
    assert( s.insert("z") == s.size()-1);
    s.dump();
    cout<<"\n";
    cout<< "insert duplicate a,b,d,y "<<endl;
    assert(s.insert("a") == 1);
    
    assert(s.insert( "b") == 3);
    assert(s.insert( "d")== 6);
    assert(s.insert("y") == s.size()-2);
    s.dump();
    cout<<"\n";
    
    s.set(0, "a");
    s.set(1, "b");
    s.set(2, "c");
    s.set(3, "b");
    s.set(4, "e");
    s.set(5, "f");
    s.set(6, "g");
    s.set(7, "h");
    cout<<"size: "<< s.size()<<endl;
    assert(s.set(s.size(), "iiii") == false);
    assert(s.set(-1, "iiii") == false);
    assert(s.set(s.size()-3, "x") == true);
    cout<< s.size()<<endl;
    cout<<" ----- pass set test ------"<<endl;
    s.dump();
    
    s.erase(0);
    assert( s.find("a") == -1);
    s.erase(1);
    assert(s.find("c") == -1);
    s.dump();
    assert(s.find("h") == 5);
    assert(s.find("g") == 4);
    assert(s.remove("b") == 2);
    cout<<" ------ pass find remove erase test ------ \n";
    
    s.set(0, "a");
    s.set(1, "b");
    s.set(2, "c");
    s.set(3, "b");
    //    s.insert(0, "a");
    //    s.insert(1, "b");
    //    s.insert(2, "c");
    //    s.insert(3, "b");
    s.insert(4, "e");
    s.insert(5, "f");
    s.insert(6, "g");
    s.insert(7, "g");
    s.dump();
    
    ItemType value = "xxx";
    assert(!s.get(s.size(), value) && value=="xxx");
    assert(s.get(0, value) && value=="a");
    assert(s.get(1, value) && value=="b");
    assert(s.get(2, value) && value=="c");
    assert(s.get(3, value) && value=="b");
    assert(s.get(4, value) && value=="e");
    assert(s.get(5, value) && value=="f");
    assert(s.get(6, value) && value=="g");
    assert(s.get(7, value) && value=="g");
    assert(s.get(8, value) && value=="x");
     assert(s.get(9, value) && value=="y");
     assert(s.get(10, value) && value=="z");
    assert(!s.get(11, value) && value=="z");
    cout<<" ----- pass get test ----- \n";
    
    while(!s.empty())
    {
        s.erase(0);
        cout<<"curr size "<<s.size()<<endl;
    }
    assert(s.empty());
    s.insert(0, "a");
    s.insert(1, "b");
    s.insert(2, "c");
    s.insert(3, "d");
    s.insert(4, "e");
    s.insert(5, "f");
    s.insert(6, "h");
    s.insert(6, "g");
    Sequence a;
    a.insert("1");
    a.insert("2");
    a.insert("3");
    a.insert("4");
    a.insert("5");
    a.insert("6");
    a.insert("7");
    a.insert("8");
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
    assert( a.find("a") == 0);
    assert( a.find("b") == 1);
    assert( a.find("c") == 2);
    assert( a.find("d") == 3);
    assert( a.find("e") == 4);
    assert( a.find("f") == 5);
    assert( a.find("g") == 6);
    assert( a.find("h") == 7);
    
    assert(s.find("1") == 0);
    assert(s.find("2") == 1);
    assert(s.find("3") == 2);
    assert(s.find("4") == 3);
    assert(s.find("5") == 4);
    assert(s.find("6") == 5);
    assert(s.find("7") == 6);
    assert(s.find("8") == 7);
    cout << "----- pass same size swap test ----\n"<<endl;
    cout<<" ++++++different size test++++++\n\n";
    
    a.remove("a");
    a.remove("b");
    a.remove("c");
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
    A.insert(0, "jonathan");
    assert(A.insert(2, "jonathan") == -1);
    A.insert(1, "kevin");
    A.insert("jammy");
    A.insert( "katherine");
    A.insert( "andy");
    A.insert( "ban");
    A.insert("family");
    A.dump();
    assert(A.size() == 7);
    //A.insert(A.size(), "last");
    cout<< "construct B with A B(A)"<<endl;
    Sequence B(A);
    B.dump();
    cout<<"bs "<<B.size()<<endl;
    assert(B.size() == A.size());
    //assert(B.max() == A.max());
    cout<< "construct C with A C=A"<<endl;
    Sequence C= A;
    C.dump();
    assert(C.size() == A.size());
    //assert(C.max() == A.max());
    cout<<" ----- pass copy constructor test -----\n\n";
    cout<<" +++++ Assignment Operator test +++++\n\n";
    assert(C.remove("first") == 0) ;
    assert(C.remove("jonathan") == 1) ;
    assert(C.remove("andy") == 1) ;
    while( !C.empty())
    {
        C.erase(0);
    }
    assert( C.empty());
    string valueT="xxxxx";
    assert(!C.get(0, valueT));
    assert( valueT == "xxxxx");
    C.insert("11");
    C.insert("11");
    C.insert("12");
    C.insert("13");
    C.insert("14");
    assert(C.insert("11") == 0);
    C.dump();
    //cout<<"c size "<<C.insert("14");
    assert( C.insert("14")== C.size()-2);
    assert(C.insert("15") == C.size()-1);
    assert(C.insert("15") == C.size()-2);
    assert(C.get(0, valueT) && valueT =="11");
    assert(C.get(C.size()-1, valueT) && valueT =="15");
    
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
    
    string vB="BBB", vC="CCC";
    assert( B.find("11") == C.find("11"));
    assert( B.find("13") == C.find("13"));
    assert( B.find("15") == C.find("15"));
    for( int i =0 ; i < C.size() ; i++)
        assert( B.get(i, vB) && C.get(i, vC) && vB==vC);
    assert( !B.get(B.size(), vB));
    assert( !B.get(-1, vB) );
    cout<<" ++++++ Set Test +++++\n";
    cout<<B.size()<<endl;
    B.dump();
    assert(B.set( 0, "AB"));
    assert(B.set( 1, "CD"));
    assert(B.set( 2, "EF"));
    assert(B.set( 4, "GH"));
    assert(B.set( 5, "GH"));
    assert(B.set( 6, "GH"));
    assert(B.set( 7, "ZX"));
    assert(!B.set( B.size(), "XXXXX"));
    assert(!B.set( -1, "XXXXXX"));
    
    assert( B.find("11") != C.find("11"));
    assert( B.find("13") != C.find("13"));
    assert( B.find("15") != C.find("15"));
    //cout<<B.remove("GH") <<endl;
    assert(B.remove("GH") == 3);
    assert(B.size() == 9-3);
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
    assert(B.remove("11") == 0);
    assert(B.remove("12") == 1);
    assert(A.remove("11") == 0);
    assert(A.remove("12") == 1);
    cout<< "After removing 11 and 12 "<<endl;
    A.dump();
    B.dump();
    cout<<" ----- Pass Assignment Operator test -----\n\n";
    cout<<"+++++++++++ subsequence test +++++++++++"<<endl;
    assert(subsequence(A, B) == 0);
    assert(subsequence(C, B) == -1);
    assert(subsequence(A, C) == -1);
    Sequence s1;
    s1.insert(0, "30");
    s1.insert(1, "21");
    s1.insert(2, "63");
    s1.insert(3, "42");
    s1.insert(4, "17");
    s1.insert(5, "63");
    s1.insert(6, "17");
    s1.insert(7, "29");
    s1.insert(8, "8");
    s1.insert(9, "32");
    
    Sequence s2;
    s2.insert(0, "63");
    s2.insert(1, "17");
    s2.insert(2, "29");
    //cout<<subsequence(s1, s2)<<endl;
    assert(subsequence(s1, s2) == 5);
   
    s2.set(0, "17");
    s2.set(1, "63");
    s2.set(2, "29");
    assert(subsequence(s1, s2) == -1);
    
    while( !s2.empty())
        s2.erase(0);
    assert(subsequence(s1, s2) == -1);
    
    Sequence c,d;
    
    c.insert(0, "1");
    c.insert(1, "2");
    c.insert(2, "3");
    c.insert(3, "2");
    c.insert(4, "1");
    c.insert(5, "2");
    c.insert(6, "3");
    c.insert(7, "4");
    c.insert(8, "1");
    c.insert(9, "2");
    c.insert(10, "3");
    c.insert(11, "4");
    
    d.insert(0, "1");
     d.insert(1, "2");
     d.insert(2, "3");
     d.insert(3, "4");
    
    assert(subsequence(c, d) ==  4);
    assert(subsequence(c, s2) ==  -1);
    
    
    
    
   
    
    cout<<" ----- Pass subsequence test -----\n\n";
    cout<<"+++++++++++ same size interleave test +++++++++++"<<endl;
    
    s2.insert(0, "30a");
    s2.insert(1, "21a");
    s2.insert(2, "63a");
    s2.insert(3, "42a");
    s2.insert(4, "17a");
    s2.insert(5, "63a");
    s2.insert(6, "17a");
    s2.insert(7, "29a");
    s2.insert(8, "8a");
    s2.insert(9, "32a");
    
    Sequence res;
    res.insert(0, "a");
    res.insert(1, "b");
    res.insert(2, "c");
    
    interleave(s1, s2, res);
    int count = 0;
    s1.dump();
    s2.dump();
    res.dump();
    for( int i =0 ; i < (s1.size()+s2.size()) ; i+=2)
    {
        ItemType v1,v2, v3;
        s1.get(count, v1) ;
        s2.get(count, v2);
        count++;
        assert( res.get(i, v3) && v3==v1  );
        assert( res.get(i+1, v3) && v3==v2 );
    }
    
    cout<<"+++++++++++ diff size interleave test +++++++++++"<<endl;
    
    s2.erase(6);
    s2.erase(5);
    s2.erase(4);
    s2.erase(3);
    interleave(s1, s2, res);
    assert(res.size() == ( s1.size() + s2.size()));
    s1.dump();
    s2.dump();
    res.dump();
    
    cout<<"+++++++++++ s1 empty size interleave test +++++++++++"<<endl;
    Sequence empty1;
    cout<< "before interleave res is "<<endl;
    res.dump();
    interleave(empty1, s2, res);
    assert(res.size() == s2.size());
    for( int i =0 ; i < s2.size(); i++)
    {
        ItemType v2, v3;
       // s1.get(count, v1) ;
        s2.get(i, v2);
        //assert( res.get(i, v3) && v3==v1  );
        assert( res.get(i, v3) && v3==v2 );
    }
     cout<< "\nafter interleave res is "<<endl;
     res.dump();
    cout<<"\n\n+++++++++++ s2 empty size interleave test +++++++++++"<<endl;
    cout<< "\nbefore interleave res is "<<endl;
    res.dump();
    interleave(s1, empty1, res);
    assert(res.size() == s1.size());
    for( int i =0 ; i < s1.size(); i++)
    {
        ItemType v1, v3;
        // s1.get(count, v1) ;
        s1.get(i, v1);
        //assert( res.get(i, v3) && v3==v1  );
        assert( res.get(i, v3) && v3==v1 );
    }
    cout<< "\nafter interleave res is "<<endl;
    res.dump();
    
    cout<<"+++++++++++ s1 and s2 empty interleave test +++++++++++"<<endl;
    Sequence empty2;
    cout<< "\nbefore interleave res is "<<endl;
    res.dump();
    interleave(empty1, empty2, res);
    assert(res.size() == 0 && res.empty());
    cout<< "\nafter interleave res is "<<endl;
    res.dump();
    cout<<"------- pass interleave test ------"<<endl;
    //cout << "Passed all tests" << endl;

}
Project 2 Test Data

When the following program is compiled along with Sequence.cpp, it can be run with input 1 through 112 to test your solution. (This program uses some features of C++ we're not covering, but that's irrelevant to you.) Each test case was worth 75/112 points.

To be able to keep track of how many nodes you created and deleted, we devised a simple class that acted like an int, but kept track of how many objects of that class were in existence at any time. We called this class OurType. We adjusted your ItemType type alias so that your Sequence stored objects of this type (and we inserted #include "OurType.h" in your Sequence.h file). (This test harness uses some C++ features we're not covering, but that should be irrelevant to you.)
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            =========================== OurType.h ==============================
#ifndef OURTYPE_INCLUDED
#define OURTYPE_INCLUDED
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            struct OurType
{
    explicit OurType(int v = 0) : m_value(v) { m_count++; }
    OurType(const OurType& other) : m_value(other.m_value)
    { m_count++; m_asstcopycount++; }
    ~OurType() { m_count--; }
    OurType& operator=(const OurType& rhs)
    { m_value = rhs.m_value; m_asstcopycount++; return *this; }
    
    int m_value;
    static int m_count;
    static int m_asstcopycount;
};
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline
                                                                                                                                                                                                                                                                                                                                                                                            bool operator==(const OurType& lhs, const OurType& rhs)
{ return lhs.m_value == rhs.m_value; }
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline
                                                                                                                                                                                                                                                                                                                                                                                            bool operator<(const OurType& lhs, const OurType& rhs)
{ return lhs.m_value < rhs.m_value; }
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline
                                                                                                                                                                                                                                                                                                                                                                                            bool operator!=(const OurType& lhs, const OurType& rhs)
{ return ! (lhs == rhs); }
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline
                                                                                                                                                                                                                                                                                                                                                                                            bool operator<=(const OurType& lhs, const OurType& rhs)
{ return ! (rhs < lhs); }
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline
                                                                                                                                                                                                                                                                                                                                                                                            bool operator>=(const OurType& lhs, const OurType& rhs)
{ return ! (lhs < rhs); }
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline
                                                                                                                                                                                                                                                                                                                                                                                            bool operator>(const OurType& lhs, const OurType& rhs)
{ return rhs < lhs; }
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline
                                                                                                                                                                                                                                                                                                                                                                                            bool operator==(const OurType& lhs, int rhs)
{ return lhs.m_value == rhs; }
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline
                                                                                                                                                                                                                                                                                                                                                                                            bool operator!=(const OurType& lhs, int rhs)
{ return ! (lhs == rhs); }
                                                                                                                                                                                                                                                                                                                                                                                            
#include <iostream>
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline
                                                                                                                                                                                                                                                                                                                                                                                            std::ostream& operator<<(std::ostream& lhs, const OurType& rhs)
{ return lhs << rhs.m_value; }
                                                                                                                                                                                                                                                                                                                                                                                            
#endif // OURTYPE_INCLUDED
                                                                                                                                                                                                                                                                                                                                                                                            =========================== tester.cpp ==============================
#include "OurType.h"
#include "Sequence.h"
#include <iostream>
#include <cstdlib>
#include <type_traits>
#include <cassert>
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            using namespace std;
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            int OurType::m_count = 0;
                                                                                                                                                                                                                                                                                                                                                                                            int OurType::m_asstcopycount = 0;
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline int itemcount()
{
    return OurType::m_count;
}
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            inline int nasstcopys()
{
    return OurType::m_asstcopycount;
}
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            ItemType SOMEVAL = ItemType(123);
                                                                                                                                                                                                                                                                                                                                                                                            ItemType DEFAULT = ItemType(0);
                                                                                                                                                                                                                                                                                                                                                                                            ItemType ARRAY[6] = {
                                                                                                                                                                                                                                                                                                                                                                                                ItemType(10), ItemType(20), ItemType(30),
                                                                                                                                                                                                                                                                                                                                                                                                ItemType(40), ItemType(50), ItemType(60),
                                                                                                                                                                                                                                                                                                                                                                                            };
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            void testone(int n)
{
    Sequence s;
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            assert((is_same<decltype(&Sequence::empty), bool (Sequence::*)() const>::value));
        } break; case  2: {
            assert((is_same<decltype(&Sequence::size), int (Sequence::*)() const>::value));
        } break; case  3: {
            assert((is_same<decltype(&Sequence::get), bool (Sequence::*)(int, ItemType&) const>::value));
        } break; case  4: {
            assert((is_same<decltype(&Sequence::find), int (Sequence::*)(const ItemType&) const>::value));
        } break; case  5: {
            assert(s.empty());
        } break; case  6: {
            assert(s.size() == 0);
        } break; case  7: {
            assert(!s.erase(0)  &&  s.size() == 0);
        } break; case  8: {
            assert(s.remove(DEFAULT) == 0  &&  s.size() == 0);
        } break; case  9: {
            ItemType x = SOMEVAL;
            assert(!s.get(0, x));
        } break; case 10: {
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 11: {
            assert(!s.set(0, SOMEVAL)  &&  s.size() == 0);
        } break; case 12: {
            assert(s.find(DEFAULT) == -1);
        } break; case 13: {
            assert(s.insert(0, SOMEVAL) == 0);
        } break; case 14: {
            s.insert(0, SOMEVAL);
            assert(! s.empty());
        } break; case 15: {
            s.insert(0, SOMEVAL);
            assert(s.size() == 1);
        } break; case 16: {
            s.insert(0, SOMEVAL);
            assert(s.find(SOMEVAL) == 0);
        } break; case 17: {
            s.insert(0, SOMEVAL);
            ItemType x = DEFAULT;
            assert(s.get(0, x));
        } break; case 18: {
            s.insert(0, SOMEVAL);
            ItemType x = DEFAULT;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 19: {
            s.insert(0, SOMEVAL);
            assert(s.set(0, DEFAULT));
        } break; case 20: {
            s.insert(0, SOMEVAL);
            s.set(0, DEFAULT);
            assert(s.size() == 1);
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == DEFAULT);
        } break; case 21: {
            s.insert(0, DEFAULT);
            s.set(0, SOMEVAL);
            assert(s.size() == 1);
            ItemType x = DEFAULT;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 22: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            assert(! s.empty()   &&  s.size() == 2);
        } break; case 23: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 24: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            ItemType x = SOMEVAL;
            s.get(1, x);
            assert(x == ARRAY[1]);
        } break; case 25: {
            s.insert(0, ARRAY[0]);
            s.insert(0, ARRAY[1]);
            assert(s.size() == 2);
        } break; case 26: {
            s.insert(0, ARRAY[0]);
            s.insert(0, ARRAY[1]);
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == ARRAY[1]);
        } break; case 27: {
            s.insert(0, ARRAY[0]);
            s.insert(0, ARRAY[1]);
            ItemType x = SOMEVAL;
            s.get(1, x);
            assert(x == ARRAY[0]);
        } break; case 28: {
            s.insert(0, ARRAY[3]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[0]);
            s.insert(0, ARRAY[4]);
            s.insert(2, ARRAY[2]);
            assert(s.size() == 5);
        } break; case 29: {
            s.insert(0, ARRAY[3]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[0]);
            s.insert(0, ARRAY[4]);
            s.insert(2, ARRAY[2]);
            for (size_t k = 0; k < 5; k++)
            {
                ItemType x = SOMEVAL;
                s.get(k, x);
                assert(x == ARRAY[5-1-k]);
            }
        } break; case 30: {
            s.insert(0, ARRAY[3]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[0]);
            s.insert(3, ARRAY[4]);
            s.insert(4, ARRAY[2]);
            for (size_t k = 0; k < 5; k++)
                s.set(k, ARRAY[k]);
            assert(s.size() == 5);
            for (size_t k = 0; k < 5; k++)
            {
                ItemType x = SOMEVAL;
                s.get(k, x);
                assert(x == ARRAY[k]);
            }
        } break; case 31: {
            assert(s.insert(SOMEVAL) == 0);
        } break; case 32: {
            s.insert(SOMEVAL);
            assert(! s.empty());
        } break; case 33: {
            s.insert(SOMEVAL);
            assert(s.size() == 1);
        } break; case 34: {
            s.insert(SOMEVAL);
            assert(s.find(SOMEVAL) == 0);
        } break; case 35: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            assert(! s.empty()   &&  s.size() == 2);
        } break; case 36: {
            s.insert(SOMEVAL);
            ItemType x = DEFAULT;
            assert(s.get(0, x));
        } break; case 37: {
            s.insert(SOMEVAL);
            ItemType x = DEFAULT;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 38: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 39: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            ItemType x = SOMEVAL;
            s.get(1, x);
            assert(x == ARRAY[1]);
        } break; case 40: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 41: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x = SOMEVAL;
            s.get(1, x);
            assert(x == ARRAY[1]);
        } break; case 42: {
            assert(s.insert(ARRAY[3]) == 0);
            assert(s.insert(ARRAY[1]) == 0);
            assert(s.insert(ARRAY[0]) == 0);
            assert(s.insert(ARRAY[4]) == 3);
            assert(s.insert(ARRAY[2]) == 2);
            assert(s.size() == 5);
        } break; case 43: {
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[4]);
            s.insert(ARRAY[2]);
            for (size_t k = 0; k < 5; k++)
            {
                ItemType x = SOMEVAL;
                s.get(k, x);
                assert(x == ARRAY[k]);
            }
        } break; case 44: {
            assert(s.insert(ARRAY[2]) == 0);
            assert(s.insert(ARRAY[1]) == 0);
            assert(s.insert(ARRAY[0]) == 0);
            assert(s.insert(ARRAY[1]) == 1);
            assert(s.insert(ARRAY[1]) == 1);
            assert(s.size() == 5);
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == ARRAY[0]);
            s.get(4, x);
            assert(x == ARRAY[2]);
            for (size_t k = 1; k < 4; k++)
            {
                x = SOMEVAL;
                s.get(k, x);
                assert(x == ARRAY[1]);
            }
        } break; case 45: {
            assert(s.insert(1, SOMEVAL) == -1  &&  s.size() == 0);
        } break; case 46: {
            assert(s.insert(-1, SOMEVAL) == -1  &&  s.size() == 0);
        } break; case 47: {
            s.insert(0, SOMEVAL);
            assert(s.insert(2, SOMEVAL) == -1  &&  s.size() == 1);
        } break; case 48: {
            s.insert(0, SOMEVAL);
            assert(! s.erase(1)  &&  s.size() == 1);
        } break; case 49: {
            s.insert(0, SOMEVAL);
            assert(s.erase(0)  &&  s.size() == 0);
        } break; case 50: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            assert(s.erase(4)  &&  s.size() == 4);
        } break; case 51: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            s.erase(4);
            ItemType x;
            s.get(3, x);
            assert(x == ARRAY[3]);
        } break; case 52: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            assert(s.erase(1)  &&  s.size() == 4);
        } break; case 53: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            s.erase(1);
            ItemType x;
            s.get(0, x);
            assert(x == ARRAY[0]);
            for (size_t k = 1; k < 4; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[k+1]);
            }
        } break; case 54: {
            s.insert(0, SOMEVAL);
            assert(s.remove(SOMEVAL) == 1);
        } break; case 55: {
            s.insert(0, SOMEVAL);
            s.remove(SOMEVAL);
            assert(s.size() == 0);
        } break; case 56: {
            s.insert(0, ARRAY[0]);
            assert(s.remove(ARRAY[1]) == 0);
        } break; case 57: {
            s.insert(0, ARRAY[0]);
            s.remove(ARRAY[1]);
            assert(s.size() == 1);
        } break; case 58: {
            s.insert(0, ARRAY[4]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[1]);
            s.insert(4, ARRAY[0]);
            s.remove(ARRAY[2]);
            ItemType x;
            for (size_t k = 0; k < 2; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[5-1-k]);
            }
            for (size_t k = 2; k < 4; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[5-2-k]);
            }
        } break; case 59: {
            s.insert(0, ARRAY[4]);
            s.insert(1, ARRAY[2]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            s.insert(4, ARRAY[2]);
            s.insert(5, ARRAY[2]);
            assert(s.remove(ARRAY[2]) == 4);
        } break; case 60: {
            s.insert(0, ARRAY[4]);
            s.insert(1, ARRAY[2]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            s.insert(4, ARRAY[2]);
            s.insert(5, ARRAY[2]);
            s.remove(ARRAY[2]);
            assert(s.size() == 2);
        } break; case 61: {
            s.insert(0, ARRAY[4]);
            s.insert(1, ARRAY[2]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            s.insert(4, ARRAY[2]);
            s.insert(5, ARRAY[2]);
            s.remove(ARRAY[2]);
            ItemType x;
            for (size_t k = 0; k < 2; k++)
            {
                x = ARRAY[0];
                s.get(k, x);
                assert(x == ARRAY[4]);
            }
        } break; case 62: {
            s.insert(0, ARRAY[2]);
            s.insert(1, ARRAY[2]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[2]);
            s.insert(4, ARRAY[2]);
            s.remove(ARRAY[2]);
            assert(s.size() == 0);
        } break; case 63: {
            s.insert(0, SOMEVAL);
            s.insert(1, SOMEVAL);
            s.insert(2, SOMEVAL);
            ItemType x;
            assert(! s.get(-1, x));
        } break; case 64: {
            s.insert(0, SOMEVAL);
            s.insert(1, SOMEVAL);
            s.insert(2, SOMEVAL);
            ItemType x = ARRAY[1];
            s.get(-1, x);
            assert(x == ARRAY[1]);
        } break; case 65: {
            s.insert(0, SOMEVAL);
            s.insert(1, SOMEVAL);
            s.insert(2, SOMEVAL);
            ItemType x;
            assert(! s.get(3, x));
        } break; case 66: {
            s.insert(0, SOMEVAL);
            s.insert(1, SOMEVAL);
            s.insert(2, SOMEVAL);
            ItemType x = ARRAY[1];
            s.get(3, x);
            assert(x == ARRAY[1]);
        } break; case 67: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            assert(! s.set(-1, ARRAY[3]));
        } break; case 68: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.set(-1, ARRAY[3]);
            assert(s.size() == 3);
            for (size_t k = 0; k < 3; k++)
            {
                ItemType x = SOMEVAL;
                assert(s.get(k, x)  &&  x == ARRAY[k]);
            }
        } break; case 69: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            assert(! s.set(3, ARRAY[3]));
        } break; case 70: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.set(-1, ARRAY[3]);
            assert(s.size() == 3);
            for (size_t k = 0; k < 3; k++)
            {
                ItemType x = SOMEVAL;
                assert(s.get(k, x)  &&  x == ARRAY[k]);
            }
        } break; case 71: {
            s.insert(SOMEVAL);
            assert(s.find(DEFAULT) == -1);
        } break; case 72: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            assert(s.find(ARRAY[4]) == 1);
        } break; case 73: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            assert(s.find(ARRAY[3]) == -1);
        } break; case 74: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2;
                s2.insert(0, ARRAY[3]);
                s2.insert(1, ARRAY[4]);
                s.swap(s2);
                assert(s.size() == 2  &&  s2.size() == 3);
            }
        } break; case 75: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2;
                s2.insert(0, ARRAY[3]);
                s2.insert(1, ARRAY[4]);
                s.swap(s2);
                ItemType x;
                assert(s.get(0, x)  &&  x == ARRAY[3]);
                assert(s.get(1, x)  &&  x == ARRAY[4]);
                assert(s2.get(0, x)  &&  x == ARRAY[0]);
                assert(s2.get(1, x)  &&  x == ARRAY[1]);
                assert(s2.get(2, x)  &&  x == ARRAY[2]);
            }
        } break; case 76: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            {
                Sequence s2;
                s2.insert(0, ARRAY[3]);
                s2.insert(1, ARRAY[4]);
                s2.insert(2, ARRAY[0]);
                int n = nasstcopys();
                s.swap(s2);
                int n2 = nasstcopys();
                assert(n2 >= n  &&  n2 <= n+3);  // swapping head nodes OK
            }
        } break; case 77: {
            const size_t BIG = 600;
            for (size_t k = 0; k < BIG; k++)
                assert(s.insert(SOMEVAL) != -1);
            assert(s.size() == BIG);
            for (size_t k = 0; k < BIG; k++)
            {
                ItemType x = DEFAULT;
                s.get(k, x);
                assert(x == SOMEVAL);
            }
        } break; case 78: {
            int before = itemcount();
            {
                Sequence s2;
                s2.insert(0, SOMEVAL);
                assert(itemcount() > before);
            }
            assert(itemcount() == before);
        } break; case 79: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(0, ARRAY[2]);
                s2.insert(2, ARRAY[3]);
                s2.insert(1, ARRAY[2]);
                s2.erase(0);
                s2.remove(ARRAY[2]);
                s2.insert(0, ARRAY[4]);
                s2.insert(s2.size(), ARRAY[4]);
                s2.remove(ARRAY[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 80: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(0, ARRAY[2]);
                s2.insert(2, ARRAY[3]);
                s2.insert(1, ARRAY[2]);
                Sequence s3(s2);
                s3.insert(0, ARRAY[1]);
                s3.insert(0, ARRAY[2]);
                s3.insert(2, ARRAY[3]);
                s3.insert(1, ARRAY[2]);
                s3.erase(0);
                s3.remove(ARRAY[2]);
                s3.insert(0, ARRAY[4]);
                s3.insert(s3.size(), ARRAY[4]);
                s3.remove(ARRAY[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 81: {
            int before = itemcount();
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                int mid = itemcount();
                Sequence s3(s2);
                assert(s3.size() == 3);
                assert(itemcount() - mid == mid - before);
            }
            assert(itemcount() == before);
        } break; case 82: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2(s);
                s2.insert(3, ARRAY[3]);
                assert(s2.size() == s.size()+1);
            }
        } break; case 83: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2(s);
                s2.insert(0, ARRAY[3]);
                ItemType x;
                assert(s2.get(0, x)  &&  x == ARRAY[3]);
                assert(s2.get(1, x)  &&  x == ARRAY[0]);
                assert(s2.get(2, x)  &&  x == ARRAY[1]);
                assert(s2.get(3, x)  &&  x == ARRAY[2]);
            }
        } break; case 84: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2(s);
                s2.insert(0, ARRAY[3]);
                ItemType x;
                assert(s.get(0, x)  &&  x == ARRAY[0]);
                assert(s.get(1, x)  &&  x == ARRAY[1]);
                assert(s.get(2, x)  &&  x == ARRAY[2]);
            }
        } break; case 85: {
            {
                Sequence s2;
                Sequence s3(s2);
                s2.insert(0, ARRAY[0]);
                s3.insert(0, ARRAY[1]);
                assert(s2.size() == 1  &&  s3.size() == 1);
                ItemType x;
                s2.get(0, x);
                assert(x == ARRAY[0]);
                s3.get(0, x);
                assert(x == ARRAY[1]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 86: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(0, ARRAY[2]);
                s2.insert(2, ARRAY[3]);
                Sequence s3;
                s3.insert(0, ARRAY[5]);
                s3.insert(0, ARRAY[4]);
                s3 = s2;
                s3.insert(1, ARRAY[2]);
                s3.erase(0);
                s3.remove(ARRAY[2]);
                s3.insert(0, ARRAY[4]);
                s3.insert(s3.size(), ARRAY[4]);
                s3.remove(ARRAY[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 87: {
            int before = itemcount();
            {
                Sequence s2;
                Sequence s3;
                int mid = itemcount();
                s2.insert(0, ARRAY[0]);
                s2.insert(1, ARRAY[1]);
                assert(s2.size() == 2);
                s2 = s3;
                assert(itemcount() == mid);
                s2.insert(0, ARRAY[2]);
                s3.insert(0, ARRAY[3]);
                assert(s2.size() == 1  &&  s3.size() == 1);
                ItemType x;
                s2.get(0, x);
                assert(x == ARRAY[2]);
                s3.get(0, x);
                assert(x == ARRAY[3]);
            }
            assert(itemcount() == before);
        } break; case 88: {
            int before = itemcount();
            {
                Sequence s2;
                Sequence s3;
                s2.insert(0, ARRAY[0]);
                s2.insert(1, ARRAY[1]);
                s3 = s2;
                s2.insert(2, ARRAY[2]);
                s3.insert(2, ARRAY[3]);
                assert(s2.size() == 3  &&  s3.size() == 3);
                ItemType x;
                for (size_t k = 0; k < 2; k++)
                {
                    s2.get(k, x);
                    assert(x == ARRAY[k]);
                    s3.get(k, x);
                    assert(x == ARRAY[k]);
                }
                s2.get(2, x);
                assert(x == ARRAY[2]);
                s3.get(2, x);
                assert(x == ARRAY[3]);
            }
            assert(itemcount() == before);
        } break; case 89: {
            int before = itemcount();
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                int mid = itemcount();
                Sequence s3;
                s3.insert(0, ARRAY[5]);
                s3.insert(0, ARRAY[4]);
                s3 = s2;
                assert(itemcount() - mid == mid - before);
            }
        } break; case 90: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                Sequence s3;
                s3.insert(0, ARRAY[5]);
                s3.insert(0, ARRAY[4]);
                s3 = s2;
                s3.insert(3, ARRAY[3]);
                assert(s3.size() == s2.size()+1);
                for (int k = 0; k < s2.size(); k++)
                {
                    ItemType x2 = SOMEVAL;
                    ItemType x3 = DEFAULT;
                    s2.get(k, x2);
                    s3.get(k, x3);
                    assert(x2 == x3);
                }
            }
        } break; case 91: {
            int before = itemcount();
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                Sequence s3;
                s3.insert(0, ARRAY[5]);
                s3.insert(0, ARRAY[4]);
                s2 = s3;
                assert(s2.size() == s3.size());
                ItemType x;
                assert(!s2.get(2, x));
                s2.insert(0, ARRAY[3]);
                assert(s2.size() == s3.size()+1);
                assert(s2.get(0, x)  &&  x == ARRAY[3]);
                assert(s2.get(1, x)  &&  x == ARRAY[4]);
                assert(s2.get(2, x)  &&  x == ARRAY[5]);
            }
            assert(itemcount() == before);
        } break; case 92: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                int n2 = itemcount();
                s2 = s2;
                assert(itemcount() == n2);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 93: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                s2 = s2;
                s2.insert(3, ARRAY[4]);
                ItemType x = SOMEVAL;
                s2.get(0, x); assert(x == ARRAY[1]);
                s2.get(1, x); assert(x == ARRAY[3]);
                s2.get(2, x); assert(x == ARRAY[2]);
                s2.get(3, x); assert(x == ARRAY[4]);
            }
        } break; case 94: {
            Sequence s2;
            assert(subsequence(s2, s) == -1);
        } break; case 95: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[2]);
            Sequence s2;
            assert(subsequence(s2, s) == -1);
        } break; case 96: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[2]);
            Sequence s2;
            assert(subsequence(s, s2) == -1);
        } break; case 97: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[2]);
            assert(subsequence(s, s) == 0);
        } break; case 98: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[0]);
            assert(subsequence(s, s2) == 2);
        } break; case 99: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[0]);
            s2.insert(1, ARRAY[3]);
            assert(subsequence(s, s2) == -1);
        } break; case 100: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[2]);
            assert(subsequence(s, s2) == -1);
        } break; case 101: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[0]);
            assert(subsequence(s, s2) == 2);
        } break; case 102: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[0]);
            s2.insert(1, ARRAY[2]);
            assert(subsequence(s, s2) == 3);
        } break; case 103: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[0]);
            s2.insert(1, ARRAY[2]);
            s2.insert(1, ARRAY[3]);
            assert(subsequence(s, s2) == -1);
        } break; case 104: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            Sequence s3;
            interleave(s, s2, s3);
            assert(s3.size() == s.size());
            for (int k = 0; k < s.size(); k++)
            {
                ItemType x = SOMEVAL;
                ItemType x3 = SOMEVAL;
                s.get(k, x);
                s3.get(k, x3);
                assert(x == x3);
            }
        } break; case 105: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            Sequence s3;
            interleave(s2, s, s3);
            assert(s3.size() == s.size());
            for (int k = 0; k < s.size(); k++)
            {
                ItemType x = SOMEVAL;
                ItemType x3 = SOMEVAL;
                s.get(k, x);
                s3.get(k, x3);
                assert(x == x3);
            }
        } break; case 106: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            s2.insert(0, ARRAY[2]);
            s2.insert(1, ARRAY[0]);
            s2.insert(2, ARRAY[4]);
            Sequence s3;
            interleave(s, s2, s3);
            assert(s3.size() == s.size() + s2.size());
            for (int k = 0; k < s3.size(); k++)
            {
                ItemType x = SOMEVAL;
                ItemType x3 = SOMEVAL;
                if (k % 2 == 0)
                    s.get(k/2, x);
                else
                    s2.get(k/2, x);
                s3.get(k, x3);
                assert(x == x3);
            }
        } break; case 107: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[2]);
            s2.insert(1, ARRAY[0]);
            s2.insert(2, ARRAY[4]);
            Sequence s3;
            interleave(s, s2, s3);
            assert(s3.size() == s.size() + s2.size());
            for (int k = 0; k < s3.size(); k++)
            {
                ItemType x = SOMEVAL;
                ItemType x3 = SOMEVAL;
                if (k >= 2 * s2.size())
                    s.get(k-s2.size(), x);
                else if (k % 2 == 0)
                    s.get(k/2, x);
                else
                    s2.get(k/2, x);
                s3.get(k, x3);
                assert(x == x3);
            }
        } break; case 108: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            s2.insert(0, ARRAY[2]);
            s2.insert(1, ARRAY[0]);
            s2.insert(2, ARRAY[4]);
            s2.insert(3, ARRAY[1]);
            s2.insert(4, ARRAY[3]);
            Sequence s3;
            interleave(s, s2, s3);
            assert(s3.size() == s.size() + s2.size());
            for (int k = 0; k < s3.size(); k++)
            {
                ItemType x = SOMEVAL;
                ItemType x3 = SOMEVAL;
                if (k >= 2 * s.size())
                    s2.get(k-s.size(), x);
                else if (k % 2 == 0)
                    s.get(k/2, x);
                else
                    s2.get(k/2, x);
                s3.get(k, x3);
                assert(x == x3);
            }
        } break; case 109: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            s2.insert(0, ARRAY[2]);
            s2.insert(1, ARRAY[0]);
            s2.insert(2, ARRAY[4]);
            Sequence s3;
            s3.insert(0, ARRAY[3]);
            s3.insert(1, ARRAY[2]);
            s3.insert(2, ARRAY[1]);
            interleave(s, s2, s3);
            assert(s3.size() == s.size() + s2.size());
            for (int k = 0; k < s3.size(); k++)
            {
                ItemType x = SOMEVAL;
                ItemType x3 = SOMEVAL;
                if (k % 2 == 0)
                    s.get(k/2, x);
                else
                    s2.get(k/2, x);
                s3.get(k, x3);
                assert(x == x3);
            }
        } break; case 110: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[2]);
            s2.insert(2, ARRAY[0]);
            interleave(s, s2, s);
            assert(s.size() == 5);
            ItemType x = SOMEVAL;
            s.get(0, x); assert(x == ARRAY[1]);
            s.get(1, x); assert(x == ARRAY[3]);
            s.get(2, x); assert(x == ARRAY[4]);
            s.get(3, x); assert(x == ARRAY[2]);
            s.get(4, x); assert(x == ARRAY[0]);
            s2.get(0, x); assert(x == ARRAY[3]);
            s2.get(1, x); assert(x == ARRAY[2]);
            s2.get(2, x); assert(x == ARRAY[0]);
        } break; case 111: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[2]);
            s2.insert(2, ARRAY[0]);
            interleave(s, s2, s2);
            assert(s2.size() == 5);
            ItemType x = SOMEVAL;
            s2.get(0, x); assert(x == ARRAY[1]);
            s2.get(1, x); assert(x == ARRAY[3]);
            s2.get(2, x); assert(x == ARRAY[4]);
            s2.get(3, x); assert(x == ARRAY[2]);
            s2.get(4, x); assert(x == ARRAY[0]);
            s.get(0, x); assert(x == ARRAY[1]);
            s.get(1, x); assert(x == ARRAY[4]);
        } break; case 112: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            interleave(s, s, s);
            assert(s.size() == 4);
            ItemType x = SOMEVAL;
            s.get(0, x); assert(x == ARRAY[1]);
            s.get(1, x); assert(x == ARRAY[1]);
            s.get(2, x); assert(x == ARRAY[4]);
            s.get(3, x); assert(x == ARRAY[4]);
        }
    }
}
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                    
int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 112)
    {
        cout << "Bad test number" << endl;
        return 1;
    }
    testone(n);
    cout << "Passed" << endl;
}

