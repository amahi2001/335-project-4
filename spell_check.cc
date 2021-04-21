// Abrar Mahi.

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int testSpellingWrapper(int argument_count, char **argument_list)
{
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);
    HashTable<string> dictionary; //instantiating dictionary hash table
    string line, word, temp, arr = " -> ";
    bool apostrophe = false; //checks if there's an apostrophe in the word

    //opening document and dictionary files and printing error messaged if either of them fail to open
    ifstream doc(document_filename), dict(dictionary_filename);;
    if (doc.fail())
    {
        cerr << "couldn't open document file" << endl;
        exit(1);
    }
    if (dict.fail())
    {
        cerr << "couldn't open dictionary file" << endl;
        exit(1);
    }

    //inserting words from dictionary into hash table
    while (dict >> line)
    {
        dictionary.Insert(line);
    }

    //checking words for apostrophes and turning letters lowercase
    while (doc >> line)
    {
        //creating an empty string
        word = "";

        //traversing through the letters in each word
        for (auto x : line)
        {
            //setting each letter to be lowercase
            x = tolower(x);

            //if one of the chars is an apostrophe: set the flag to be true
            if ('\'' == x)
            {
                apostrophe = true;
            }

            //if the chars are all lowercase, add the letters to the empty string
            if ((x <= 'z') && (x >= 'a'))
            {
                word += x;
            }
        }

        //reset the temp string
        temp = word;

        //if there is no apostrophe
        if (apostrophe == false)
        {
            //if the hash table contains the temp word, print if it is correct
            if (dictionary.Contains(temp) == true)
            {
                cout << word << " is correct" << endl;
            }
            //else if the word doesn't exist in the hash table, print it isnt correct
            else
            {
                cout << word << " is not correct" << endl;
                int size = word.size();

                //for case a
                //iterate though the word and insert the correct character into the temp string
                for (int i = 0; i < (size + 1); i++)
                {
                    for (char c = 'z'; c >= 'a'; c--)
                    {
                        temp.insert(i, 1, c);

                        //if the hash table contains the newly changed temp string, print the corrected word
                        if (dictionary.Contains(temp) == true)
                        {
                            cout << word << arr << temp << " case a" << endl;
                        }
                        temp = word; //reset the temp string
                    }
                }

                temp = word; //resetting the temp string

                //for case b: traverse through the word
                for (int i = 0; i < size; i++)
                {
                    //remove the incorrect letter from the word
                    temp.erase(i, 1);
                    //if the hash table contains the newly changed temp string, print the corrected word
                    if (dictionary.Contains(temp) == true)
                    {
                        cout << word << arr << temp << " case b" << endl;
                    }

                    temp = word; //resetting the temp string
                }

                //for case c: traverse through the word
                for (int i = size - 1; i >= 0; i--)
                {
                    //swap the incorrectly placed letters that are next to eachother
                    swap(temp[i + 1], temp[i]);

                    //if the hash table contains the newly changed temp string, print the corrected word
                    if (dictionary.Contains(temp) == true)
                    {
                        cout << word << arr << temp << " case c" << endl;
                    }
                    temp = word; //resetting the temp string
                }
            }
        }
        apostrophe = false; //reset the flag to be false
    }

    doc.close(), dict.close(); //closing the files

    // Call functions implementing the assignment requirements.
    // HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    // SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
             << endl;
        return 0;
    }

    testSpellingWrapper(argc, argv);

    return 0;
}
