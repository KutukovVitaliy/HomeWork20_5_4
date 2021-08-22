//
// Created by kvit on 18.08.2021.
//

#include "functions.h"
//------------------------------------------------------------
//Ф-я заполнения банкомата купюрами
//Принимает параметры: Имя файла для заполнения купюрами;
//                      Размерность банкомата
//Купюры заполняются в случайном порядке
void AddBanknotes(std::string& fileName, int bankSize){
    int banknotes[6] = {100, 200, 500, 1000, 2000, 5000};//Массив разновидности купюр
    std::vector<int> bank;
    std::ifstream inFile(fileName);//Сначала проверяем существует ли уже файл
    if(inFile.is_open()){//Если существует, то дописываем в него недостающие купюры
        int oldBankSize = 0, tmp = 0;
        inFile.read((char*) &oldBankSize, sizeof(oldBankSize));//Считываем количество купюр в файле
        for(int i = 0; i < oldBankSize; ++i){//Считываем купюры
            inFile.read((char*) &tmp, sizeof(tmp));
            bank.push_back(tmp);
        }
        inFile.close();//Закрываем файл, открытый на чиение
        std::ofstream outFile(fileName, std::ios::binary );//Открываем на запись
        for(int i = 0; i < (bankSize - oldBankSize); i++){
            bank.push_back(banknotes[std::rand() % 6]);//Выбираем в случайном порядке купюру из массива и добавляем в вектор
        }
        outFile.write((char*) &bankSize, sizeof(bankSize));//Записываем количество купюр в файл
        for(int i =0; i < bankSize; ++i){
            outFile.write((char*) &bank[i], sizeof (bank[i]));//Записываем купюру в файл
        }
        outFile.close();//Закрываем файл
#ifdef DEBUG
        for(int el : bank) std::cout << el << " ";
        std::cout << std::endl;
#endif
    }
    else{
        std::ofstream outFile(fileName, std::ios::binary);//если файл не существует, то создаем и заполняем новый
        if(!outFile.is_open()){
            std::cerr << "Can't open file!" << std::endl;
            return;
        }
        outFile.write((char*) &bankSize, sizeof (bankSize));//Записываем количество купюр в банкомате
        for(int i = 0; i < bankSize; i++){
            bank.push_back(banknotes[std::rand() % 6]);//Выбираем в случайном порядке купюру из массива и добавляем в вектор
            outFile.write((char*) &bank[i], sizeof (bank[i]));//Записываем купюру в файл
        }
        outFile.close();//Закрываем файл
#ifdef DEBUG
        for(int el : bank) std::cout << el << " ";
        std::cout << std::endl;
#endif
    }
    return;
}
//-----------------------------------------------------
//Ф-я выдачи требуемой суммы из банкомата
//Принимает параметры: Имя файла где хранятся купюры;
//                     Требуемая сумма;
//Если возможно выдать требуемую сумму, то файл банкомата перезаписывается без выданных купюр
void GetBanknotes(std::string& fileName, int sum){
    std::vector<int> bank, sumBanknotes;
    std::ifstream inFile(fileName, std::ios::binary);
    if(!inFile.is_open()){
        std::cout << "ATM machine is empty. Please try later!" << std::endl;
        return;
    }
    int bankSize = 0, tmp = 0;
    inFile.read((char*) &bankSize, sizeof (bankSize) );//Считываем количество купюр из файла
    if(bankSize == 0){
        std::cout << "ATM machine is empty. Please try later!" << std::endl;
        return;
    }
    for(int i = 0; i < bankSize; ++i){
        inFile.read((char*) &tmp, sizeof (tmp) );
        bank.push_back(tmp);// Заполняем вектор купюрами из файла
    }
    std::sort(bank.begin(),bank.end());//Сортируем купюры в векторе для выдачи суммы крупными купюрами
#ifdef DEBUG
     for(int el : bank) std::cout << el << " ";
     std::cout << std::endl;
#endif
    for(int i = bank.size()-1; i >=0 ; --i){
        if((sum - bank[i]) >= 0){   //Если банкнота меньше или равна требуемой сумме
            sumBanknotes.push_back(bank[i]); //Заносим ее в вектор для выдачи
            sum -= bank[i]; //Минусуем от суммы
            bank.erase(bank.begin() + i); //и удаляем из вектора банкомата
        }
    }

    if(sum == 0){
        std::cout << "Your amount:" << std::endl;
        for(int el : sumBanknotes) std::cout << el << " ";
        std::cout << std::endl;
        inFile.close();
        std::ofstream outFile(fileName);
        if(!outFile.is_open()){
            std::cout << "Can't open file to write" << std::endl;
            return;
        }
        bankSize = bank.size();
        outFile.write((char*) &bankSize, sizeof (bankSize));
        for(int el : bank) outFile.write((char*) &el, sizeof (el));
        outFile.close();
        return;
    }
    else {
        std::cout << "It is not possible to issue the required amount" << std::endl;
        inFile.close();
        return;
    }
}