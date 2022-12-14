/* 
* C++ program to create a basic search engine 
* Takes one or more words as input and returns all the url's those words appear in.
*/

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

// This function lower cases all characters in a string and removes any leading and trailing punctuation from the string
// This function takes in a string containing a single token as a parameter
// This function returns that string all characters lower case and without any leading and trailing punctuation
string cleanToken(string s) {
    // To immediately return an empty string if there are no characters
    if(any_of(s.begin(), s.end(), ::isalpha) == false)
    {
        return "";
    }

    // getting rid of punctuation starting from the start of the string
    for(int i = 0; i < s.size(); i++)
    {
        i = 0;
        if(ispunct(s[i]) != 0)
        {
            s.erase(i, 1);
        }
        else
        {
            break;
        }
    }

    // getting rid of punctuation starting from the end of the string
    for(int i = s.size() - 1; i >= 0; i--)
    {
        i = s.size() - 1;
        if(ispunct(s[i]) != 0)
        {
            s.erase(i, 1);
        }
        else
        {
            break;
        }
    }
    
    // converts all characters in string s to lowercase 
    transform(s.begin(), s.end(), s.begin(), ::tolower);

    return s;
}// end of function cleanToken


// This function takes all the unique tokens in a body of text and puts them into a set
// This function takes a string containing the body of text as a parameter
// This function returns a set containing all the unique tokens in the body of text
set<string> gatherTokens(string text) {
    set<string> tokens;
    stringstream sStream(text);
    string temp;
    string clean;

    while(!sStream.eof())
    {
        getline(sStream, temp, ' ');
        clean = cleanToken(temp);
        if(clean == "")
        {
            continue;
        }
        tokens.insert(clean);
    }
    return tokens; 
}// end of function gatherTokens


// This function builds an inverted index from of the data inside the file the user inputed
// This function takes a string containing the name of the file and a empty map to populate the inverted index with as parameters
// This function returns the number of documents processed from the file
int buildIndex(string filename, map<string, set<string>>& index) {
    string fileLine;
    ifstream inFs;
    string url;
    int pages = -1;
    int uniqueTerms = 0;

    inFs.open(filename);// opening file
    
    // checking to see if file opened
    if(!inFs.is_open()){
        return 0; 
    }

    //looping until end of file
    while(!inFs.eof())
    {
        // get URL
        getline(inFs, fileLine, '\n');
        url = fileLine;
        pages++;

        // get body of text
        getline(inFs, fileLine, '\n');

        // loop through set made by gatherTokens() and assign each token into the map
        for (auto i : gatherTokens(fileLine))
        {
            // insert into map
            index[i].insert(url);
        }
    }

    cout << "Stand by while building index..." << endl;

    //output pages and uniqueTerms
    cout << "Indexed " << pages << " pages containing " << index.size() <<  " unique terms" << endl << endl;

    inFs.close(); // closing file

    return pages;
}// end of function buildIndex


// This function creates a set that contains all the url's that have the term/terms the user searched for inside them
// This function takes a string containing the term/terms the user wants to search for inside the inverted index as parameters
// This function returns a set containing all the url's that have the searched for term/terms inside them
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    set<string> tempSet;
    stringstream sStream(sentence);
    string temp;
    string cleanWord;
    string firstWord;

    getline(sStream, temp, ' '); // get the first word in sentence
    cleanWord = cleanToken(temp);
    firstWord = cleanWord;

    for(auto i : index[firstWord])
    {
        tempSet.insert(i);
    }

    while(!sStream.eof())
    {
        getline(sStream, temp, ' ');

        if(temp[0] == '+')
        {
            cleanWord = cleanToken(temp);
            result.clear();
            set_intersection(tempSet.begin(), tempSet.end(), index[cleanWord].begin(), index[cleanWord].end(), std::inserter(result, result.begin()));
        }

        if(temp[0] == '-')
        {
            cleanWord = cleanToken(temp);
            result.clear();
            set_difference(tempSet.begin(), tempSet.end(), index[cleanWord].begin(), index[cleanWord].end(), std::inserter(result, result.begin()));
        }

        if(temp[0] != '+' && temp[0] != '-')
        {
            cleanWord = cleanToken(temp);
            result.clear();
            set_union(tempSet.begin(), tempSet.end(), index[cleanWord].begin(), index[cleanWord].end(), std::inserter(result, result.begin()));
        }

        tempSet.clear(); // clear tempSet

        // make tempSet equal to result
        for(auto i : result)
        {
            tempSet.insert(i);
        }
        
    }

    // for if only one word is in the input
    if(result.size() == 0)
    {
        for(auto i : index[firstWord])
        {
            result.insert(i);
        }
    }

    //output the set result
    cout << "Found " << result.size() << " matching pages for "<< sentence << endl;
    for (auto itr : result)
    {
        cout << itr << endl;
    }
    
    return result; 
}// end of function findQueryMatches


// This function takes the input and calls the functions necessary for the program to run
// This function takes a string containing the name of the file that the user wants to make the inverted index from as a parameter
// This function does not return anything
void searchEngine(string filename) {
    cin.ignore();
    map<string, set<string>> index;
    string sentence;

    // to call the buildIndex function and end the program if a invalid filename is provided
    if(buildIndex(filename, index) == 0)
    {
        return;
    }

    // instructions for how to properly input one or more words
    cout << "Here are some examples of how to seach for one or more words:" << endl;
    cout << "   Word" << endl;
    cout << "      matches all pages containing the term Word" << endl;
    cout << "   Word1 Word2" << endl;
    cout << "      means Word1 OR Word2" << endl;
    cout << "      matches pages that contain either Word1 or Word2 or both" << endl;
    cout << "   Word1 +Word2" << endl;
    cout << "      means Word1 AND Word2" << endl;
    cout << "      matches pages that contain both Word1 and Word2" << endl;
    cout << "   Word1 -Word2" << endl;
    cout << "      means Word1 WITHOUT Word2" << endl;
    cout << "      matches pages that contain Word1 but do not contain Word2" << endl;
    cout << "   Word1 -Word2 Word3 +Word4" << endl;
    cout << "      means Word1 WITHOUT Word2 OR Word3 AND Word4" << endl;
    cout << "      matches pages that match (((Word1 without Word2) or Word3) and Word4)";
    cout << endl << endl;

    while(true)
    {
        cout << "Please type in one or more words in the format specified in the examples above and then press enter to search (press enter without typing a word to quit): ";
        getline(cin, sentence);
        if(sentence.size() > 0)
        {
            findQueryMatches(index, sentence);
            cout << endl;
        }
        else
        {
            cout << "Thank you for searching!";
            break;
        }
    }
}// end of function searchEngine