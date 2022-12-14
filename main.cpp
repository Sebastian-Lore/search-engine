/* 
* C++ program to create a basic search engine 
* Takes one or more words as input and returns all the url's those words appear in.
*/

#include <iostream>
#include "search.h"
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int main() {
    // instructions for how to use the program
    cout << "Welcome to my search engine program. ";
    cout << "In this program you will choose which file you would like to search. "; 
    cout << "You will then enter one or more words you would like to search. " << endl; 
    cout << "This program will then return all the relevant url's that contain the word or words you searched for." << endl;
    cout << "When entering more then one word you can preface a term with a + or a - " << endl;
    cout << "   By default when not prefaced with a + or a - the matches are unioned across search terms. (any result matching either term is included) " << endl;
    cout << "   If you preface a search term with a + then matches for this term are intersected with the existing results. (results must match both terms) " << endl;
    cout << "   If you preface a search term with a - then matches for this term are removed from the existing result. (results must match one term without matching the other) " << endl;
    cout << endl;

    cout << "List of filenames:" << endl;
    cout << "tiny.txt" << endl;
    cout << "cplusplus.txt" << endl;
    cout << "stackoverflow.txt" << endl;
    cout << "uiccs-news.txt" << endl;
    cout << "wiki-uni.txt" << endl;
    cout << "Please enter the name of one of the above files then press enter. (example: filename.txt): ";
    string filename;
    cin >> filename;
    searchEngine(filename);
    return 0;
}// end of main