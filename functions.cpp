//
// Created by kvit on 18.08.2021.
//

#include "functions.h"
//------------------------------------------------------------
//Ф-я заполнения банкомата купюрами
//Принимает параметры: Имя файла для заполнения купюрами;
//                      Размерность банкомата
//Купюры заполняются в случайном порядке
void AddBanknotes(const char* FileName, int BankSize){
    int banknotes[6] = {100, 200, 500, 1000, 2000, 5000};//Массив разновидности купюр
    std::vector<int> bank;
    std::ifstream InFile(FileName);//Сначала проверяем существует ли уже файл
    if(InFile.is_open()){//Если существует, то дописываем в него недостающие купюры
        int OldBankSize = 0, tmp = 0;
        InFile.read((char*) &OldBankSize, sizeof(OldBankSize));//Считываем количество купюр в файле
        for(int i = 0; i < OldBankSize; ++i){//Считываем купюры
            InFile.read((char*) &tmp, sizeof(tmp));
            bank.push_back(tmp);
        }
        InFile.close();//Закрываем файл, открытый на чиение
        std::ofstream OutFile(FileName, std::ios::binary );//Открываем на запись
        for(int i = 0; i < (BankSize - OldBankSize); i++){
            bank.push_back(banknotes[std::rand() % 6]);//Выбираем в случайном порядке купюру из массива и добавляем в вектор
        }
        OutFile.write((char*) &BankSize, sizeof(BankSize));//Записываем количество купюр в файл
        for(int i =0; i < BankSize; ++i){
            OutFile.write((char*) &bank[i], sizeof (bank[i]));//Записываем купюру в файл
        }
        OutFile.close();//Закрываем файл
#ifdef DEBUG
        for(int el : bank) std::cout << el << " ";
        std::cout << std::endl;
#endif
    }
    else{
        std::ofstream OutFile(FileName, std::ios::binary);//если файл не существует, то создаем и заполняем новый
        if(!OutFile.is_open()){
            std::cerr << "Can't open file!" << std::endl;
            return;
        }
        OutFile.write((char*) &BankSize, sizeof (BankSize));//Записываем количество купюр в банкомате
        for(int i = 0; i < BankSize; i++){
            bank.push_back(banknotes[std::rand() % 6]);//Выбираем в случайном порядке купюру из массива и добавляем в вектор
            OutFile.write((char*) &bank[i], sizeof (bank[i]));//Записываем купюру в файл
        }
        OutFile.close();//Закрываем файл
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
void GetBanknotes(const char* FileName, int Sum){
    std::vector<int> bank, SumBanknotes;
    std::ifstream InFile(FileName, std::ios::binary);
    if(!InFile.is_open()){
        std::cout << "ATM machine is empty. Please try later!" << std::endl;
        return;
    }
    int BankSize = 0, tmp = 0;
    InFile.read((char*) &BankSize, sizeof (BankSize) );//Считываем количество купюр из файла
    if(BankSize == 0){
        std::cout << "ATM machine is empty. Please try later!" << std::endl;
        return;
    }
    for(int i = 0;i < BankSize;++i){
        InFile.read((char*) &tmp, sizeof (tmp) );
        bank.push_back(tmp);// Заполняем вектор купюрами из файла
    }
    std::sort(bank.begin(),bank.end());//Сортируем купюры в векторе для выдачи суммы крупными купюрами
#ifdef DEBUG
     for(int el : bank) std::cout << el << " ";
     std::cout << std::endl;
#endif
    for(int i = bank.size()-1; i >=0 ; --i){
        if((Sum - bank[i]) >= 0){   //Если банкнота меньше или равна требуемой сумме
            SumBanknotes.push_back(bank[i]); //Заносим ее в вектор для выдачи
            Sum -= bank[i]; //Минусуем от суммы
            bank.erase(bank.begin() + i); //и удаляем из вектора банкомата
        }
    }

    if(Sum == 0){
        std::cout << "Your amount:" << std::endl;
        for(int el : SumBanknotes) std::cout << el << " ";
        std::cout << std::endl;
        InFile.close();
        std::ofstream OutFile(FileName);
        BankSize = bank.size();
        OutFile.write((char*) &BankSize, sizeof (BankSize));
        for(int el : bank) OutFile.write((char*) &el, sizeof (el));
        OutFile.close();
        return;
    }
    else {
        std::cout << "It is not possible to issue the required amount" << std::endl;
        InFile.close();
        return;
    }
}