

#include "Player.h"

////////////////////////////////////////////
//  PLAYER IMPLEMENTATION
///////////////////////////////////////////

//NO SUCH THING CALLED VIRTUAL C'TOR
Player::Player(std::string name)
:m_name(name)
{}
//ALWAYS USE VIRTUAL D'TOR
Player::~Player(){}
string Player::name() const
{
    return m_name;
}
bool Player::isInteractive() const
{
    return false;
}

////////////////////////////////////////////
// DERIVED CLASS :: HUMAN IMPLEMENTATION
///////////////////////////////////////////


HumanPlayer::HumanPlayer( string name)
:Player(name)
{}
HumanPlayer:: ~HumanPlayer()
{}
bool HumanPlayer:: isInteractive()const
{
    return true;
}
int HumanPlayer:: chooseMove(const Board& b, Side s) const
{
    if(b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) ==0)
        return -1;
    // classic I/O
    int m_hole;
    // A HumanPlayer chooses its move by prompting a person running the program for a move
    //(reprompting if necessary until the person enters a valid hole number)
    do{
        cout<<"Select a hole, "<<name()<<": ";
        cin>>m_hole;
        
    }while( !isValidMove(b, s, m_hole));
    // valid move then operate on our board
    return m_hole;
}

bool isValidMove(const Board& b, Side s, int hole)
{
    // in valid when hole < 0 || hole > index
    // or the hole is empty
    if( hole <= 0 || hole > b.holes() )
    {
        cout<<"The hole number must be from 1 to "<<b.holes()<<"."
        <<endl;
        return false;
    }
    if( b.beans(s,hole) <=0 )
    {
        cout<<"There are no beans in that hole."<<endl;
        return false;
    }
    return true;
}


////////////////////////////////////////////
// DERIVED CLASS :: BAD_PLAYER IMPLEMENTATION
///////////////////////////////////////////
BadPlayer::BadPlayer(std::string name)
:Player(name)
{}

BadPlayer::~BadPlayer()
{}
//A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement class that at least plays legally.
int BadPlayer::chooseMove(const Board& b, Side s)const
{
    if(b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) ==0)
        return -1;
    int m_hole;
    // generat random
    do{
        m_hole = (rand() % b.holes()) + 1;
    }while( m_hole < 0 || m_hole > b.holes() || (b.beans(s, m_hole)<=0));
    // valid move then operate on our board
    return m_hole;
}


////////////////////////////////////////////
//SmartPlayer (derived from Player)
////////////////////////////////////////////

// this will always return S_pot - N-pot
// thus for we want to maximized S and minimized N !!
int SmartPlayer::evalulate( const Board& b) const
{
    return (b.beans(SOUTH, 0) - b.beans(NORTH, 0));
}

SmartPlayer::SmartPlayer(std::string name)
:Player(name)
{}
SmartPlayer::~SmartPlayer()
{}
int SmartPlayer::chooseMove(const Board &b, Side s)const
{
    if(b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) ==0)
        return -1;
    AlarmClock ac(4900);  // will time out after 4.9 seconds
    int eval;
    return minimax_ab(b, s, eval, ac);
}

// Simulates the game with the rule, return true if the game is over
// otherwise false
void SmartPlayer::simulate( Board& board, Side s, int hole)const
{    int endHole;
     Side endSide;
     board.sow(s, hole, endSide, endHole);
    // if game over
    if( board.beansInPlay(SOUTH) == 0 || board.beansInPlay(NORTH) ==0 ) // game is over if either side is empty
    {
        // simulate the final result
        if( !board.beansInPlay(SOUTH) ) // if south is empty then...
        {
            for( int hole =1 ; hole <= board.holes(); hole++)
            {
                if( board.beans(NORTH,hole))
                    board.moveToPot(NORTH, hole, NORTH);
            }
        }
        else if(!board.beansInPlay(NORTH))// if North is empty
        {
            for( int hole =1 ; hole <= board.holes(); hole++)
            {
                if( board.beans(SOUTH,hole))
                    board.moveToPot(SOUTH, hole, SOUTH);
            }
            
        }
    }else
    {
        
        // okay, since the game is not over, simulate  it
       // board.sow(s, hole, endSide, endHole);
        // sow doesnt do the rule, so it is not the final !!
        
        // Rule 1
        //If it was placed in the player's pot, he must take another turn.
        //if( endSide == s && endHole == POT)
        // Rule 2
        // capture
        if( endSide == s && board.beans(endSide, endHole) == 1 && endHole!=POT)
        {
            if( board.beans(opponent(endSide), endHole) > 0)
            {
                // we have a capture
                //cerr<<" found a cpature "<<endl;
                // move them into out pot
                board.moveToPot(opponent(endSide), endHole, endSide);
                board.moveToPot(endSide, endHole, endSide);
            }
        }
    }
    
}

