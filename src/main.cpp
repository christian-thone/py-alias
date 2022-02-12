#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main()
{
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

    ifstream filein("C:\\Users\\insom\\Desktop\\PyAlias\\tests\\main.py", fstream::in);
    ofstream fileout("C:\\Users\\insom\\Desktop\\PyAlias\\tests\\alias.py", fstream::out);
    ifstream coFile;
    string s;
    string c;

    unordered_map<string, string> variables_table;

    coFile.open("C:\\Users\\insom\\Desktop\\PyAlias\\tests\\config.alias", fstream::in);

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
            cout << "Created Key value pair: " << variables_table[lastKey] << " :: " << s << endl;
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

    cout << file_contents << endl;

    cout << file_contents.length() << endl;

    cout << "Reading main.py..." << endl;

    for (pair<string, string> element : variables_table)
    {
        cout << element.first << " :: " << element.second << endl;
        file_contents = find_and_replace(file_contents, element.first, element.second);
    }

    fileout << file_contents;

    fileout.close();

    return 0;
}