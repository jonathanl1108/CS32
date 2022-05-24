//
//  testScoreList.cpp
//  Homework1
//
//  Created by Jonathan on 4/13/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#include "ScoreList.h"
#include "Sequence.h"
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

int main()
{
    ScoreList myList;
    assert(myList.add(65));
    assert(myList.add(100));
    assert(myList.add(85));
    assert(!myList.add(-100));
    assert(!myList.add(10000));
    assert(myList.maximum() == 100);
    assert(myList.minimum() == 65);
    assert(myList.size() == 3);
    cerr<<"pass all test"<<endl;
}
