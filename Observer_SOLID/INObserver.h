#pragma once
#include<algorithm>

//INumberObserver та 2-≥ його реал≥зац≥њ: PrintObserver: CountObserver :методи void on_number(int),void on_finished()
struct INumberObserver {

	virtual ~INumberObserver() = default;
	virtual void on_number(int& num) = 0;
	virtual void on_finished() = 0;

	INumberObserver() = default;
};


//Х	PrintObserver: виводить число в std::cout
class PrintObserver :public INumberObserver {

private:
	PrintObserver(const PrintObserver&) = delete;
	PrintObserver& operator=(const PrintObserver&) = delete;	

public:
	PrintObserver() = default;

	void on_number(int& in_num) override {
		std::cout << in_num << " ";
	}
	void on_finished() override {}

};


//Х	CountObserver: рахуЇ пройден≥ числа й п≥сл€ завершенн€ виводить загальну к≥льк≥сть
class CountObserver :public INumberObserver {
	
private:	
	CountObserver(const CountObserver&) = delete;
	CountObserver& operator=(const CountObserver&) = delete;
	unsigned int counter = 0;

public:
	CountObserver() = default;

	void on_number(int& num) override {
		++this->counter;
	}
	void on_finished() override {
		std::cout << "\nResult coutner = " << this->counter << std::endl;
	}
};

