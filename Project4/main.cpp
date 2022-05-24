//
//  main.cpp
//  Project4
//
//  Created by Jonathan on 6/3/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <iostream>
#include <iostream>
#include <fstream>
#include <istream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "BSTtree.h"
using namespace std;

const int N = 8;


/*
 Read in the entire contents of the old file into a string. Read the entire contents of the new file into another string.
 For all consecutive N-character sequences in the old file's string, insert that N-character sequence and the offset F where it was found in the old file's string, into a table (e.g. hash table or binary search tree). You might use 8 for N, or maybe 16.
 Once you have filled up your table with all N-byte sequences from the source file, start processing the new file's string, starting from offset j=0, until j reaches the end of the string.
 Look up the N-byte sequence which starts at offset j ([j,j+N-1]) in the new file's string in the table you created from the old file's string.
 If you find this sequence in the table, you know that that sequence is present in both the old and new versions of the file.
 Determine how long the match goes on (it might be just N bytes long, or it might extend past the first N matching bytes to be many bytes longer).
 Once you have determined how long the match is (call this L), write a Copy instruction to the diff file to copy L bytes from offset F from the source file.
 Go back to step 3a, continuing at offset j = j + L in the new file's string.
 If you don't find the current sequence (new file's string [j,j+N-1]) in the table you created, you know that the first version of the file doesn't contain the current N byte sequence.
 Write an instruction to the diff file to Add the current character.
 Increment j by one to continue past the character used in the add instruction.
 Go back to step 3a, where we'll try to find the next N-byte sequence in our table.
 
 */
bool myfunction (string i,string j) { return (i<j); }

string loadFile( istream& fin)
{
    string myline;
    string mytxt;
    while( getline(fin,myline))
        mytxt+=(myline+'\n');
    return mytxt;
}

