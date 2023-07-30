
#include <iostream>
#include "CInterface.h"

int main(){

    CInterface init;
    if (!init.loadData()){
        std::cout << "EOF!" << std::endl; /// eof detected
    }

    return 0;
}
