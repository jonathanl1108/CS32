//
//  ScoreList.cpp
//  Homework1
//
//  Created by Jonathan on 4/13/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#include "ScoreList.h"

// Create an empty score list.
ScoreList::ScoreList()
{}

bool ScoreList::add(unsigned long score)
{
    if( score > 100 || size() >= DEFAULT_MAX_ITEMS)
        return false;
    m_scorelist.insert(score);
    return true;
}
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.

bool ScoreList::remove(unsigned long score)
{
    return m_scorelist.erase(m_scorelist.find(score));
}
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.

int ScoreList::size() const
{
    return m_scorelist.size();
}  // Return the number of scores in the list.

unsigned long ScoreList::minimum() const
{
    if( m_scorelist.empty())
        return NO_SCORE;
    unsigned long value;
    m_scorelist.get(0, value);
    return value;
}
// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.

unsigned long ScoreList::maximum() const
{
    if( m_scorelist.empty())
        return NO_SCORE;
    unsigned long value;
    m_scorelist.get(size()-1, value);
    return value;
}
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
