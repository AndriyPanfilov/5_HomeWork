#include"InputData_head.h"
#include"Filter.h"
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include<memory>
#include <algorithm>


//INumberReader читає всі числа з файлу, повертає std::vector<int>
class INumberReader {		

	std::vector <int> numbers;
	std::string filename;

public:
	INumberReader() = default;
	INumberReader(const std::string& filename) :filename(filename) {};


	std::vector <int> readNumber ()  {
		std::ifstream fin(filename);
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


//INumberObserver та 2-і його реалізації: PrintObserver: CountObserver :методи void on_number(int),void on_finished()
struct INumberObserver {

	virtual ~INumberObserver() = default;
	virtual void on_number(int &num) = 0;
	virtual void on_finished() = 0;

	INumberObserver() = default;
};


template <typename SlotInterface>
class FileProcessor {

	std::vector<SlotInterface*> slots;

public:
	class ConnectionSlot {
		SlotInterface *slot;
		FileProcessor* subject;
	public:

		ConnectionSlot (FileProcessor* subject, SlotInterface* slot) :subject(subject), slot(slot) {}

		ConnectionSlot& operator = (ConnectionSlot&& other) noexcept {
				if (this != other)
				{
					this->disconnect();
					this->subject = other.subject;
					this->slot = other.slot;
					other.subject = nullptr;
					other.slot = nullptr;
				}
				return *this;
			}
			ConnectionSlot(const ConnectionSlot& other) {};
			ConnectionSlot &operator = (const ConnectionSlot &other) = delete;

			~ConnectionSlot() {
				this->disconnect();
			}		

			void disconnect() {
				if (this->subject && this->slot) {
					this->subject->disconnect(this->slot);
					this->subject = nullptr;
					this->slot = nullptr;
				}
			}
	};

	ConnectionSlot connect(SlotInterface *slot) {
		this->slots.push_back(slot);
		return ConnectionSlot(this, slot);
	}

	void disconnect(SlotInterface* slot) {
		this->slots.erase(std::remove(slots.begin(), slots.end(), slot), slots.end());
	}

	std::vector<SlotInterface*> snapshot (){
		return this->slots;
	}

	size_t VectorSlot_size () {
		return this->slots.size();
	}
};


//•	PrintObserver: виводить число в std::cout
class PrintObserver:public INumberObserver {
	FileProcessor<INumberObserver>::ConnectionSlot conn;
public:
	PrintObserver(FileProcessor<INumberObserver>& subject) : conn (subject.connect(this)) {}

	void on_number(int& num) override {
		std::cout << num << " ";
	}
	void on_finished () override {}
};


//•	CountObserver: рахує пройдені числа й після завершення виводить загальну кількість
class CountObserver :public INumberObserver{

	FileProcessor<INumberObserver>::ConnectionSlot conn;
	
	unsigned int counter=0;

public:
	CountObserver(FileProcessor<INumberObserver>& subject) :conn(subject.connect(this)) {}
	void on_number(int& num) override {
		++this->counter;
	}
	void on_finished() override {
		std::cout << "\nResult coutner = " << this->counter << std::endl;
	}
};



class NumberProcessor  {

	FilterFactory& ff;
	INumberReader& readFile;
	FileProcessor<INumberObserver>& fProc;

	void RegistredFiltr()	{		

		ff.register_factory("EVEN", []() {
			return std::make_unique <EvenFilter>();
			});

		ff.register_factory("ODD", []() {
			return std::make_unique <OddFilter>();
			});

		ff.register_factory("GT", []() {
			return std::make_unique <GTFilter>();
			});
	}
	

public:
	
	NumberProcessor(INumberReader &RF, FilterFactory& FF, FileProcessor<INumberObserver> &FP) :readFile(RF),ff(FF), fProc(FP){}

	//•	метод run(): читає, фільтрує, викликає on_number() у всіх спостерігачів
	void run() {
		ff.ParserFilter_type();								 //Парсить назву фільтра типу GT5 (відділяє літери від цифр)	
		RegistredFiltr();									 //Рєєструє фільтри в мапі registry

		auto dataFiltr = ff.create(ff.get_filterType());	 //Повертає Сінгалтон-Фільтр в dataFiltr	
		
		PrintObserver printO(fProc);
		CountObserver countO(fProc);		

		for (auto &numFilt: readFile.readNumber()) {
			if (dataFiltr->keep(numFilt, ff.get_inNumber())) 
				for (auto& slot : fProc.snapshot()) {
					slot->on_number(numFilt);
				}			
		}	
		for (auto& slot : fProc.snapshot()) {
			slot->on_finished();
		}
	}	
}; 



int main(int argc, char* argv[]) {	
	std::vector <std::string> strParametr;
	input_data(argc, argv, strParametr);
		
	INumberReader readFile(strParametr[1]);
	FilterFactory FF (strParametr[0]);	
	FileProcessor <INumberObserver> FP;

	NumberProcessor numberProc (readFile,FF,FP);
	numberProc.run();	

	system("pause");
}

