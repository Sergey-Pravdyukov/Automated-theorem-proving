#include "parser.h"

void Parser::readFromFile(const char *fname) {
    ifstream mFile(fname);
    string currentString;
        while (getline(mFile, currentString))
            text.push_back(currentString);
    mFile.close();
    ofstream cout("test1.txt", ios_base::app);
}

void Parser::parseCNF(int i) {
    transformToOne_lineCNF(i);
    disjuncts.push_back(Disjunct().buildDisjunct(cnfs[cnfs.size() - 1]));
}

void Parser::transformToOne_lineCNF(int i) {
    string currentString = "";
    while (i != text.size()) {
        for (int j = 0; j < text[i].size(); ++j) {
            if (text[i][j] == '.') {
                cnfs.push_back(currentString);
                return;
            }
            if (text[i][j] != ' ' && text[i][j] != '\n')
                currentString += text[i][j];
        }
        ++i;
    }
}

void Parser::printCnfs() {
    ofstream cout("test1.txt", ios_base::app);
    for (int i = 0; i < cnfs.size(); ++i) {
        for (int j = 0; j < cnfs[i].size(); ++j)
            cout << cnfs[i][j];
        cout << endl;
    }
    cout << endl << endl;
    cout.close();
}

void printMerge (Disjunct merge) {
    ofstream cout("test1.txt", ios_base::app);
    if (!merge.isEmpty()) {
        cout << "Merged disjunct:" << endl;
        merge.print();
    }
    else
        cout << "Merged disjunct is empty. Formula is universaly valid. The statement is true." << endl;
    cout << endl << endl << "------------------------------------------------------------" << endl;
    cout.close();

}

void printContradictoryDisjuncts (Disjunct a, Disjunct b) {
    ofstream cout("test1.txt", ios_base::app);
    cout << "Disjuncts with contradictional literals: " << endl;
    cout << "First disjunct: " << endl;
    a.print();
    cout << "Second disjunct: " << endl;
    b.print();
    cout.close();
}

bool Parser::isUnique(Disjunct merger, vector <Disjunct> addedDisjuncts) {
    for (int i = 0; i < disjuncts.size(); ++i)
        if (merger == disjuncts[i])
            return false;
    for (int i = 0; i < addedDisjuncts.size(); ++i)
        if (merger == addedDisjuncts[i])
            return false;
    return true;
}

bool Parser::resolution() {
    bool isFind = false;
    int counter = 1;
    for (int i = 0; i < disjuncts.size(); ++i) {
        vector <Literal> literals = disjuncts[i].getLiterals();
        Disjunct merger;
        vector <Disjunct> addedDisjuncts;
        addedDisjuncts.clear();
        for (int j = 0; j < literals.size(); ++j)
            for (int k = 0; k < disjuncts.size(); ++k) {
                if (i == k)
                    continue;
                vector <Literal> comparedLiterals = disjuncts[k].getLiterals();
                for (int l = 0; l < comparedLiterals.size(); ++l) {
                    if (Literal::isContradictory(literals[j], comparedLiterals[l])) {
                        merger = Disjunct::merge(disjuncts[i], disjuncts[k], literals[j], comparedLiterals[l] ,counter++);
                        printContradictoryDisjuncts(disjuncts[i], disjuncts[k]);
                        printMerge(merger);
                        if (merger.isEmpty())
                            return true;
                        if (isUnique(merger, addedDisjuncts) && !merger.haveSimilarLiterals()) {
                            addedDisjuncts.push_back(merger);
                        }
                    }
                }
            }
        for (int j = 0; j < addedDisjuncts.size(); ++j)
            disjuncts.push_back(addedDisjuncts[j]);
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
    printCnfs();
    cout << resolution() << endl;
}


