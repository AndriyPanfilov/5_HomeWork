#include "checkCommand.h"
#include <iostream>
#include"INFilter.h" //��������� INumberFilter �� 3 ���� ���������:
#include"FilterFartory.h"
#include"INReader.h" //��������� INumberReader �� ���� ���������:
#include"INObserver.h"

/*
� NumberProcessor (���� �� ���� �����������, ���� �� ���� � �� ���������� �����, �� ���� ������ ���� ��������,
���� �� ����� �� ����������, � ��������������� ������� � main):
� � ����������� ������ INumberReader&, INumberFilter&, ������ INumberObserver&
� ����� run(): ����, �������, ������� on_number() � ��� ������������
*/

class NumberProcessor {
private:
    INumberFilter &filtered;
    INumberReader &reader; 
    std::vector<std::unique_ptr<INumberObserver>> &observers;
   // std::vector<int> numbers;

  
public:
    // NumberProcessor -	� ����������� ������ INumberReader&, INumberFilter&, ������ INumberObserver&  
   NumberProcessor(INumberReader& INR, INumberFilter& INF, std::vector<std::unique_ptr<INumberObserver>>&INO)
                                                                :reader (INR), filtered(INF), observers(INO){}


    void run() //����, �������, ������� on_number() � ��� ������������
    {
        
        auto vecNum = reader.readNumbers(); //1.1 ���������� ����� � �������� ����� � vector<int> �� ���� ����������

        for (auto& i : vecNum) {            
            if (filtered.keep(i)) {
                for (auto& obs : observers)
                   obs->on_number(i);
            }                
        }
        for (auto& obs : observers)
            obs->on_finished();       
    }    
};

/*
������� main
�	������� �������� ������ ����� ������� �������� ��������� �������� ������;
�	����� ������ ������������;
�	������ ��� � NumberProcessor � ������� run()
*/

int main(int argc, char* argv[]) {

    std::vector <std::string> V_filtrName; //������ ����� �������, �� ������ ������������
    
    enter_filterName(V_filtrName);        //�  enter_filterName(V_filtrName) ������������
                                          //�������� ����� ������� (checkCommand.h)
    std::string str_filterType="";
    std::string str_fileName="";
    int out_num = 0;

                                             // �������� ������� �������� ��������� � ���������� ����� (checkCommand.h)
    if (checkCommandLine(argc)) {       
        str_filterType = argv[1];
        str_fileName = argv[2];
    }
    else return 0;
    if (!validFiltrName(str_filterType, V_filtrName, out_num)) {  //�������� �������� ����� ������� (checkCommand.h)
        std::cout << "WRONG filterName \n";
        return 0;
    }     
   
  //===================== 1 ���������� ����� � �������� ����� � VECTOR<INT> �� ���� ���������� ===================================
    std::unique_ptr<INumberReader> INR = std::make_unique<FileNumberReader>(str_fileName);
   

    //======================== 2 ��������� ���в����� Բ����� ����� ���в�� ²���²����� ��������� �������ί ������ ==============
    FilterFactory FF (V_filtrName, out_num);       
    std::unique_ptr<INumberFilter> INF = FF.createFilter(str_filterType);


    //======================== 3 ��������� ������� ������в��ײ� =================================================================
    std::vector<std::unique_ptr<INumberObserver>> observers;
    observers.emplace_back(std::make_unique<PrintObserver>());
    observers.emplace_back(std::make_unique<CountObserver>());    


    //========================= ����������� � NumberProcessor, ������ run() ==================================================
    NumberProcessor processor(*INR, *INF, observers);
    processor.run();
        
  
  
  return 0;
}
