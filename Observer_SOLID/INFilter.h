
#pragma once
#include<memory>
#include<string>

/*
	����������� ���� INumberFilter, � ����������� ��� ������� � ����� ������� � ������� ��������� �������� ������.
	��������� INumberFilter �� 3 ���� ���������: ����� bool keep(int)
*/

class INumberFilter {
protected:
	int out_num = 0;
	
public:
	INumberFilter (int& in_num) :out_num(in_num) {}
	virtual ~INumberFilter() = default;
	virtual bool keep(const int& num) = 0;
};

//1-a ��������� => ������	EVEN � ������ ����� ���� �����
class EvenFilter :public INumberFilter {

public:
	EvenFilter(int out_num) :INumberFilter(out_num) {};
	bool keep(const int& num) override {
		if (out_num == 0) {
			return num % 2 == 0;
		}
		else return false;
	}
};

//2-a ��������� => ������	ODD � ������ ����� ������ �����
class OddFilter :public INumberFilter {

public:
	OddFilter(int out_num) :INumberFilter(out_num) {};
	bool keep(const int& num) override {		
		if (out_num == 0)
			return !(num % 2 == 0);
		else return false;
	}
};

//3-� ��������� => ������ GT<n> (GT5) - ������ ����� ����� ����� �� <n>
class GTFilter :public INumberFilter {

public:
	GTFilter(int out_num) :INumberFilter(out_num) {};
	bool keep(const int& num) override {
		if (out_num > 0){
			return (num>out_num);
		}
		else return false; 
	}
};

