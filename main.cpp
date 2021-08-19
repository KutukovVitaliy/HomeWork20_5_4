#include <iostream>
#include <vector>
#include <ctime>
#include "functions.h"


int main() {
    std::srand(std::time(nullptr));
    const int BankSize = 30;
    const char* FileName = "../bank.bin";
    std::string Operation;

    do{
        std::cout << "Enter operation ('+' or '-'): ";
        std::cin >> Operation;
    } while (Operation != "+" || Operation != "-");

    AddBanknotes(FileName, BankSize);
    GetBanknotes(FileName,1200);

    return 0;
}
