#pragma once
#include<iostream>
#include<memory>
#include<string>
#include<functional>
#include<map>
#include<vector>
#include"INFilter.h"

/*
•	FilterFactory: за назвою (з командної строки) повертає потрібний фільтр.
Зробити за принципом FactoryRegistry, як на уроці по SOLID - з мапою фабрик/лямбд.
Може не бути абстрактною, адже може нікуди не передаватися (передається готовий INumberFilter по інтерфейсу)
*/

class FilterFactory  {
private:

	using Factory = std::function<std::unique_ptr<INumberFilter>(int)>;

	std::map<std::string, Factory> registry;
	std::string filter_type;
	//std::vector<std::string> V_filterType;
	int out_num;	

	FilterFactory() = delete;
	FilterFactory(const FilterFactory& other) = delete;
	FilterFactory& operator=(const FilterFactory& other) = delete;


	void registered (const std::string& filter_key, Factory f) {
		this->registry[filter_key] = f;
	}

	void registerd_filtr (const std::vector <std::string>& V_filterName,
						const int& out_num)	{

		this->registered(V_filterName[0], [](int out_num) {
			return std::make_unique <EvenFilter>(out_num);
			});

		this->registered(V_filterName[1], [](int out_num) {
			return std::make_unique <OddFilter>(out_num);
			});

		this->registered(V_filterName[2], [](int out_num) {
			return std::make_unique <GTFilter>(out_num);
			});
	}
	 
public:

	FilterFactory(const std::vector <std::string>& V_filterName,
				  const int& out_num) {
		this->out_num = out_num;
		registerd_filtr(V_filterName, out_num);
	}



	std::unique_ptr<INumberFilter> createFilter(const std::string& filter_type) {		

			auto it = registry.find(filter_type);
			if (it != registry.end()) {
				return it->second(out_num);
			}
				else {
					throw std::runtime_error("Unknown filter type: " + filter_type);
				}
				
	}
};
