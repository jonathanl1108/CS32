//
//  eval.cpp
//  Homework2
//
//  Created by Jonathan on 4/30/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <cassert>
#include <stack>
using namespace std;

string removeBlank(const string& source)
{
    string result ="";
    for(int i =0 ; i < source.size(); i++)
    {
        char ch = source[i];
        if( ch != ' ')
            result += ch;
    }
    return result;
}
bool isTF( char c)
{
    return ( c=='T' || c =='F');
}

bool isValidInfix( const string& infix, string& nsInfix )
{
    string checkInfix= removeBlank(infix);
   
    /////////////////////////////
    // PRENTACES MATCH CHECK
    ////////////////////////////
    stack<char> prentStack;
    int length  = (int)checkInfix.size();
    if( length ==0)
        return false;
    for( int i =0 ; i< length ;i++)
    {
        char visitChr=checkInfix[i];
        if( visitChr == '(' )
            prentStack.push('('); // find one then push
        else if (visitChr == ')') // if we find ')'
        {
            if(prentStack.empty()) // if the stack is empty then mismatch
                return false;
            else if(prentStack.top() == ')' ) // else if not empty it must be '('
                return false;
            else
                prentStack.pop(); //pop it out since a set is match
        }
    }
    
    if(!prentStack.empty()) // if at the end the stack is still not empty a mismatch is found
    {
         return false;
    }
    
    /////////////////////////////
    // OPERATOR SYNTAX CHECK
    ////////////////////////////
    
    // cant start a infix with ^ &
    // cant end a infix with ^ & !
    char first = checkInfix[0];
    if( first == '&' || first =='^'
       ||checkInfix[length - 1] == '&' || checkInfix[length - 1]=='^'
       ||checkInfix[length - 1] == '!' )
        return false;
    
    for( int i =0 ; i < length ; i++)
    {
        char checkChr = checkInfix[i];
        switch( checkChr)
        {
            /* we dont have to worry about
             * the first and last char having
             * & or ^ 0r ! at end since check above
             */
            case '&':
            case '^':
            {
                // invalid when && ^^ !& &! !^ ^!
                //only valid T&F T^F &() ...
                if( i > 0 && i < length-2)
                {
                    // (& , && , &^ , (^, ^^, ^&
                    char prv=checkInfix[i-1];
                    char next=checkInfix[i+1];
                    if( prv=='&'  || prv=='^' || prv =='(')
                       return false;
                    // && &^ &) ^^ ^& ^)
                    if( next == '&'|| next=='^' || next==')')
                        return false;
                }
                break;
            }
            case '!':
            {
                if( i > 0 && i < length-2)
                {
                    char prv = checkInfix[i-1];
                    char next= checkInfix[i+1];
                    // invalid when, )!, T!, F!
                    if( prv == ')' || isTF(prv))
                        return false;
                    // invalid when !), !&, !^
                    if( next == ')' || next =='&' || next == '^')
                        return false;
                }
                if( i > 0 )
                {
                    char prv = checkInfix[i-1];
                    if( prv == ')' || isTF(prv))
                        return false;
                }
                if( i+1 < length)
                {
                    char next= checkInfix[i+1];
                    if( next == ')' || next =='&' || next == '^')
                        return false;
                }
                break;
            }
            case '(':
            {
                if( i > 0 && i < length-2)
                {
                    char prv = checkInfix[i-1];
                    if( isTF(prv))
                        return false;
                    char next= checkInfix[i+1];
                    // invalid when (), (&, (^
                    if( next == ')' || next =='&' || next == '^')
                        return false;
                    if(isTF(prv) && isTF(next))
                        return false;
                }
                if( i > 0 )
                {
                    char prv = checkInfix[i-1];
                    if( isTF(prv))
                        return false;
                }
                if( i+1 < length)
                {
                    char next= checkInfix[i+1];
                    if( next == ')' || next =='&' || next == '^')
                        return false;
                }
                
                break;
            }
            case ')':
            {
                if( i > 0 && i < length-2)
                {
                    char prv = checkInfix[i-1];
                    char next= checkInfix[i+1];
                    // invalid when, !) &) ^) ()
                    if( (!isTF(prv) && prv !=')') || prv == '(')
                        return false;
                    // invalid when )!, )(
                    if( next == '!' || next == '(')
                        return false;
                    // invalid when T)F
                    if(isTF(prv) && isTF(next))
                        return false;
                }
                if( i > 0 )
                {
                    char prv = checkInfix[i-1];
                    if( (!isTF(prv) && prv !=')') || prv == '(')
                        return false;
                }
                if( i+1 < length)
                {
                    char next= checkInfix[i+1];
                    if( next == '!' || next == '(')
                        return false;
                }
                break;
            }
            case 'T':
            case 'F':
            {
                if( i > 0 && i < length-2)
                {
                    char prv = checkInfix[i-1];
                    char next= checkInfix[i+1];
                    // invalid when, TT FF )T
                    if( (isTF(prv) || prv ==')') )
                        return false;
                    // invalid when TT FF t! f!
                    if( isTF(next) || next=='!')
                        return false;
                }
                if( i > 0 )
                {
                    char prv = checkInfix[i-1];
                    if( (isTF(prv) || prv ==')') )
                        return false;
                }
                if( i+1 < length)
                {
                    char next= checkInfix[i+1];
                    if( isTF(next) || next=='!')
                        return false;
                }
                break;
            }
            default: // bad operends
                return false;
        }
        
    }
    nsInfix = checkInfix;
    return true;
}

