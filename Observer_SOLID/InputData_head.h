#pragma once
#include<iostream>
#include<vector>

struct MSG {
	std::string msg_enter_filter = { "enter filter name:\n" };
	std::string msg_enter_file = { "enter fail name: " };

	std::string msg_filter_text = { "EVEN - leaves only even numbers;\nODD - leaves only odd numbers;\n"
		"GT<n> -leaves only numbers more than n(for example, GT5)\n\n" };
	std::string msg_file_text = { "(Using file numbers.txt)  " };
};

class enterData:public MSG{		

public:
	enterData() = default;
	enterData(enterData& other) = delete;
	enterData& operator = (enterData& other) = delete;
	
	bool input_Filtr_name(std::string& filtrname) const
	{
		std::cout << msg_enter_filter<< msg_filter_text;
		std::cout << "Waiting for action  ";

		while (!(std::cin >> filtrname));
		for (auto& lit : filtrname) {
			if (isalpha(lit))
				lit = toupper(static_cast<char> (lit));
		}
		return true;
	}

	bool  input_File_name(std::string& filename) {
		std::cout << msg_enter_file << msg_file_text;
		while (!(std::cin >> filename));
		for (auto& lit : filename) {
			if (isalpha(lit))
				lit = tolower(static_cast<char> (lit));			
		}
		system("cls");
		return true;
	}

	void static input_valid (std::string& filtrname, std::string& filename) {
		for (auto& lit : filtrname)	{
			if (isalpha(lit))
				lit = toupper(static_cast<char> (lit));
		}
		for(auto & lit:filename) {
			if (isalpha(lit))
				lit = tolower(static_cast<char> (lit));
		}
	}

	void static input_valid(std::string& filtrname) {
		for (auto& lit : filtrname)
		{
			if (isalpha(lit))
				lit = toupper(static_cast<char> (lit));
		}
	
	}
};

void input_data(const int &argc,  char* argv[], std::vector<std::string> &nameFile) {
	std::string filtrname, filename;
	std::string msg_filtr_name = { "filtr name =>>" };

	if (argc <= 3) {
		enterData in_data;
		if (argc == 1) {
			while (!in_data.input_Filtr_name(filtrname));
			nameFile.push_back(filtrname);
			system("cls");
			std::cout << msg_filtr_name << filtrname << std::endl << std::endl;
			while (!in_data.input_File_name(filename));
			nameFile.push_back(filename);

		}
		else if (argc == 2) {
			filtrname = argv[1];
			in_data.input_valid(filtrname);
			nameFile.push_back(filtrname);
			std::cout << msg_filtr_name << filtrname << std::endl;
			while (!in_data.input_File_name(filename));
			nameFile.push_back(filename);
		}
		else if (argc == 3) {
			filtrname = argv[1];
			filename = argv[2];
			in_data.input_valid(filtrname, filename);
			nameFile.push_back(filtrname);
			nameFile.push_back(filename);
		}
	}
	else {
		std::cout << "Error entry data\n";
	}
	
}

