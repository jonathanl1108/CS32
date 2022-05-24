

#include "Game.h"
#include <stdio.h>
#include <iostream>
using namespace std;
bool Game::isGameOver()const
{
    return (m_board.beansInPlay(SOUTH)==0 || m_board.beansInPlay(NORTH)==0);
}
string Game::barSetup( int hole, string tab, Side s)const
{
//    string myPits;
//    for(int i =1 ; i<= hole; i++ )
//    {
//        char num = i+'0';
//        myPits =  myPits+num+" ";
//    }
    string dash;
    for( int i =0 ; i <hole*2; i++ )
        dash+='-';
    
    if( s == NORTH)
        return tab+'\n'+tab+dash;
    else
        return tab+dash+tab;
}

Game::Game(const Board& b, Player* south, Player* north)
:m_board(b),South_player(south),North_player(north)
{}
void Game::display() const
{
    // to make it look good the center of name
    // will be display at above the center oh hole
    // comput center pot
    string centerbar =North_player->name()+"'s pot "+
    to_string(m_board.beans(NORTH, 0));
    string displayTab="  ";
    const char tab=' ';
    int sizeS = South_player->name().size();
    int sizeN = North_player->name().size();
    // compute
    int num_hole= m_board.holes();
    sizeS = sizeS/2;
    sizeN = sizeN/2;
    int length =(int)num_hole+displayTab.size();
    int counter = centerbar.size();
    while( length -sizeN < 0 ||  length -sizeS < 0  )
    {
        displayTab+=tab;
        num_hole+=displayTab.size();
    }
    string nametab;
    for(int i =0 ; i < counter-1 ;i++)
        displayTab+=tab;
    for(int i =0 ; i < num_hole ;i++)
        nametab+=tab;
  
    string Northbar=
    displayTab+North_player->name()+barSetup(num_hole, displayTab,NORTH);
    string Southbar=
    barSetup(num_hole, displayTab,SOUTH)+'\n'+displayTab+' '+South_player->name();
    
    cout<<Northbar<<endl;
    cout<<displayTab;
    for( int i =1 ; i <= num_hole ; i++)
        cout<<m_board.beans(NORTH, i)<<" ";
    cout<<endl;
    cout<<centerbar;
    for( int i =0 ; i <= num_hole*2 ; i++)
        cout<<tab;
    cout<<m_board.beans(SOUTH, 0)<<" "<<South_player->name()<<"'s pot"<<endl;
    cout<<displayTab;
    for( int i =1 ; i <= num_hole ; i++)
        cout<<m_board.beans(SOUTH, i)<<" ";
    cout<<endl;
    cout<<Southbar<<endl;
    
}

//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    if(isGameOver())
    {
        over = true;
        int S_Pot =m_board.beans(SOUTH, 0);
        int N_Pot =m_board.beans(NORTH, 0);
        // there could have 3 possible outcome, tie, N_w , S_w
        if( S_Pot == N_Pot )
        {
            // we have a tie
            hasWinner = false;
        }
        else // must has a winner
        {
            hasWinner = true;
            // 2 casee
            if( S_Pot > N_Pot)
                winner=SOUTH;
            else
                winner=NORTH;
        }
    }else
         over = false;
}

//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.

bool Game::move() // complete a move
{
    bool over, hasWinner;
    Side winner, endSide;;
    int endHole;
    
    status(over, hasWinner, winner);
    if(over)
        return false; //If the game is over, return false.
    Player* currPlayer;
    // compute the game
    
    int hole = -1;
    if( curr_move == SOUTH)
        currPlayer= South_player;
    else
        currPlayer = North_player;
    
    // let player choes the hole
    hole = currPlayer->chooseMove(m_board, curr_move);
    cout << currPlayer->name() << " chooses hole " << hole << endl;
    // make that move !!!
    m_board.sow(curr_move, hole, endSide, endHole);

    if( !isGameOver()) // only do it if not gameover
    {
        // Rule 1 :: go-again
        // If it was placed in the player's pot, he must take another turn.
        if(endSide == curr_move && endHole == POT)
        {
            // we get to go again
            do{
                display();
                cout<<currPlayer->name()<<" gets another turn."<<endl;
                hole = currPlayer->chooseMove(m_board, curr_move);
                if( hole == -1)
                    break; // game over
                m_board.sow(curr_move, hole, endSide, endHole);
                cout << currPlayer->name() << " chooses hole " << hole << endl;
            }while(endSide == curr_move && endHole == POT && !isGameOver() );
        }
    }
    
    // Rule 2 :: capture
    if(!isGameOver())  // only do it if not gameover
    {
        if( endSide == curr_move && endHole != POT
           && m_board.beans(endSide, endHole)==1 && m_board.beans(opponent(endSide), endHole) > 0)
        {
            // we have a capture
           // cerr<<" found a cpature "<<endl;
            // move them into out pot
            m_board.moveToPot(opponent(endSide), endHole, endSide);
            m_board.moveToPot(endSide, endHole, endSide);
        }
        
    }
  
   
    if( isGameOver())
    {
        Player *owner;
        // final result
        if( !m_board.beansInPlay(SOUTH)) // if south is empty then...
        {
            owner = North_player;
            for( int hole =1 ; hole <= m_board.holes(); hole++)
            {
                if( m_board.beans(NORTH,hole))
                    m_board.moveToPot(NORTH, hole, NORTH);
            }
        }
        else if(!m_board.beansInPlay(NORTH))// if North is empty
        {
            owner=South_player;
            for( int hole =1 ; hole <= m_board.holes(); hole++)
            {
                if( m_board.beans(SOUTH,hole))
                    m_board.moveToPot(SOUTH, hole, SOUTH);
            }
            
        }else
            return false;
        cout << "Sweeping remaining beans into "<<owner->name() <<"'s pot."<< endl;
        display();
        return false;
    }
    // the game is not yet over, switch turn
    curr_move = opponent(curr_move);
    return true; // shows there are still moves
}


//   If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)


void Game::play()
{
    // first check if south has bean to start the first move
    bool hasWinner;
    Side winner;
    bool over;
    if(!m_board.beansInPlay(SOUTH))
    {
        display(); // show the init state
        if( m_board.beansInPlay(NORTH))
        {
            for( int hole =1 ; hole <= m_board.holes(); hole++)
            {
                if( m_board.beans(NORTH,hole))
                    m_board.moveToPot(NORTH, hole, NORTH);
            }
            cout << "Sweeping remaining beans into "<<North_player->name() <<"'s pot."<< endl;
            display();
            status(over, hasWinner, winner);
        }
        
    }
    else
    {
        
        // while we still have move
        do{
            display();
            if(!South_player->isInteractive() && !North_player->isInteractive())
            {
                // prompt the viewer to press ENTER
                display();
                cout<<"Press ENTER to continue";
                cin.ignore(10000, '\n');
            }
            // move it
            move();
            // keep track
            status(over, hasWinner, winner);
        }while( !over);
    }
    status(over, hasWinner, winner);
    if(hasWinner)
    {
        string winner_name;
        if( winner == SOUTH)
            winner_name = South_player->name();
        else
            winner_name = North_player->name();
        
        cout << "The winner is " << winner_name<< endl;
    }
    else
        cout << "The game restulted in a tie." << endl;
    
    
}


int Game::beans(Side s, int hole) const
{
    if (hole < 0 || hole > m_board.holes())
        return -1;
    return m_board.beans(s, hole);
}
