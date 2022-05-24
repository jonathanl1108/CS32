

#ifndef Game_hpp
#define Game_hpp
#include "Side.h"
#include "Board.h"
#include "Player.h"
#include <stdio.h>
#include <iostream>

using namespace std;
class Game
{
    public:

    Game(const Board& b, Player* south, Player* north);
    //Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
    void display() const;
    //Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
    void status(bool& over, bool& hasWinner, Side& winner) const;

    bool move();
    //If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
    void play();
    // Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)
    int beans(Side s, int hole) const;
    //Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
private:
    string barSetup( int hole, string tab,Side s)const;
    bool isGameOver() const;
    Player* South_player;
    Player* North_player;
    Side curr_move=SOUTH;
    Board m_board;

};

#endif /* Game_hpp */
