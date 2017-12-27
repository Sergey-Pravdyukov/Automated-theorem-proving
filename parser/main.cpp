#include "parser.h"

#include <iostream>
#include <cstring>

using namespace std;

int main() {

    const int maxSize = 1e3;

    char fileName[maxSize] = {'a'};

    cout << "Please input correct parsing file name: ";
//    gets(fileName);
    cout << "File name: " << fileName << endl << endl;

    Parser *parser = new Parser();
    parser->parse(fileName);



    return 0;
}