int precedenence( char oprt)
{
    switch( oprt)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        default :
            return -1;
    }
}

string infixToPostfix(string infix)
{
    string postfix="";
    stack<char> m_operator;
    for( int i = 0 ; i < infix.size() ; i++)
    {
        char ch = infix[i];
        switch( ch)
        {
            case '(':
                m_operator.push(ch);
                break;
            case ')':
                while(m_operator.top() != '(')
                {
                    postfix+=m_operator.top();
                    m_operator.pop();
                }
                m_operator.pop(); // pop  (
                break;
            case '^':
            case '&':
            case '!':
            {
                while( !m_operator.empty() && m_operator.top()!= '('
                      && precedenence(ch) <= precedenence(m_operator.top())
                      && !(ch=='!' && m_operator.top() == '!'))
                {
                    postfix+=m_operator.top();
                    m_operator.pop();
                }
                m_operator.push(ch);
                break;
                
            }
            case 'T':
            case 'F':
                postfix+=ch;
                break;
            default:
                break;
        }
    }
    while( !m_operator.empty())
    {
        postfix+=m_operator.top();
        m_operator.pop();
    }
    return postfix;
}




int evaluate(string infix, string& postfix, bool& result)
{
    string myInfix;
    if( !isValidInfix(infix, myInfix) || !infix.size())
        return 1;
    //cout<<"cool\n";
    // now we are share the syntax is valid
    // start to evulate
    postfix = infixToPostfix(myInfix);
    //cout<< postfix<<endl;
    stack<bool> operation; //value that ch represents onto the operand stack
    int length = (int)postfix.size();
    for( int i =0 ; i < length ; i++)
    {
        char check = postfix[i];
        bool Result;
        char operend1, operend2;
        if( isTF(check))
        {
            if( check=='T'){
                operation.push(true);
            }
            else{
                operation.push(false);
            }
        }
        else
        {
            switch(check)
            {
                case '&':
                case '^':
                {
                    operend1=operation.top();
                    operation.pop();
                    operend2=operation.top();
                    operation.pop();
                    if( check == '&')
                        Result= (operend1&&operend2);
                    else{
                        Result= ((operend1||operend2));
                        Result=(Result && !(operend1 && operend2) );
                    }
                    operation.push(Result);
                    break;
                }
                case '!':
                {
                    operend1=operation.top();
                    operation.pop();
                    Result= (!operend1);
                    operation.push(Result);
                    break;
                }
            }
        }
        
    }
    result =operation.top();
    return 0;
}
int main()
{
    string pf;
    bool answer;
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("T^F^T", pf, answer) == 0 &&  pf == "TF^T^"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    assert(evaluate("!!!T",  pf, answer) == 0 && pf == "T!!!" &&  !answer);
    assert(evaluate("!!!!T",  pf, answer) == 0 && pf == "T!!!!" &&  answer);
    assert(evaluate(" &(T) ", pf, answer) == 1 &&  pf == "T!!!!"  &&  answer);
    assert(evaluate(" F(T) ", pf, answer) == 1 &&  pf == "T!!!!" &&  answer);
    assert(evaluate(" F&&T ", pf, answer) == 1 &&  pf == "T!!!!" &&  answer);
    assert(evaluate(" F&!T ", pf, answer) == 0 &&  pf == "FT!&" &&  !answer);
    assert(evaluate(" F!T ", pf, answer) == 1 &&  pf == "FT!&" &&  !answer);
    assert(evaluate(" (F&T)) ", pf, answer) == 1 &&  pf == "FT!&" &&  !answer);
    assert(evaluate(" ((F&T) ", pf, answer) == 1 &&  pf == "FT!&" &&  !answer);
    pf="";
    answer=false;
     // (& , && , &^ , (^, ^^, ^&
    assert(evaluate(" (&T^F) ", pf, answer) == 1 &&  pf == "" &&  !answer);
    assert(evaluate(" (T&&F) ", pf, answer) == 1 &&  pf == "" &&  !answer);
    assert(evaluate(" (^T^F) ", pf, answer) == 1 &&  pf == "" &&  !answer);
    assert(evaluate(" (T^^F) ", pf, answer) == 1 &&  pf == "" &&  !answer);
    assert(evaluate(" (T^(&F)) ", pf, answer) == 1 &&  pf == "" &&  !answer);
     // && &^ &) ^^ ^& ^)
    assert(evaluate(" ((T^F)^T) ", pf, answer) == 0 &&  pf == "TF^T^" &&  !answer);
     // invalid when, TT FF )T
    assert(evaluate(" (TT) ", pf, answer) == 1 &&  pf == "TF^T^" &&  !answer);
    assert(evaluate(" (T^)T ", pf, answer) == 1 &&  pf == "TF^T^" &&  !answer);
    assert(evaluate(" (T^F)F ", pf, answer) == 1 &&  pf == "TF^T^" &&  !answer);
    // invalid when TT FF t! f!
    assert(evaluate(" (T!) ", pf, answer) == 1 &&  pf == "TF^T^" &&  !answer);
    assert(evaluate(" (F!) ", pf, answer) == 1 &&  pf == "TF^T^" &&  !answer);
    assert(evaluate(" T! ", pf, answer) == 1 &&  pf == "TF^T^" &&  !answer);
    assert(evaluate(" F! ", pf, answer) == 1 &&  pf == "TF^T^" &&  !answer);
    assert(evaluate(" (!)T ", pf, answer) == 1 &&  pf == "TF^T^" &&  !answer);
    assert(evaluate(" (!&T)^T ", pf, answer) == 1 &&  pf == "TF^T^" &&  !answer);
    assert(evaluate(" (!T)^(!F) ", pf, answer) == 0 &&  pf == "T!F!^" &&  answer);
    assert(evaluate(" T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 &&  answer);
    assert(evaluate("  T ^     ! F", pf, answer) == 0 && pf=="TF!^" && !answer);
    assert(evaluate("  !(T&F)  ", pf, answer) == 0 && pf=="TF&!" && answer);
    assert(evaluate("  !T&F  ", pf, answer) == 0 && pf=="T!F&" && !answer);
    assert(evaluate("  T^F&F  ", pf, answer) == 0 && pf=="TFF&^" && answer);
    assert(evaluate("  t^f&f  ", pf, answer) == 1 && pf=="TFF&^" && answer);
    assert(evaluate("  jonathan  ", pf, answer) == 1 && pf=="TFF&^" && answer);
    // invalid when T)F
    // invalid when !), !&, !^
    // invalid when !), !&, !^
    // invalid when (), (&, (^
    /*
    T                          evaluates to true
    (F)                        evaluates to false
    T^(F)                      evaluates to true
    T ^ !F                     evaluates to false
    !(T&F)                     evaluates to true
    !T&F                       evaluates to false
    T^F&F                      evaluates to true
    T&!(F^T&T^F)^!!!(F&T&F)    evaluates to true
    cout<<pf<<endl;
     */
    cout << "Passed all tests" << endl;
}
