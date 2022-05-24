//
//  linear.cpp
//  Homework3
//
//  Created by Jonathan on 2/9/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    // base case
    if( n <= 0 )
        return true;
    if( !somePredicate(a[0]))
        return false;
    else
        return allTrue(a+1, n-1); // serach the next n-1 string from a+1
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    // base case
    if( n <=0 )
        return 0;
    if ( n ==1 && !somePredicate(a[0]))
        return 1;
    // start recs
    int numfalse =0;
    if( !somePredicate(a[0]))
        numfalse=1;
    return numfalse+countFalse(a+1, n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    int index = -1; // default
    // base case
    if ( n <= 0 )
        return -1;
    // if curr a is false return already
    if(!somePredicate(a[0]))
        return 0;
    else
        index=firstFalse(a+1, n-1);
    
    if( index == -1 )
        return -1;
    else
        return 1+index;
    
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
    //base case
    if( n <=0 )
        return -1;
    if( n ==1 )
        return 0;
    int minIndex = indexOfLeast(a+1, n-1)+1; // this will give us the least index after curr
    if( a[0] <= a[minIndex]){
        return 0; //return this curr index
    }
    else
        return minIndex; // since this is not least then ret shoud be 1+ up do min Index
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
    // base case
    if( n2 <=0 )
        return true;
    if( n2 > n1 ) // n2 dont fit n1
        return false;
    // this is simple just check if curr1 are the same as curr2
    if( a1[0] == a2[0])
    {
        // if this curr is same, start from this index in a1 and serahc a2 next
        return includes( a1+1 , n1-1, a2+1, n2-1);
    }else
    {  // move on to a1+1 and search a2[0] again
        return includes(a1+1, n1-1, a2, n2);
    }
}