void collectPattern( string orgtxt, int N)
{
    BSTtree mytree;
    string pattern;
    long len = orgtxt.size();
    int N_SUB =N;
    long actlen= len-N_SUB;
    for( int i = 0 ; i < actlen ; i++)
    {
        pattern=orgtxt.substr(i,N_SUB);
        mytree.insert(pattern, i);
        //cout<<pattern<<endl;
    }
    //    /////////////////////////////////
    //    // fun1
    //    /////////////////////////////////
    //    for( int i = 0 ; i < len-N_SUB ; i++)
    //    {
    //        string pattern;
    //        for( int j =0 ; j < N_SUB;j++)
    //        {
    //            pattern+= oldtxt[i+j];
    //        }
    //        patterTable.push_back(pattern);
    //        cout<<pattern<<endl;
    //    }
    //    /////////////////////////////////
    //    // fun2
    //    /////////////////////////////////
    //    string pattern;
    //    for( int i = 0 ; i < len-N_SUB ; i++)
    //    {
    //        if( i == 0 )
    //        {
    //            for( int j =0 ; j < N_SUB ; j++)
    //                pattern+=oldtxt[i+j];
    //        }else if( i < len-(N_SUB-1) )
    //        {
    //             // reassoiatate
    //            pattern = pattern.substr(1);
    //            pattern+=oldtxt[i+(N_SUB-1)];
    //        }
    //        cout<<pattern<<endl;
    //    }
    // mytree.inorderprint();
}

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    // read in the files
    string oldtext = loadFile(fold);
    string newtext = loadFile(fnew);
    //
    int foundOffset=-1;
    // collect all  substring from old file
    BSTtree mytable;
    long len = oldtext.size();
    long actlen= len-N;
    for( int i = 0 ; i <= actlen ; i++)
    {
        string pattern= oldtext.substr(i,N);
        mytable.insert(pattern, i);
        //cout<<pattern<<endl;
    }
    
    // mytable.inorderprint();
    //start the matching
    long newFile_size = newtext.size();
    for(int offset_n = 0; offset_n < newFile_size; )
    {
        // for [j,j+N-1]
        string curr_new_sub = newtext.substr(offset_n, N);
        // look up the substring in out tabel
        record matchNode;
        int offset_source = mytable.search(curr_new_sub, matchNode);
        
        // if found the pattern in the table
        if( offset_source != -1)
        {
            // safe to access matchNode
            
            //cout<<repeatSub<<endl;
            // this means the pattern has more than once
            // we want LCS
            int size = matchNode.otSet.size();
            int maxLen =0;
            for( int se=0 ; se < size ; se++)
            {
                int L=0;
                int index_n = offset_n;
                int index_s = matchNode.otSet[se];
                while( newtext[index_n+L] == oldtext[index_s+L])
                {
                    L++;
                    if( index_n+L >= newFile_size || index_s+L >= oldtext.size() )
                        break;
                }
                if( L > maxLen)
                {
                    maxLen = L;
                    foundOffset = index_s;
                }
                
            } // end for
             cout<<"C"<<maxLen<<","<<foundOffset<<endl;;    //print copy command to delta file
            fdiff<<"C"<<maxLen<<","<<foundOffset;
            offset_n+=maxLen;
        }
        else
        {
            // we didnt find any patern match ,,,
            int L = 0;
            curr_new_sub=(newtext.substr(offset_n+L, N));
            
            while(mytable.search(curr_new_sub, matchNode)==-1 && offset_n+L< newFile_size)
            {
                L++;
                curr_new_sub=(newtext.substr(offset_n+L, N));
            }
            // cout<<"A"<<L<<":"<<newtext.substr(offset_n, L)<<endl;  //print add command to delta file
            fdiff<<"A"<<L<<":"<<newtext.substr(offset_n, L);
            cout<<"A"<<L<<":"<<newtext.substr(offset_n, L);
            offset_n+=L;
        }
        
    }
    
} // end create diff

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
    cout<<" reached applied diff"<<endl;
    //read in the files
    string source  = loadFile(fold);
    string diffcommand = loadFile(fdiff);
    //size of files
    //  long size_diff = diffcommand.size();
    long size_sourece = source.size();
    // some formate
    //  C(len),(offset)
    //  A(len),(substring)
    
    // A3:xyz.....C0,24
    // C12,2A1:A
    // Before get into the loop
    if( diffcommand[0] != 'A' && diffcommand[0] != 'C') // must start with A or C
        return false;
   // cout<<"crash here"<<endl;
    //a character other than an A or C where an instruction is expected,
    //or an offset or length is invalid), the function returns false.
    
    while( diffcommand.size() > 0 )
    {
        
        char exam = diffcommand[0]; //must always start with either A or C
        switch (exam)
        {
            case 'A':
            {
                // compute len if possible
                diffcommand = diffcommand.substr(1);
                char next = diffcommand[0];
                // A5:abcde
                //  ^
                // while hasnextdigit compute
                int addlen =0;
                if( isdigit(next))
                {
                    while( isdigit(next) && diffcommand.size())
                    {
                        addlen = addlen*10+(next-'0');
                        diffcommand =diffcommand.substr(1);
                        next=diffcommand[0];
                    }
                }else
                {
                    cerr<<"Add must follow a valid len "<<endl;
                    return false;
                }
                // after the number it should follow :
                //                cout<<"add len "<<addlen<<endl;
                string addstr;
                if(diffcommand[0] == ':' && diffcommand.size())
                {
                    // remove :
                    diffcommand =diffcommand.substr(1);
                    // now should be safe to compute our string
                    addstr = diffcommand.substr(0,addlen);
                    // to prepare for next iteration
                    if( addlen < diffcommand.size()){
                        cout<<"=B=>"<<diffcommand<<endl;
                        cout<<"==>"<<addlen<<endl;
                        diffcommand=diffcommand.substr(addlen);
                        cout<<"=A=>"<<diffcommand<<endl;
                        cout<<"=== === === === === === === === \n ";
                    }
                    else{
                        cout<<" false here "<<endl;
                        return false;
                    }
                }else
                {
                    cerr<<"Add must start string with ':' after len"<<endl;
                    return false;
                }
                //cout<<"add "<<addlen<<" with "<<addstr<<endl;
                fnew<<addstr;
                break;
            }
            case 'C':
            {
                //copy
                char next;
                int  cpylen = 0;
                int  offset = 0;
                // compute len if possible
                diffcommand = diffcommand.substr(1);
                next = diffcommand[0];
                // A5:abcde
                //  ^
                // while hasnextdigit compute
                if( isdigit(next))
                {
                    while( isdigit(next) && diffcommand.size())
                    {
                        cpylen = cpylen*10+(next-'0');
                        diffcommand =diffcommand.substr(1);
                        next=diffcommand[0];
                    }
                }else
                {
                    cerr<<"Copy must follow a valid len "<<endl;
                    return false;
                }
                
                // after the number it should follow ,
                string addstr;
                if(diffcommand[0] == ',' && diffcommand.size())
                {
                    // remove ,
                    diffcommand =diffcommand.substr(1);
                    next = diffcommand[0];
                    // A5:abcde
                    //  ^
                    // while hasnextdigit compute
                    if( isdigit(next))
                    {
                        while( isdigit(next) && diffcommand.size())
                        {
                            offset = offset*10+(next-'0');
                            diffcommand =diffcommand.substr(1);
                            next=diffcommand[0];
                        }
                    }else
                    {
                        cerr<<", must follow a valid offset "<<endl;
                        return false;
                    }
                }else
                {
                    cerr<<"Copy must have , before offset"<<endl;
                    return false;
                }
                // copy len from offset
                //cout<<"copy "<<cpylen<<" at "<<offset<<endl;
                if( cpylen-offset > size_sourece )
                    return false;
                string copystr= source.substr(offset,cpylen);
                fnew<<copystr;
                break;
            }
            case'\n':
            case'\r':
            {
                //cerr<<"we do nothing"<<endl;
                diffcommand =diffcommand.substr(1);
                break;
            }
            default: // bad case
            {
                cout<<"bad "<<endl;
            return false;
                
            }
        }
    }
    return true;
}

