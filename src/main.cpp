#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main()
{
    auto fileContentsToString = [](ifstream & is)
    {
        string contents;
        for (char ch; is.get(ch); contents.push_back(ch))
        {
        };
        return contents;
    };

    auto find_and_replace = [](string & file_contents, const string &word_find, const string &word_replace)
    {
        auto pos = file_contents.find(word_find);
        while (pos != string::npos)
        {
            file_contents.replace(pos, word_find.length(), word_replace);
            pos = file_contents.find(word_find, pos);
        }
        return 0;
    };


    ifstream filein("../tests/main.py");
    ofstream fileout("../tests/alias.py");
    ifstream coFile;
    string s;
    string c;

    unordered_map<string, string> variables_table;

    // Opening the file ->
    // While accessing it's contents
    /* inFile.open("C:\\Users\\insom\\Desktop\\PyAlias\\tests\\main.py");
    coFile.open("C:\\Users\\insom\\Desktop\\PyAlias\\tests\\config.alias"); */

    if (!coFile)
    {
        cerr << "Failed to load config.alias" << endl;
        exit(1);
    }

    int count;
    count = 0;
    string lastKey;

    while (coFile >> s)
    {
        if (count % 2 == 0)
        {
            variables_table.insert({s, ""});
            lastKey = s;
        }
        else
        {
            variables_table[lastKey] = s;
            lastKey = "";
        }
        count++;
    }

    string file_contents;

    file_contents = fileContentsToString(filein);

    for (pair<string, string> element : variables_table)
    {
        cout << element.first << " :: " << element.second << endl;
        find_and_replace(file_contents, element.first, element.second);
    }

    fileout << file_contents;

    return 0;
}