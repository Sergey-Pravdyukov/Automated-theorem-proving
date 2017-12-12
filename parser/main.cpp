#include "parser.h"

#include <iostream>
#include <cstring>

using namespace std;

int main() {

    const int maxSize = 1e3;

    char fileName[maxSize] = {'a'};

    std::cout << "Please input correct parsing file name: ";
//    gets(fileName);
    std::cout << "File name: " << fileName << std::endl;

    Parser *parser = new Parser(fileName);
    parser->parse();



    return 0;
}
