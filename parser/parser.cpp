#include "parser.h"

void Parser::readFromFile(const char *fname) {
    ifstream mFile("PUZ009-1.p");
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

bool Parser::resolution() {
    bool isFind = false;
    for (int i = 0; i < disjuncts.size(); ++i) {
        if (isFind)
            --i;
        isFind = false;
        vector <Literal> merger;
        merger.clear();
        vector <Literal> literals = disjuncts[i].getLiterals();
        int comparedLiteralsIndex = -1;
        for (int j = 0; j < literals.size(); ++j) {
            for (int k = 0; k < disjuncts.size(); ++k) {
                if (i == k)
                    continue;
                vector <Literal> comparedLiterals = disjuncts[k].getLiterals();
                for (int l = 0; l < comparedLiterals.size(); ++l) {
                    if (Literal::isContradictory(literals[j], comparedLiterals[l])) {
                        merger = Disjunct::merge(literals, comparedLiterals);
                        if (merger.empty())
                            return true;
                        comparedLiteralsIndex = k;
                        isFind = true;
                        break;
                    }
                }
                if (isFind)
                    break;
            }
            if (isFind)
                break;
        }
        if (isFind) {
            disjuncts.erase(disjuncts.begin() + i);
            disjuncts.erase(disjuncts.begin() + comparedLiteralsIndex - 1);
            disjuncts.push_back(Disjunct(merger));
            merger.clear();
        }
    }
    for (int i = 0; i < disjuncts.size(); ++i) {
        vector <Literal> literals = disjuncts[i].getLiterals();
        if (literals.size() == 0)
            return true;
    }
    return false;
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
    cout << resolution() << endl;
//    printCnfs();
}


