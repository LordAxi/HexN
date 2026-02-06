#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <boost/tokenizer.hpp>

using namespace std;

namespace fi {
    string input;
    string input_0;
    string input_1;
}

string removeSpaces(string input)
{
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}

std::vector<std::string> splitLine(const std::string& line) {
    std::vector<std::string> row;
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ','))
        row.push_back(removeSpaces(cell));
    if (!ss && cell.empty())
        row.push_back("");
    return row;
}

vector<vector<string>> loadAsciiTable(const std::string& path) {
    vector<vector<string>> table;
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line))
        table.push_back(splitLine(line));
    return table;
}

vector<vector<string>> asciiTable = loadAsciiTable("ascii_tabel.csv");

std::vector<std::string> getTableRow(std::string type) {

    vector<string> tableRow = {};

    int row = 0;

    if (type == "dec") {
        row = 0;
    } else if (type == "hex") {
        row = 1;
    } else if (type == "oct") {
        row = 2;
    } else if (type == "bin") {
        row = 3;
    } else if (type == "ascii") {
        row = 4;
    } else {
        cout << "Invalid charset arg" << endl;
        return tableRow;
    }

    for (int i = 0; i <= 0x7F; i++) {
        tableRow.push_back(asciiTable[i][row]);
    }

    return tableRow;
}

int main(void) {
    
    string delimiter = " ";

    cout << "============= HEX N =============" << endl;
    cout << "Info: The ASCII Tabel is used, and\nyou have to write the full-degit-number." << endl;
    cout << "Example: 0x00 | 0b0 = wrong, 0b00000000 = correct." << endl;
    cout << "Choose two systems [bin, oct, dec, hex, ascii]." << endl;

    getline(cin, fi::input);

    size_t p = fi::input.find(' ');
    fi::input_0 = fi::input.substr(0, p);
    fi::input_1 = fi::input.substr(p + 1);

    vector array_0 = getTableRow(fi::input_0);
    vector array_1 = getTableRow(fi::input_1);

    cout << "You chose: " << fi::input_0 << " and " << fi::input_1 << endl;
    cout << "Do you want to learn(0), or translate(1)?" << endl;

    string input; cin >> input;

    if (input == "0") {
        cout << "=================================" << endl;
        cout << "Learning-Mode!" << endl;

        string guess;

        while (1) {
            cout << "=================================" << endl;
            cout << "Use 'exit' to exit learn mode." << endl;
            cout << "=================================" << endl;

            int i = (rand()%0x80);

            cout << "Whats the " << fi::input_0 << "-value of " << fi::input_1 << "-" << array_1[i] << "?" << endl;
        
            cin >> guess;

            if (guess == "exit") break;
            
            cout << "You guessed: " << guess << endl;

            if (guess == array_0[i]) {
                cout << "Correct!" << endl;
            } else {
                cout << "Wrong!" << endl;
                cout << "Correct answer: " + array_0[i] << endl;
            }
        }
    }

    if (input == "1") {
        cout << "=================================" << endl;
        cout << "Translate-Mode!" << endl;

        string raw_str;
        string out_str;

        while (1) {
            cout << "=================================" << endl;
            cout << "Use 'exit' to exit translate mode." << endl;
            cout << "=================================" << endl;

            cout << "Which " << fi::input_0 << " value\ndo you want to translate to " << fi::input_1 << endl;
            cout << "Choose a value to translate. " << endl;
            cin >> raw_str;

            if (raw_str == "exit") break;

            size_t array_0_size = array_0.size();

            bool found = false;

            for (int i = 0; i < array_0_size; i++) {
                if (raw_str == array_0[i]) {
                    cout << "Your value: " << raw_str << endl;
                    cout << "Tras value: " << array_1[i] << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Invalid input" << endl;
            }
        }
    }
}
