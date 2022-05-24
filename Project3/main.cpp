
#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Side.h"
#include "Player.h"
#include <iostream>
#include <cassert>
using namespace std;
void doBoardTests()
{
    Board b(3, 2);
    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
           b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
           b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
           b.beansInPlay(SOUTH) == 3);
    Side es;
    int eh;
    b.sow(SOUTH, 3, es, eh);
    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
           b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
           b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
}

void doBoardTests2()
{
    Board b(3, 2);
    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
           b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
           b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
           b.beansInPlay(SOUTH) == 3);
    Side es;
    int eh;
    b.sow(SOUTH, 3, es, eh);
    cout<<eh<<endl;
    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
           b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
           b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);

    Board b1(3, 5);
    assert(b1.holes() == 3  &&  b1.totalBeans() == 30  &&
           b1.beans(SOUTH, POT) == 0  &&  b1.beansInPlay(SOUTH) == 15 &&
           b1.beansInPlay(NORTH) == 15);
    b1.setBeans(SOUTH, 1, 1);
    b1.moveToPot(NORTH, 2, SOUTH);
    assert(b1.totalBeans() == 26  &&  b1.beans(SOUTH, 1) == 1  &&
           b1.beans(NORTH, 2) == 0  &&  b1.beans(SOUTH, POT) == 5  &&
           b1.beansInPlay(SOUTH) == 11 && b1.beansInPlay(NORTH) == 10);

    b1.sow(SOUTH, 3, es, eh);
    assert(es == SOUTH  &&  eh == 1  &&  b1.beans(SOUTH, 3) == 0  &&
           b1.beans(NORTH, 3) == 6 && b1.beans(NORTH, 2) == 1 && b1.beans(NORTH, 1) == 6
           &&  b1.beans(NORTH, POT) == 0 &&  b1.beans(SOUTH, POT) == 6  && b1.beans(SOUTH, 1) == 2&&
           b1.beansInPlay(SOUTH) == 7  &&  b1.beansInPlay(NORTH) == 13);
    
    Board b2( 6, 5);
    /*
        5 5 5 5 5 5
     0              0
        5 5 5 5 5 5
     */
    // hole return test
    assert( b2.holes() == 6);
    // beans( s, h ) return test
    for( int hole = 1 ; hole <=  b2.holes();hole++)
    {
        assert(b2.beans(SOUTH, hole)== 5);
        assert(b2.beans(NORTH, hole)== 5);
    }
    // test if pot start at 0 beans
    assert(b2.beans(SOUTH, 0)== 0);
    assert(b2.beans(NORTH, 0)== 0);
    assert(b2.beansInPlay(SOUTH) == 30);
    assert(b2.beansInPlay(NORTH) == 30);
    // this will test if any beans are lost
    // after moves
    int bf_m = b2.totalBeans();
    assert(bf_m == 60);
    // TEST MOVE
    // Kalah move
    Side endSide;
    int endHole;
    b2.sow(SOUTH, 2, endSide,endHole);
    assert(b2.beans(SOUTH, 0)== 1 && b2.beans(SOUTH, 2)==0 && b2.beans(SOUTH, 3)==6
              && b2.beans(SOUTH, 4)==6 &&b2.beans(SOUTH, 5)==6);
   // should not affect north
    for( int hole = 1 ; hole <=  b2.holes();hole++)
    {
        assert(b2.beans(NORTH, hole)== 5);
    }
           /*
             5 5 5 5 5 5
            0            1
             5 0 6 6 6 6
            */
   b2.sow(SOUTH, 1, endSide,endHole);
    assert(b2.beans(SOUTH, 0)== 1 && b2.beans(SOUTH, 2)==1 && b2.beans(SOUTH, 3)==7
           &&b2.beans(SOUTH, 4)==7&&b2.beans(SOUTH, 5)==7 && b2.beans(SOUTH, 1)==0 && endSide == SOUTH
         &&endHole==6);
    // should not affect north
   for( int hole = 1 ; hole <=  b2.holes();hole++)
    {
     assert(b2.beans(NORTH, hole)== 5);
    }
          /*
             5 5 5 5 5 5
           0             1
             0 1 7 7 7 7
           */
   b2.setBeans(SOUTH,2, 0);
   b2.setBeans(SOUTH,6, 8);
          /*
            5 5 5 5 5 5
           0             1
            0 0 7 7 7 8
           */
    // skip opp pot test shoulk
    // should not go into opp's pot
    /*
       6 6 6 6 6 6
     0             2
       1 0 7 7 7 0
     */
 b2.sow(SOUTH, 6, endSide,endHole);
 assert(b2.beans(SOUTH, 0)== 2 && b2.beans(SOUTH, 2)==0 && b2.beans(SOUTH, 3)==7
   &&b2.beans(SOUTH, 4)==7&&b2.beans(SOUTH, 5)==7 && b2.beans(SOUTH, 6)==0 &&b2.beans(SOUTH, 1)==1
               && endSide == SOUTH
     &&endHole==1);
        for( int hole = 1 ; hole <=  b2.holes();hole++)
        {
         assert(b2.beans(NORTH, hole)== 6);
        }
    
    //North move
    b2.sow(NORTH, 6, endSide,endHole);
    assert(b2.beans(SOUTH, 0)== 2 && b2.beans(SOUTH, 2)==0 && b2.beans(SOUTH, 3)==7
           &&b2.beans(SOUTH, 4)==7&&b2.beans(SOUTH, 5)==7 && b2.beans(SOUTH, 6)==0 &&b2.beans(SOUTH, 1)==1);
    assert(b2.beans(NORTH, 0)== 1 && b2.beans(NORTH, 2)==7 && b2.beans(NORTH, 3)==7
           &&b2.beans(NORTH, 4)==7&&b2.beans(NORTH, 5)==7 && b2.beans(NORTH, 6)==0 &&b2.beans(NORTH, 1)==7
           && endHole == NORTH
           &&endHole==0);
    /*
       7 7 7 7 7 0
     1             2
       1 0 7 7 7 0
     */
    b2.setBeans(NORTH, 1, 11);
    b2.setBeans(NORTH, 2, 3);
    
   
    // This sow, will cause North1 to go around the table and end up one pos of the start
    // beans should not increase the beans in south pot
    b2.sow(NORTH, 1, endSide,endHole);
    assert(b2.beans(SOUTH, 0)== 2 && b2.beans(SOUTH, 2)==1 && b2.beans(SOUTH, 3)==8
           &&b2.beans(SOUTH, 4)==8&&b2.beans(SOUTH, 5)==8 && b2.beans(SOUTH, 6)==1 &&b2.beans(SOUTH, 1)==2);
    /*
     0 3 8 8 8 1
     2             2
     2 1 8 8 8 1
     */
    assert(b2.beans(NORTH, 0)== 2 && b2.beans(NORTH, 2)==3 && b2.beans(NORTH, 3)==8
           &&b2.beans(NORTH, 4)==8&&b2.beans(NORTH, 5)==8 && b2.beans(NORTH, 6)==1 &&b2.beans(NORTH, 1)==0
           && endSide == NORTH
           &&endHole==3);
    for( int hole = 1 ; hole <=  b2.holes();hole++)
        b2.moveToPot(NORTH, hole, SOUTH);
    for( int hole = 1 ; hole <=  b2.holes();hole++)
    {
        assert(b2.beans(NORTH, hole)== 0);
    }
    assert(b2.beans(SOUTH,POT) == 30);
    // total bean no less test
    assert(b2.totalBeans() == bf_m);
    /*
      0 0 0 0 0 0
     2             30
      2 1 8 8 8 1
     */
}


