//
//  Zombie.hpp
//  project1
//
//  Created by Jonathan on 4/3/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#ifndef Zombie_h
#define Zombie_h
class Arena;
class Zombie
{
public:
    // Constructor
    Zombie(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool getAttacked(int dir);
    
private:
    Arena* m_arena; // indicates using class
    int    m_row;
    int    m_col;
    int    m_health;
};

#endif /* Zombie_hpp */
