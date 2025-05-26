#pragma once
#include<memory>
#include <functional>
#include <map>
#include<string>


//та 3 його реалізації: метод bool keep(int)
class INumberFilter {	
public:
	virtual ~INumberFilter() = default;
	virtual bool keep(const int& num, const int &in_num) = 0;
};


//1-a реалізація => філетр	EVEN — залишає тільки парні числа
class EvenFilter:public INumberFilter {
	
public:
	EvenFilter() = default;
	
	bool keep(const int& num, const int& in_num) override {
		
		if (in_num == 0) {
		return num % 2 == 0;
		}
		else return false;
	} 	
};


//2-a реалізація => філетр	ODD — залишає тільки непарні числа
class OddFilter :public INumberFilter {
	
public:	
	OddFilter() = default;

	bool keep(const int& num, const int &in_num) override {		
		if (in_num == 0)
			return !(num % 2 == 0);
		else return false;
	}
};


//3-а реалізація => фільт GT<n> (GT5) - залишає тільки чился більше за <n>
class GTFilter :public INumberFilter {

public:	
	GTFilter() = default;

	bool keep(const int& num, const int &in_num) override {
		if (in_num > 0)
			return (num > in_num);
		else return false;
	}
};


struct FilterRegistry {
	virtual std::unique_ptr<INumberFilter> create (const std::string& filtr_type) = 0;
};

class FilterFactory :public FilterRegistry {

	std::string filter_type;
	int in_number = 0;

	using Factory = std::function <std::unique_ptr<INumberFilter>()>;
	std::map <std::string, Factory> registry;							//map в якій рєєструються фільтри
	
	FilterFactory(const FilterFactory& other) = delete;
	FilterFactory& operator = (const FilterFactory& other) = delete;

public:
	FilterFactory(std::string Filter_type) :filter_type(Filter_type) {}

	void ParserFilter_type() {
		std::string temp_filterType;
		std::string stdDigit = "0";

		for (int i(0); i < this->filter_type.size(); i++) {
			if (isupper(this->filter_type[i])) {
				temp_filterType += this->filter_type[i];

			}
			else if (isdigit(this->filter_type[i]))
				stdDigit += this->filter_type[i];
		}
		this->filter_type = temp_filterType;

		try {
			this->in_number = std::stoi(stdDigit);
		}
		catch (std::invalid_argument&) {
			std::cout << "Wrong digit for GT\n";
		}
	}
	
	inline std::string get_filterType() const { return this->filter_type; }
	inline int get_inNumber() const { return this->in_number; }
	inline void set_inNumber(int& in_num) { this->in_number = in_num; }

	void register_factory (std::string ParsFilter_type, Factory f) {		
		this->registry[ParsFilter_type] = f;		
	}
		
	std::unique_ptr<INumberFilter> create (const std::string &filter_type) override {		
		auto &func = this->registry[filter_type];			
		return func();
	}
};