void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    n = sp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
}

void doPlayerTest2()
{
    
    // TEST:: is the virtual function defined correctly
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp2("Bart");
    assert(bp2.name() == "Bart"  &&  !bp2.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    SmartPlayer sp2("Meggie");
    assert(sp2.name() == "Meggie"  &&  !sp2.isInteractive());
    
    /*
       1 2 3 4
     3         5
       1 2 3 4
     */
    // TEST Basic no choice CHOICE
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    n = sp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    
    // THESE ARE DESIGNED TEST CASE
    // smart player should make smart choice
    // if the tree were to be drawn
    // 3 is a better choice than 1
    Board b2(3, 2);
        b2.setBeans(SOUTH, 2, 0);
        b2.setBeans(SOUTH, 3, 1);
        b2.setBeans(NORTH, 1, 3);
    /*
       3 2 2
     0       0
       2 0 1
     */
    cout << "^^^^^^^^^" << endl;
    int n_sp = sp.chooseMove(b2, SOUTH);
    assert(n_sp == 3);
    cout << "^^^^^^^^^" << endl;
    Board b3(3, 2);
    b3.setBeans(SOUTH, 1, 1);
    b3.setBeans(SOUTH, 2, 1);
    b3.setBeans(SOUTH, 3, 0);
    b3.setBeans(NORTH, 3, 0);
    b3.setBeans(NORTH, 2, 3);
    b3.setBeans(SOUTH, POT, 5);
    /*
       2 3 0
     0       5
       1 1 0
     */
     // 1 is a better choice than 2
    n_sp = sp.chooseMove(b3, SOUTH);
    assert(n_sp == 1);
}
void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
    //    Homer
    //   0  1  2
    // 0         0
    //   2  0  0
    //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
           g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    
    g.move();
    //   0  1  0
    // 0         3
    //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
    
    g.move();
    //   1  0  0
    // 0         3
    //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
    
    g.move();
    //   1  0  0
    // 0         3
    //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
    
    g.move();
    //   0  0  0
    // 1         4
    //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}

void gameDisplaytest()
{
    SmartPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(10,3);
    Game g(b, &bp1, &bp2);
    g.display();
}
void doGameTest2()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    SmartPlayer sp2("Meggie");
    assert(sp2.name() == "Meggie"  &&  !sp2.isInteractive());
    // play() test
    Board b(3,0);
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    // the board is all empty
    Game g(b, &bp1, &bp2);
    g.play();
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g1(b, &bp1, &bp2);
    /*
     (Note: If when this function is called, South has no beans in play, so can't make
     the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)
     */
    g1.play();
    // TEST IF  promt ENTER to user
    //comp vs comp
    Board b_cvc(3,2);
    // TEST BAD VS BAD
    Game g_cvc(b_cvc, &bp1, &bp2);
    Game g_cvc_sp_bp(b_cvc,&sp,&bp1);
    Game g_cvc_sp_sp(b_cvc,&sp,&sp2);
    Game g_hvc_sp(b_cvc,&sp,&hp);
    Game g_hvc_bp(b_cvc, &hp, &bp2);
    g_cvc.play();
    // TEST SMART VS BAD
    g_cvc_sp_bp.play();
    // TEST SMART VS SMART !!
    g_cvc_sp_sp.play();
    // TEST SMART VS HUMAN !!
    g_hvc_sp.play();
    // TEST BAD VS HUMAN !!
    g_hvc_bp.play();
//
    // A GOOD TEST is JUST TO PLAY
    
    // GAME2- CPATURE TEST
    bool over;
    bool hasWinner;
    Side winner;
    Board b2(3,0);
    b2.setBeans(SOUTH, 1, 2);
    b2.setBeans(NORTH, 2, 1);
    b2.setBeans(NORTH, 3, 3);
    b2.setBeans(NORTH, 0, 1);
    Game g2(b2, &bp1, &bp2);
    //   0  1  3
    // 1         0
    //   2  0  0
    g2.display();
    g2.status(over, hasWinner, winner);
    // should not be over yet
    assert(!over && g2.beans(NORTH, 1) == 0 && g2.beans(NORTH, 2) == 1 && g2.beans(NORTH, 3) == 3
           &&g2.beans(SOUTH, 1) == 2 && g2.beans(SOUTH, 2) == 0 && g2.beans(SOUTH, 3) == 0
           && g2.beans(NORTH, 0) == 1 && g2.beans(SOUTH, 0) == 0);
    // SOUTH alway start the game
    g2.move();
    //   0  1  3
    // 1         0
    //   0  1  1
    // leaving no choice + capture
    //   0  1  0
    // 1         4
    //   0  1  0
    g2.display();
    g2.status(over, hasWinner, winner);
    assert(!over && g2.beans(NORTH, 1) == 0 && g2.beans(NORTH, 2) == 1 && g2.beans(NORTH, 3) == 0
           &&g2.beans(SOUTH, 1) == 0 && g2.beans(SOUTH, 2) == 1 && g2.beans(SOUTH, 3) == 0
           && g2.beans(NORTH, 0) == 1 && g2.beans(SOUTH, 0) == 4);
    // NORTH TURN
    g2.move();
    //   1  0  0
    // 1         4
    //   0  1  0
    g2.display();
    g2.status(over, hasWinner, winner);
    assert(!over && g2.beans(NORTH, 1) == 1 && g2.beans(NORTH, 2) == 0 && g2.beans(NORTH, 3) == 0
           &&g2.beans(SOUTH, 1) == 0 && g2.beans(SOUTH, 2) == 1 && g2.beans(SOUTH, 3) == 0
           && g2.beans(NORTH, 0) == 1 && g2.beans(SOUTH, 0) == 4);
    
     // SOUTH TURN
    g2.move();
    //   1  0  0
    // 1         4
    //   0  0  1
    g2.display();
    g2.status(over, hasWinner, winner);
    assert(!over && g2.beans(NORTH, 1) == 1 && g2.beans(NORTH, 2) == 0 && g2.beans(NORTH, 3) == 0
           &&g2.beans(SOUTH, 1) == 0 && g2.beans(SOUTH, 2) == 0 && g2.beans(SOUTH, 3) == 1
           && g2.beans(NORTH, 0) == 1 && g2.beans(SOUTH, 0) == 4);
    //NORTH TURN
    g2.move();
    //   0  0  0
    // 2         4
    //   0  0  1
    // WE HAVE A GAME OVER
    // SWEEP SWEEP
    //   0  0  0
    // 2         5
    //   0  0  0
    g2.display();
    g2.status(over, hasWinner, winner);
    assert(hasWinner && winner == SOUTH);
    assert(over && g2.beans(NORTH, 1) == 0 && g2.beans(NORTH, 2) == 0 && g2.beans(NORTH, 3) == 0
           &&g2.beans(SOUTH, 1) == 0 && g2.beans(SOUTH, 2) == 0 && g2.beans(SOUTH, 3) == 0
           && g2.beans(NORTH, 0) == 2 && g2.beans(SOUTH, 0) == 5);
  
    // GAME3- GO AGAIN TEST
    //   0  0  1
    // 1         1
    //   3  2  1
    Board b3(3,0);
    b3.setBeans(NORTH, 0, 1);
    b3.setBeans(NORTH, 1, 0);
    b3.setBeans(NORTH, 2, 0);
    b3.setBeans(NORTH, 3, 1);
    b3.setBeans(SOUTH, 0, 1);
    b3.setBeans(SOUTH, 1, 3);
    b3.setBeans(SOUTH, 2, 2);
    b3.setBeans(SOUTH, 3, 1);
    Game g3(b3, &hp, &sp);
    g3.display();
  //  g3.play();
    // HUMTURN
    g3.move();
//    g3.display();
//    assert(over && g3.beans(NORTH, 1) == 0 && g3.beans(NORTH, 2) == 0 && g3.beans(NORTH, 3) == 1
//           &&g3.beans(SOUTH, 1) == 3 && g3.beans(SOUTH, 2) == 2 && g3.beans(SOUTH, 3) == 0
//           && g3.beans(NORTH, 0) == 1 && g3.beans(SOUTH, 0) == 2);
     // STILL HUMTURN
    //   0  0  1
    // 1         3
    //   3  0  1
//    g3.move();
//    g3.display();
//    assert(over && g3.beans(NORTH, 1) == 0 && g3.beans(NORTH, 2) == 0 && g3.beans(NORTH, 3) == 1
//           &&g3.beans(SOUTH, 1) == 3 && g3.beans(SOUTH, 2) == 0 && g3.beans(SOUTH, 3) == 1
//           && g3.beans(NORTH, 0) == 1 && g3.beans(SOUTH, 0) == 3);

    //   0  0  1
    // 1         4
    //   0  1  2
    
    
    assert(over && g3.beans(NORTH, 1) == 0 && g3.beans(NORTH, 2) == 0 && g3.beans(NORTH, 3) == 2
        &&g3.beans(SOUTH, 1) == 0 && g3.beans(SOUTH, 2) == 1 && g3.beans(SOUTH, 3) == 0
        && g3.beans(NORTH, 0) == 1 && g3.beans(SOUTH, 0) == 5);
    
    //   1  1  0
    // 1         5
    //   0  1  0
    
    g3.move();
    g3.display();
    assert(over && g3.beans(NORTH, 1) == 1 && g3.beans(NORTH, 2) == 1 && g3.beans(NORTH, 3) == 0
           &&g3.beans(SOUTH, 1) == 0 && g3.beans(SOUTH, 2) == 1 && g3.beans(SOUTH, 3) == 0
           && g3.beans(NORTH, 0) == 1 && g3.beans(SOUTH, 0) == 5);
        g3.move();
        g3.display();
    Board b404( 3, 0);
    Game g4( b404, &bp1, &bp1);
    assert(!g4.move());
}



int main()
{
    gameDisplaytest();
    doGameTest2();
    doBoardTests();
    doPlayerTests();
    doBoardTests2();
    doPlayerTest2();
    cout<<"pass all test"<<endl;
}
