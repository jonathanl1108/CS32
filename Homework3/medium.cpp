//
//  medium.cpp
//  Homework3
//
//  Created by Jonathan on 5/9/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//
enum CallType {
    VOICE, TEXT
};

//Your declarations and implementations would go here
class Medium
{
public:
    Medium(string name);
    virtual ~Medium();
    virtual string connect() const =0; // now Medium is a Abstract class
    virtual string transmit(string msg)const;
    string id() const;
private:
    string m_name;
};
Medium::Medium(string name):m_name(name){}
Medium::~Medium(){}
string Medium::transmit(string msg) const
{
    return ("text: "+msg);
}
string Medium::id()const{ return m_name;}
////////////////////////////////////
// Class Twitter
///////////////////////////////////
class TwitterAccount : public Medium
{
public:
    TwitterAccount( string name );
    virtual ~TwitterAccount();
    virtual string connect() const;
private:
};
TwitterAccount::TwitterAccount( string name ): Medium(name){}
TwitterAccount::~TwitterAccount()
{
    cout<<"Destroying the Twitter account "<<id()<<"."<<endl;
}
string TwitterAccount::connect()const
{
    return "Tweet";
}

////////////////////////////////////
// Class Phone
///////////////////////////////////
class Phone : public Medium
{
public:
    Phone(string name, CallType method);
    virtual ~Phone();
    virtual string connect()const;
    virtual string transmit(string msg)const;
private:
    string m_way;
};
Phone::Phone(string name, CallType method): Medium(name)
{
    if(method == VOICE)
        m_way="voice: ";
    else if(method == TEXT)
        m_way= "text: ";
}
Phone:: ~Phone()
{
    cout<<"Destroying the phone "<<id()<<"."<<endl;
}
string Phone::connect()const{ return "Call"; }
string Phone::transmit(string msg)const
{
    return (m_way+msg);
}

////////////////////////////////////
// Class Email
///////////////////////////////////

class EmailAccount : public Medium
{
public:
    EmailAccount(string name);
    virtual ~EmailAccount();
    virtual string connect()const;
};
EmailAccount:: EmailAccount(string name): Medium(name){}
EmailAccount::~EmailAccount()
{
    cout<<"Destroying the email account "<<id()<<"."<<endl;
}
string EmailAccount::connect()const{ return "Email";}


void send(const Medium* m, string msg)
{
    cout << m->connect() << " using id " << m->id()
    << ", sending " << m->transmit(msg) << endl;
}
