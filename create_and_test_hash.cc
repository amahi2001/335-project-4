// YOUR NAME.

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename)
{
    cout << "TestFunctionForHashTables..." << endl;
    cout << "Words filename: " << words_filename << endl;
    cout << "Query filename: " << query_filename << endl;

    string str;
    ifstream word(words_filename); //opeing the file of words, and setting error message
    if (word.fail())
    {
        cerr << "can't read words file" << endl;
        exit(1);
    }

    while (getline(word, str))
    {
        hash_table.Insert(str); // inserting all the words into the hash table
    }

    ifstream query(query_filename); //opening query file and setting an error message
    if (query.fail())
    {
        cerr << "unable to open  query_filename" << endl;
        exit(1);
    }

    //setting #of total elements, size of table and #of collisions into floating point vars
    float totalElements = hash_table.getTotalElements(), 
          tableSize = hash_table.getArraySize(),
          collissions = hash_table.getCollissions();
          
    //calculating the load factor and average collisions and setting them into floating point vars
    float lambda = (totalElements / tableSize),
          averageCollissions = (collissions / totalElements);

    //printint out following values
    cout << "Number of items: " << hash_table.getTotalElements() << endl;
    cout << "Size of hash table: " << hash_table.getArraySize() << endl;
    cout << "Load factor: " << lambda << endl;
    cout << "Average number of collisions: " << averageCollissions << endl;
    cout << "Total number of collisions: " << hash_table.getCollissions() << endl;

    hash_table.resetCollissions(); //resetting the collisions in the hash table

    //setting the lines from query files into a string
    while (getline(query, str))
    {
        // if the hash table doesn't contain the string, pring the following message
        if (!hash_table.Contains(str))
        {
            cout << str << " Not_Found " << hash_table.getCollissions() + 1 << endl;

            hash_table.resetCollissions(); //reset the collisions in the hash table
        }
        //else if the hash table does 
        else 
        {
            cout << str << " Found " << hash_table.getCollissions() + 1 << endl;

            hash_table.resetCollissions();
        }
    }

    word.close(), query.close(); //closing the files
}

// namespace PROTECTED {

int testHashingWrapper(int argument_count, char **argument_list)
{
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 2;
    if (argument_count == 5)
    {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }

    if (param_flag == "linear")
    {
        cout << "Linear:" << endl;
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "quadratic")
    {
        // cout << "Quadratic:" << endl;
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "double")
    {
        cout << "Double:" << endl;
        cout << "r_value: " << endl;
        HashTableDouble<string> double_probing_table;
        double_probing_table.SetR(R);
        TestFunctionForHashTable(double_probing_table, words_filename,
                                 query_filename);
    }
    else
    {
        cout << "Unknown hash type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
    if (argc != 4 and argc != 5)
    {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}

//};  // namespace PROTECTED
