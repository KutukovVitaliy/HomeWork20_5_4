#include <iostream>
#include <ctime>
#include "functions.h"



int main() {
    std::srand(std::time(nullptr));
    int bankSize = 1000;
#ifdef DEBUG
    bankSize = 30;
#endif
    std::string fileName = "../bank.bin";
    std::string operation;
    bool inputIsCorrect;

    do{
        std::cout << "Enter operation ('+' or '-'): ";
        std::cin >> operation;
        if(operation == "+" || operation == "-") {
            inputIsCorrect = true;
        }
        else{
            std::cout << "operation not allowed! Try again!" << std::endl;
            inputIsCorrect = false;
        }
    } while (!inputIsCorrect);
    if(operation == "+") AddBanknotes(fileName, bankSize);
    else if(operation == "-"){
        int amount;
        do{
            inputIsCorrect = true;
            std::cout << "Input amount (amount must be a multiple of 100): ";
            std::cin >> amount;
            if((amount % 100) != 0) {
                inputIsCorrect = false;
                std::cout << "Amount not allowed! Try again!" << std::endl;
            }
        }while(!inputIsCorrect);
        GetBanknotes(fileName, amount);
    }


    return 0;
}
