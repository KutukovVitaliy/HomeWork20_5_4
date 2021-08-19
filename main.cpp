#include <iostream>
#include <vector>
#include <ctime>
#include "functions.h"



int main() {
    std::srand(std::time(nullptr));
    int BankSize = 1000;
#ifdef DEBUG
    BankSize = 30;
#endif
    const char* FileName = "../bank.bin";
    std::string Operation;
    bool InputIsCorrect;

    do{
        std::cout << "Enter operation ('+' or '-'): ";
        std::cin >> Operation;
        if(Operation == "+" || Operation == "-") {
            InputIsCorrect = true;
        }
        else{
            std::cout << "Operation not allowed! Try again!" << std::endl;
            InputIsCorrect = false;
        }
    } while (!InputIsCorrect);
    if(Operation == "+") AddBanknotes(FileName, BankSize);
    else if(Operation == "-"){
        int amount;
        do{
            InputIsCorrect = true;
            std::cout << "Input amount (amount must be a multiple of 100): ";
            std::cin >> amount;
            if((amount % 100) != 0) {
                InputIsCorrect = false;
                std::cout << "Amount not allowed! Try again!" << std::endl;
            }
        }while(!InputIsCorrect);
        GetBanknotes(FileName,amount);
    }


    return 0;
}
