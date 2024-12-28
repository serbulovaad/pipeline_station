#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

class pipe
{
private:
	static int MaxID;
	int ID;
	std::string name;
	int d; // diameter;
	double l; // length;
	bool in_repair; // 0 False - ready for use, 1 True - under in_repair

public:
	pipe();
	pipe(std::string nam, double len, int diam);

	static pipe addPipe(); //не к конкретной трубе
	static void resetMaxID();

	friend std::ostream& operator << (std::ostream& out, const pipe& p); 
	friend std::istream& operator >> (std::istream& in, pipe& p);
	friend std::ofstream& operator << (std::ofstream& fout, const pipe& p);
	friend std::ifstream& operator >> (std::ifstream& fin, pipe& p);

	void editPipe(int status = 2);
	int getID() const
	{
		return ID;
	}
	std::string getName() const
	{
		return name;
	}
	bool getInRepair() const
	{
		return in_repair;
	}
	int getDiam() const
	{
		return d;
	}
	double getCapacity() const
	{
		//std::cout << std::sqrt(pow(d * 0.0001, 5) / l)  << std::endl;
		return std::sqrt(pow(d*0.0001, 5) / l);
	}
};

