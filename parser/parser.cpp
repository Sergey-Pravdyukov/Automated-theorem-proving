#include "parser.h"

Parser::Parser(const char *fname) {
    ptrFile = freopen("PUZ001-1.p", "r", stdin);
    char currentString[maxStringLehgth];
    if (ptrFile == NULL)
        perror("Error opening file");
    else
        while (fgets(currentString, maxStringLehgth, ptrFile) != nullptr)
            if (currentString[0] != '%')
                concat(currentString);
}

Parser::~Parser() {
    fclose(ptrFile);
}

void Parser::parse() {
    std::cout << "Fuck this shit" << std::endl;
}

void Parser::concat(char string[]) {
    const int length = strlen(string) - 1;
    text[size] = new char[length];
    for (int i = 0; i < length; ++i)
        text[size][i] = string[i];
    ++size;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < strlen(text[i]); ++j) std::cout << text[i][j];
        std::cout << std::endl;
    }
    std::cout << size << std::endl;
}

