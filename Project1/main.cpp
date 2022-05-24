//
//  main.cpp
//  project1
//
//  Created by Jonathan on 4/3/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

// zombies.cpp

#include "Game.h"
int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

    // Play the game
    g.play();
}

//#include "Arena.h"
//#include "History.h"
//#include "Player.h"
//#include "globals.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    Arena a(3, 4);
//    a.addPlayer(2, 3);
//    a.addZombie(2, 2);
//    a.addZombie(2, 4);
//    a.addZombie(1, 3);
//    a.player()->moveOrAttack(RIGHT);
//    a.player()->moveOrAttack(LEFT);
//    a.player()->moveOrAttack(LEFT);
//    a.player()->moveOrAttack(LEFT);
//    a.player()->moveOrAttack(RIGHT);
//    a.player()->moveOrAttack(UP);
//    a.history().display();
//    cout << "====" << endl;
//}
//