// okay so i want my  minimax to return the best hole for me
// not the best value use less here
// thus change parameters again !!!

int SmartPlayer::minimax_ab( const Board& board, Side player, int& eval,AlarmClock& alarm,int depth, int alpha, int beta )const
{
    // Borad is being passed in as the most relvent state from the prv move
    // side s will be the player
    
    // Varible Setteing
    int bestHole = -3;
   
    // base case
    if( depth <= 0)
    {
        // return
        eval = evalulate(board);
        return -1; // times out return -1
    }
    // 1 if the times up
    if( alarm.timedOut())
    {
        eval = evalulate(board);
        return -1; // times out return -1
    }
    // 2 if the game is over
    /*
     notice since board is not responsible for the
     rules, we will have to do it manully
    */
   
    if( board.beansInPlay(SOUTH) == 0 || board.beansInPlay(NORTH) ==0  ) // game is over if either side is empty
    {
        Board currB(board); // so we can simulate our B
        // simulate the final result
        if( !board.beansInPlay(SOUTH) ) // if south is empty then...
        {
            for( int hole =1 ; hole <= board.holes(); hole++)
            {
                if( currB.beans(NORTH,hole))
                    currB.moveToPot(NORTH, hole, NORTH);
            }
        }
        else if( !board.beansInPlay(NORTH))
        {
            for( int hole =1 ; hole <= board.holes(); hole++)
            {
                if( currB.beans(SOUTH,hole))
                    currB.moveToPot(SOUTH, hole, SOUTH);
            }
            
        }
        // do the computation on the final result ...
        // and save it to eval
        eval = evalulate(currB);
        return -1; // return -1 hit end
    }

    
    // okay, since the game is either not over and time is sill up
    // lets look for bestHole from the relevent  board status for the player
    
    /*
     With my definition of evaulate()
                south_pot - north_pot
     SOUTH -> MAXIMIZER
     NORTH -> MINIMIZER
     
     */
    int numHole= board.holes();
    if( player == SOUTH) // MAXIMIZED player
    {
        int maxEval = N_INFINTY;
        // visit each child
        for( int hole = 1; hole <= numHole ; hole++ )
        {
            if( board.beans(player, hole) <= 0)
                continue;
            // another temp board to simulate 
            Board temp(board);
            simulate(temp, player, hole);
            // now evaluate the result of the move
            int evalu= N_INFINTY;
            minimax_ab(temp, opponent(player), evalu, alarm,depth-1, alpha, beta );
            if( evalu > maxEval)
            {
                maxEval=evalu;
                bestHole = hole;
            }
             //puring so we dont waste time
            alpha=max(alpha, evalu);
            if( beta <= alpha )
                break;
        }
        eval = maxEval;
        return bestHole;
    }
    else // MINIMIZED player
    {
        int minEval = P_INFINTY;
        // visit each child
        for( int hole = 1; hole <= numHole ; hole++ )
        {
            if( board.beans(player, hole) <= 0)
                continue;
            // another temp board to simulate
            Board temp(board);
            simulate(temp, player, hole);
            // now evaluate the result of the move
            int evalu= N_INFINTY;
            minimax_ab(temp, opponent(player), evalu, alarm,depth-1,alpha, beta);
            if( evalu < minEval)
            {
                minEval=evalu;
                bestHole = hole;
            }
            // puring so we dont waste time
            beta=min(beta, evalu);
            if( beta <= alpha )
                break;
        }
        eval = minEval;
        return bestHole;
    }
    
}
