
#include "Board.h"
#include <iostream>
using namespace std;
/*
 Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
 */
Board::Board(int nHoles, int nInitialBeansPerHole)
:num_hole_perside(nHoles),num_bean_perhole(nInitialBeansPerHole)
{
    if( num_hole_perside <= 0)
        num_hole_perside=1;
    if(num_bean_perhole < 0 )
        num_bean_perhole=0;
    total =(num_hole_perside+1)*2;
    
    // method
    /*
             N-----------------
             11 10  9  8  7
     N[0]                         S[6]
             1  2  3  4  5
             -------------------S
     */
    for( int i =0 ; i < total ; i++)
    {
        int num_insert = num_bean_perhole;
        if( i == 0 || i == total/2)
            num_insert =0;
        m_bord.push_back( num_insert);
    }
}
Board::Board( const Board& source)
{
    
   // first copy data memeber
     num_hole_perside = source.holes();
     num_bean_perhole = source.num_bean_perhole;
     total = source.total;
    
    // copy the vector
    for( int i=0 ; i < source.m_bord.size(); i++)
    {
        m_bord.push_back(source.m_bord[i]);
    }
}
int Board::holes() const
{
    return num_hole_perside;
}

//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beans(Side s, int hole) const
{
    if( hole < 0 || hole > num_hole_perside)
        return -1;
    int index = convertIndex(s, hole);
    return m_bord[index];
}
//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const
{
    int sum=0;
    //  start at 1, since we only want the sum of the bean in holes
    for( int hole = 1 ; hole <= num_hole_perside ; hole++)
        sum+=beans(s, hole);
    return sum;
}
//Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const
{
    int N_sum=0, S_sum=0;
    N_sum = m_bord[0]+beansInPlay(NORTH);
    S_sum = m_bord[total/2]+beansInPlay(SOUTH);
    return N_sum + S_sum;
}
/*
 
 Otherwise, it will return true after
 sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
 */
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    //If the hole indicated by (s,hole) is empty or invalid or a pot
    int bean_at_s_h=beans(s,hole);
    if(  bean_at_s_h == -1 || bean_at_s_h == 0 || hole == 0 /* hole 0 is pot */)
        return false;
    
    /* BOARD SET UP
     total= 14
     last index = total - 1
                     North
                     [13]  [12]  [11]  [10]  [9]  [8]
                     1     2    3     4     5    6
                     ----------------------------
                     b    b    b    b    b    b
     North's pot[0]                                   South's pot[7]
                     b    b    b    b    b    b
                     ----------------------------
                     1    2    3    4    5    6
                     [1]  [2]  [3]  [4]  [5]  [6]
                     South
     */
    // 2 cases to disscuss
    // "WITHIN" and "OUT"   our side_ bound
    // which is a dependent of the !!!! num_of_beans at ( s, h ) !!!!
    // NOTICE that with my set up,
    /*
     South will have   correct order  S1,S2,S3,S4,S5,S6....S[0] n6,n5,n4...
     sow --------------->->->->->->->->->--->-?->->->->->->->->->movement
     North will have   reversed order N6,N5,N4,N3,N2,N1....N[0] s1,s2,s3...
     */
    // Determine which case we have
    
    int source = convertIndex(s, hole);
    int curr_hole = source;
    if( s == SOUTH) // 1 2 3 4 5 6 .... total/2 skip m_board[0]
    {
        
        while( bean_at_s_h > 0)
        {
            curr_hole++; // start distribute from NEXT
            if( curr_hole >= total )
                curr_hole = 1; // hit the end of north re-start from S[1]
            m_bord[curr_hole]++;
            bean_at_s_h--;
            m_bord[source]--;
        }
    }else // NORTH 7 8 9 10 11 12 13 0 ..... skip m_borad[ total/2]
    {
        
        while( bean_at_s_h > 0)
        {
            curr_hole++; // start distribute from NEXT
            if( curr_hole == total/2)
                curr_hole++; // hit the end of south
            if( curr_hole >= total  )
                curr_hole = 0;
            m_bord[curr_hole]++;
            bean_at_s_h--;
            m_bord[source]--;
        }
    }
    if( curr_hole < 0)
    {
        return false;
    }
    
    if( (curr_hole > total/2 && curr_hole < total) || curr_hole == 0)
    {
        
        endHole= convertIndex(NORTH,curr_hole);
        if(endHole ==0 )
            endHole=POT;
        endSide=NORTH;
         return true;
    }else if( curr_hole >= 1 && curr_hole <= total/2 )
    {
        endHole=curr_hole;
        if( endHole == total/2)
            endHole=POT;
        endSide=SOUTH;
        return true;
    }
    return false; // some bad thing happend
}
//If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
bool Board:: moveToPot(Side s, int hole, Side potOwner)
{
    if( hole <=0 || hole > num_hole_perside)
        return false;
    // do the math
    if(potOwner == NORTH)
        m_bord[0]+=beans(s, hole);
    else
        m_bord[total/2]+=beans(s, hole);
    
    // clear
    m_bord[convertIndex(s, hole)]=0;
    return true;
}

//  If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
bool Board::setBeans(Side s, int hole, int beans)
{
    if ( hole < 0 || hole > num_hole_perside || beans < 0)
        return false;
    m_bord[convertIndex(s, hole)]=beans;
    return true;
}
void Board:: swap( vector<int>& s1,vector<int>& s2)
{
    for( int i =0 ; i <= num_hole_perside ; i++)
    {
        int temp = s1[i];
        s1[i] = s2[i];
        s2[i] = temp;
    }
}
int Board::convertIndex(Side s, int index) const
{
    if( s == SOUTH)
    {
        if( index == 0)
            return total/2;
        else
            return index;
    }
    else
    {
        if( index == 0)
            return 0;
        else
            return total - index;
    }
}

