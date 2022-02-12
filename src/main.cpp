#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <filesystem>

using namespace std;

int main(int argc, char **argv)
{
    if (!(filesystem::path(argv[1]).extension() == ".py"))
    {
        cerr << "ERROR: " << argv[1] << "is not a python file!" << endl;
        exit(1);
    }
    if (!(filesystem::path(argv[2]).extension() == ".py"))
    {
        cerr << "ERROR: " << argv[2] << "is not a python file!" << endl;
        exit(1);
    }
    if (!(filesystem::path(argv[3]).filename() == "config.alias"))
    {
        cerr << "ERROR: Configuration files MUST be named 'config.alias' !" << endl;
        exit(1);
    }
    auto find_and_replace = [](string &file_contents, const string &word_find, const string &word_replace)
    {
        auto pos = file_contents.find(word_find);
        while (pos != string::npos)
        {
            file_contents.replace(pos, word_find.length(), word_replace);
            pos = file_contents.find(word_find, pos);
        }
        return file_contents;
    };

    cout << "Running script..." << endl;

    ifstream filein(argv[1], fstream::in);
    ofstream fileout(argv[2], fstream::out);
    ifstream coFile;
    string s;
    string c;

    unordered_map<string, string> variables_table;

    coFile.open(argv[3], fstream::in);

    if (!coFile)
    {
        cerr << "Failed to load config.alias" << endl;
        exit(1);
    }
    else
    {
        cout << "Successfully loaded config.alias" << endl;
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

    coFile.close();

    string file_contents;
    char ch;

    while (filein.get(ch))
    {
        file_contents += ch;
    }

    cout << "Reading main.py..." << endl;

    for (pair<string, string> element : variables_table)
    {
        file_contents = find_and_replace(file_contents, element.first, element.second);
    }

    fileout << file_contents;

    fileout.close();
    cout << "Script Finished Running." << endl;

    return 0;
}