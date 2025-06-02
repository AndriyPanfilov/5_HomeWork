#pragma once
#include <vector>
#include<iostream>
#include<string>
#include <fstream>


/*
	Інтерфейс INumberReader та його реалізація: читає всі числа з файлу, повертає std::vector<int>
*/
struct INumberReader {
	virtual ~INumberReader() = default;
	virtual std::vector<int> readNumbers() = 0;	
};

class FileNumberReader : public INumberReader {

    std::vector<int> numbers;
    std::string filename;

public:
    FileNumberReader(std::string& f_name) :filename(f_name) {};
    FileNumberReader(FileNumberReader& other) = delete;
    FileNumberReader& operator = (FileNumberReader& other) = delete;
    std::vector<int> readNumbers () override {      

        std::ifstream fin (filename);
        if (!fin.is_open()) {
            std::cout << "ERROR! Couldn't open file for reading. Wrong filename?\n";
            return this->numbers;
        }
        else {
            int num;
            while (fin >> num) {
                this->numbers.push_back(num);
            }
        }
        return this->numbers;
    }       
};
