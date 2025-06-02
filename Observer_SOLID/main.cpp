#include "checkCommand.h"
#include <iostream>
#include"INFilter.h" //≤нтерфейс INumberFilter та 3 його реал≥зац≥њ:
#include"FilterFartory.h"
#include"INReader.h" //≤нтерфейс INumberReader та його реал≥зац≥€:
#include"INObserver.h"

/*
Х NumberProcessor (може не бути абстрактним, адже в≥н один ≥ в≥н однозначно вир≥шуЇ, що буде робити наша програма,
плюс в≥н н≥куди не передаЇтьс€, а використовуЇтьс€ напр€му у main):
Х у конструктор≥ приймаЇ INumberReader&, INumberFilter&, список INumberObserver&
Х метод run(): читаЇ, ф≥льтруЇ, викликаЇ on_number() у вс≥х спостер≥гач≥в
*/

class NumberProcessor {
private:
    INumberFilter &filtered;
    INumberReader &reader; 
    std::vector<std::unique_ptr<INumberObserver>> &observers;
   // std::vector<int> numbers;

  
public:
    // NumberProcessor -	у конструктор≥ приймаЇ INumberReader&, INumberFilter&, список INumberObserver&  
   NumberProcessor(INumberReader& INR, INumberFilter& INF, std::vector<std::unique_ptr<INumberObserver>>&INO)
                                                                :reader (INR), filtered(INF), observers(INO){}


    void run() //читаЇ, ф≥льтруЇ, викликаЇ on_number() у вс≥х спостер≥гач≥в
    {
        
        auto vecNum = reader.readNumbers(); //1.1 «читуванн€ чисел з заданого файлу у vector<int> та його поверненн€

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
‘ункц≥€ main
Х	—творюЇ потр≥бний ф≥льтр через фабрику в≥дпов≥дно аргументу командноњ строки;
Х	ќбираЇ вектор спостер≥гач≥в;
Х	ѕередаЇ все в NumberProcessor ≥ запускаЇ run()
*/

int main(int argc, char* argv[]) {

    std::vector <std::string> V_filtrName; //«бер≥гаЇ назву ф≥льтр≥в, €к≥ введен≥ користувачем
    
    enter_filterName(V_filtrName);        //в  enter_filterName(V_filtrName)  ористувачем
                                          //задаЇтьс€ назва ф≥льтр≥в (checkCommand.h)
    std::string str_filterType="";
    std::string str_fileName="";
    int out_num = 0;

                                             // ѕерев≥рка к≥лькост≥ введених аргумент≥в з командного р€дка (checkCommand.h)
    if (checkCommandLine(argc)) {       
        str_filterType = argv[1];
        str_fileName = argv[2];
    }
    else return 0;
    if (!validFiltrName(str_filterType, V_filtrName, out_num)) {  //ѕерев≥рка вал≥дност≥ назви ф≥льтру (checkCommand.h)
        std::cout << "WRONG filterName \n";
        return 0;
    }     
   
  //===================== 1 «„»“”¬јЌЌя „»—≈Ћ « «јƒјЌќ√ќ ‘ј…Ћ” ” VECTOR<INT> “ј …ќ√ќ ѕќ¬≈–Ќ≈ЌЌя ===================================
    std::unique_ptr<INumberReader> INR = std::make_unique<FileNumberReader>(str_fileName);
   

    //======================== 2 —“¬ќ–≈ЌЌя ѕќ“–≤ЅЌќ√ќ ‘≤Ћ№“–” „≈–≈« ‘јЅ–≤ ” ¬≤ƒѕќ¬≤ƒЌќ√ќ ј–√”ћ≈Ќ“”  ќћјЌƒ–ќѓ —“–ќ » ==============
    FilterFactory FF (V_filtrName, out_num);       
    std::unique_ptr<INumberFilter> INF = FF.createFilter(str_filterType);


    //======================== 3 —“¬ќ–≈ЌЌя ¬≈ “ќ–” —ѕќ—“≈–≤√ј„≤¬ =================================================================
    std::vector<std::unique_ptr<INumberObserver>> observers;
    observers.emplace_back(std::make_unique<PrintObserver>());
    observers.emplace_back(std::make_unique<CountObserver>());    


    //========================= ѕ≈–≈ƒј¬јЌЌя в NumberProcessor, «јѕ”—  run() ==================================================
    NumberProcessor processor(*INR, *INF, observers);
    processor.run();
        
  
  
  return 0;
}
