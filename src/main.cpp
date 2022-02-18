#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <experimental/filesystem>
#include <sys/utsname.h>
#include <stdlib.h>

using namespace std;
using namespace experimental;

string inputFile;
string outputFile;
string configFile;

bool debugMode(false);

string usageExample = "\nEXAMPLE USAGE: \n pyalias [path_to_input_file] [path_to_output_file] [path_to_config_file]";

int getUserOS() {
    struct utsname name;
    if (uname( & name)) exit(-1);
    printf("\n%s@%s\n", name.sysname, name.release);
    return 1;
}

int initializeProject() {
    ofstream newFile("./config.alias");
    newFile << "> Use this file for your configuration";
    newFile.close();
}

int validateFiles(int argc, char ** argv) {
    getUserOS();
    if (debugMode == true) {
        cout << "Debug:" << endl;
        for (int i=0; i<argc; i++) {
            cout << "   -- argv[" << i << "] : " << argv[i] << endl;
        }
    }
    if (filesystem::path(argv[1]).extension() == ".py") {
        inputFile = argv[1];
        if (filesystem::path(argv[2]).filename() == "config.alias") {
            /* outputFile = argv[1];
            configFile = argv[2]; */
            cout << "\nWARNING: You must put all 3 files (input, output, configuration) in order for this script to work properly!  This feature will come soon!" << endl;
            cout << usageExample << endl;
            return 0;
        } else if (filesystem::path(argv[2]).extension() == ".py") {
            outputFile = argv[2];
            if (filesystem::path(argv[3]).filename() == "config.alias") {
                configFile = argv[3];
            }
            return 1;
        } else {
            return 0;
        }
        return 1;
    } else {
        return 0;
    }
    return 0;

}

string find_and_replace(string & file_contents,
    const string & word_find,
    const string & word_replace){
    cout << "Finding " << word_find << " | ";
    auto pos = file_contents.find(word_find);
    cout << "Found. Replacing with " << word_replace << " | ";
    while (pos != string::npos) {
        file_contents.replace(pos, word_find.length(), word_replace);
        pos = file_contents.find(word_find, pos);
    }
    cout << "Replaced." << endl;
    return file_contents;
};

unordered_map <string, string> loadConfig(string config_file_name) {
    int count;
    count = 0;
    string s;
    string lastKey;
    unordered_map <string, string> variables_table;
    ifstream conFile(config_file_name, fstream:: in );

    while (conFile >> s) {
        if (count % 2 == 0) {
            variables_table.insert({
                s,
                ""
            });
            lastKey = s;
        } else {
            variables_table[lastKey] = s;
            lastKey = "";
        }
        count++;
    }

    conFile.close();

    return variables_table;
}

int main(int argc, char ** argv) {

    if (debugMode == true) {
        cout << "Debug Mode: On" << endl;
    }

    if (validateFiles(argc, argv) == 0) {
        cout << "\nFailed to validate files passed in as parameters." << endl;
        return 1;
    }

    ifstream filein(inputFile, fstream:: in);
    ofstream fileout(outputFile, fstream::out);
    string s;
    string c;
    unordered_map < string, string > variables_table;

    variables_table = loadConfig(configFile);

    // ToDo: If no output file specified, use input file as output

    string file_contents;
    char ch;

    while (filein.get(ch)) {
        file_contents += ch;
    }

    cout << "\nReading '" << inputFile << "'..." << endl;

    for (pair < string, string > element: variables_table) {
        file_contents = find_and_replace(file_contents, element.first, element.second);
    }

    fileout << file_contents;
    fileout.close();

    cout << "Script Finished Running.\n" << endl;

    return 0;
}