
#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>
#include "Board.h"
#include "Side.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace std;

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
    AlarmClock(int ms)
    {
        m_timedOut = false;
        m_isRunning = true;
        m_alarmClockFuture = std::async([=]() {
            for (int k = 0; k < ms  &&  m_isRunning; k++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_isRunning)
                m_timedOut = true;
        });
    }
    
    ~AlarmClock()
    {
        m_isRunning = false;
        m_alarmClockFuture.get();
    }
    
    bool timedOut() const
    {
        return m_timedOut;
    }
    
    AlarmClock(const AlarmClock&) = delete;
    AlarmClock& operator=(const AlarmClock&) = delete;
private:
    std::atomic<bool> m_isRunning;
    std::atomic<bool> m_timedOut;
    std::future<void> m_alarmClockFuture;
};
////////////////////////////////////////////
// BASE CLASS :: PLAYER
///////////////////////////////////////////
class Player
{
public:
    Player(std::string name);
    //Create a Player with the indicated name.
    std::string name() const;
    //Return the name of the player.
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player();
    //Since this class is designed as a base class, it should have a virtual destructor.
private:
    string m_name;
};

////////////////////////////////////////////
// DERIVED CLASS :: HUMAN
///////////////////////////////////////////

/*
 
 and returning that choice. We will never test for a situation where the user doesn't enter an integer when prompted for a hole number.
 (The techniques for dealing with the issue completely correctly are a distraction to this project, and involve either a function like stoi or strtol, or the type istringstream.)
 */
bool isValidMove(const Board& b, Side s, int hole);

class HumanPlayer : public Player
{
public:
    HumanPlayer( string name);
    virtual ~HumanPlayer();
    virtual bool isInteractive()const;
    virtual int chooseMove(const Board& b, Side s) const;
private:
};

////////////////////////////////////////////
// DERIVED CLASS :: BAD_PLAYER
///////////////////////////////////////////

class BadPlayer : public Player
{
public:
    BadPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~BadPlayer();
private:

};
////////////////////////////////////////////
//DERIVED CLASS :: SmartPlayer 
////////////////////////////////////////////
class SmartPlayer:public Player
{
public:
    SmartPlayer(std::string name);
    virtual ~SmartPlayer();
    virtual int chooseMove(const Board& b, Side s) const;
    int minimax_ab( const Board& board, Side s,int& eval, AlarmClock& alarm, int depth=5,int alpha=N_INFINTY, int beta=P_INFINTY ) const;
private:
    int evalulate( const Board& b)const;
    void simulate( Board&b, Side s, int hole)const;
};


#endif /* Player_hpp */

