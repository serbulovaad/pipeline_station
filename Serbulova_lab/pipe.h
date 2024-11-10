#pragma once
#include <iostream>
#include <string>
#include <fstream>

class pipe
{
private:
	static int MaxID;
	int ID;
	std::string name;
	double l; // length;
	int d; // diameter;
	bool repair; // 0 False - ready for use, 1 True - under repair

public:
	pipe();

	static pipe addPipe(); //не к конкретной трубе

	friend std::ostream& operator << (std::ostream& out, const pipe& p); 
	friend std::istream& operator >> (std::istream& in, pipe& p);
	friend std::ofstream& operator << (std::ofstream& fout, const pipe& p);
	friend std::ifstream& operator >> (std::ifstream& fin, pipe& p);

	void editPipe();
	int getID()
	{
		return ID;
	}
};

