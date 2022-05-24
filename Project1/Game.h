//
//  Game.hpp
//  project1
//
//  Created by Jonathan on 4/3/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
class Arena;
class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

int decodeDirection(char dir);
#endif /* Game_hpp */
