#pragma once
#include <string>
#include <vector>
#include <iostream>

void enter_filterName(std::vector<std::string> &V_filtrName) {
    V_filtrName.push_back("EVEN");  //EVEN - залишає тільки парні числа;
    V_filtrName.push_back("ODD");   // ODD - залишає тільки не парні числа;
    V_filtrName.push_back("GT");    // GT<5> - залишає числа більше ніж задане <n> (5);
}

bool checkCommandLine(const int& numArgum){
    if (numArgum != 3) {
        if (numArgum == 1) {
            std::cout << "Missing Filtr_name and File_name\n";
        }
        else if (numArgum == 2) {
            std::cout << "Missing File_name\n";
        }
        else if (numArgum > 3) {
            std::cout << "Wrong enter\n";
        }
        return false;
    } else  return true;
}

static bool validFiltrName(std::string& str_filtrName, const std::vector<std::string>& V_filtrName, int& in_num) {
    std::string temp_filtrName = "";
    std::string str_inNum = "";
    int i = 0;
    while (!isdigit(str_filtrName[i])) {
        str_filtrName[i] = toupper(str_filtrName[i]);
        if (i < str_filtrName.size())
            i++;
        else break;
    }


    if (isdigit(str_filtrName[i])) {

        temp_filtrName = str_filtrName.substr(0, i);
        while (isdigit(str_filtrName[i])) {
            str_inNum += str_filtrName[i];
            if (i < str_filtrName.size())
                i++;
            else break;
        }       

        if (temp_filtrName.size() + str_inNum.size() == str_filtrName.size()) {
            str_filtrName = temp_filtrName;
            if (temp_filtrName == V_filtrName[2]) {                
                in_num = std::stoi(str_inNum);         
                return true;
            }
            else return false;
        }
        else return false;
    }
    else {
        temp_filtrName = str_filtrName;
        if ((temp_filtrName == V_filtrName[0]) || (temp_filtrName == V_filtrName[1])) {
            str_filtrName = temp_filtrName;
            return true;
        }
        else
            return false;
    }
}