//int main(int argc, const char * argv[]) {
//    // insert code here...
//    ifstream infilea1("/Users/jonathan/Desktop/test/a2.txt");
//    ifstream infilea2("/Users/jonathan/Desktop/test/mynewfile2.txt.txt");
//    ofstream diff("/Users/jonathan/Desktop/test/diff.txt");
//    ofstream newfile("/Users/jonathan/Desktop/test/newa1a2.txt");
//    //createDiff(infilea1, infilea2, diff);
//    diff.close();
//    infilea1.clear();   // clear the end of file condition
//    infilea1.seekg(0);  // reset back to beginning of the stream
////    cout<<"divider!!\n\n"<<endl;
//    ifstream inputdiff("/Users/jonathan/Desktop/test/baddiff.txt");
//    inputdiff.clear();
//    inputdiff.seekg(0);
//    applyDiff(infilea1, inputdiff, newfile);
//    return 0;
//}

//int main(int argc, const char * argv[])
//{
//    BSTtree *tree = new BSTtree();
//    tree->insert("j",1);
//    tree->insert("k",2);
//    tree->insert("a",3);
//    tree->insert("b",4);
//    tree->insert("z",5);
//    tree->insert("i",6);
//    tree->insert("j",7);
//    tree->inorderprint();
//    record returnNode;
//    cout<<tree->search("a",returnNode );
//    cout<<returnNode.m_pattern<<endl;
//    cout<<returnNode.getCount()<<endl;
//    cout<<returnNode.otSet.size()<<endl;
//    delete tree;
//
//
//}
bool runtest(string oldName, string newName, string diffName, string newName2)
{
    if (diffName == oldName  ||  diffName == newName  ||
        newName2 == oldName  ||  newName2 == diffName  ||
        newName2 == newName)
    {
        cerr << "Files used for output must have names distinct from other files" << endl;
        return false;
    }
    ifstream oldFile(oldName, ios::binary);
    if (!oldFile)
    {
        cerr << "Cannot open " << oldName << endl;
        return false;
    }
    ifstream newFile(newName, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName << endl;
        return false;
    }
    ofstream diffFile(diffName, ios::binary);
    if (!diffFile)
    {
        cerr << "Cannot create " << diffName << endl;
        return false;
    }
    createDiff(oldFile, newFile, diffFile);
    diffFile.close();

    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the file
    ifstream diffFile2(diffName, ios::binary);
    if (!diffFile2)
    {
        cerr << "Cannot read the " << diffName << " that was just created!" << endl;
        return false;
    }
    ofstream newFile2(newName2, ios::binary);
    if (!newFile2)
    {
        cerr << "Cannot create " << newName2 << endl;
        return false;
    }
    assert(applyDiff(oldFile, diffFile2, newFile2));
    newFile2.close();

    newFile.clear();
    newFile.seekg(0);
    ifstream newFile3(newName2, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName2 << endl;
        return false;
    }
    if ( ! equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
    {

        cerr << newName2 << " is not identical to " << newName
        << "; test FAILED" << endl;
        return false;
    }
    return true;
}

int main()
{
    assert(runtest("/Users/jonathan/Desktop/test/f_hamlet1.txt", "/Users/jonathan/Desktop/test/f_hamlet2.txt", "/Users/jonathan/Desktop/test/f_hamlet_diff.txt", "/Users/jonathan/Desktop/test/updatef_hamlet.txt"));
    //runtest("/Users/jonathan/Desktop/test/f_warandpeace1.txt", "/Users/jonathan/Desktop/test/f_warandpeace2.txt", "/Users/jonathan/Desktop/test/f_f_warandpeace_diff.txt", "/Users/jonathan/Desktop/test/updatef_warandpeace.txt");
    cerr << "Test PASSED" << endl;
}






