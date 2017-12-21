#include "parser.h"

void Parser::readFromFile(const char *fname) {
    ifstream mFile("PUZ001-1.p");
    string currentString;
        while (getline(mFile, currentString))
            text.push_back(currentString);
}

void Parser::parseCNF(int i) {
    transformToOne_lineCNF(i);
    disjuncts.push_back(Disjunct().buildDisjunct(cnfs[cnfs.size() - 1]));
}

void Parser::transformToOne_lineCNF(int i) {
    string currentString = "";
    for (;;++i)
        for (int j = 0; j < text[i].size(); ++j) {
            if (text[i][j] == '.') {
                cnfs.push_back(currentString);
                currentString = "";
                return;
            }
            else if (text[i][j] != '\n' && text[i][j] != ' ')
                currentString += text[i][j];
            else if (text[i][j] == '\n')
                continue;
        }
}

void Parser::printCnfs() {
    for (int i = 0; i < cnfs.size(); ++i) {
        for (int j = 0; j < cnfs[i].size(); ++j)
            cout << cnfs[i][j];
        cout << endl;
    }
}

void Parser::parse(const char *file) {
    readFromFile(file);
    for (int i = 0; i < text.size(); ++i) {
        if (text[i][0] == '%')
            continue;
        if (text[i].size() < 3 || text[i][0] == ' ')
            continue;
        if (text[i].substr(0, 3) == "cnf")
            parseCNF(i);
    }
    printCnfs();
}


