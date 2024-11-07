#include "pipe.h"
#include "help.h"
using namespace std;

int pipe::MaxID = 0;

pipe::pipe()
{
	ID = ++MaxID;
	string name = "";
	bool repair = false;
};

ostream& operator<<(std::ostream& out, const pipe& p)
{
	cout << "Pipe" << endl
		<< "ID = " << p.ID << endl;
	out << "name: " << p.name << endl
		<< "d: " << p.d << endl
		<< "l: " << p.l << endl
		<< "repair status: " << p.repair << endl;

	return out;
}

istream& operator>>(istream& in, pipe& p)
{
	cout << "Pipe" << endl;
	cout << "ID = " << p.ID << endl;
	cout << "name (str) = ";
	p.name = inputString(in);
	cout << "d (int) = ";
	p.d = getPositiveNumber<int>(in);
	cout << "l (double) = ";
	p.l = getPositiveNumber<double>(in);
	cout << "repair status: 0 (ready for use)" << endl;

	return in;
}

ofstream& operator << (ofstream& fout, const pipe& p) // output for CS
{
	fout << p.ID << endl
		<< p.name << endl
		<< p.l << endl
		<< p.d << endl
		<< p.repair << endl;;

	return fout;
}

ifstream& operator >> (ifstream& fin, pipe& p)
{
	fin >> p.ID;
	p.name = inputString(fin);
	fin >> p.l;
	fin >> p.d;
	fin >> p.repair;

	return fin;
}

pipe pipe::addPipe() // add new pipe
{
	pipe p;
	cin >> p;
	return p;
}

void pipe::editPipe() // change status of repair for pipe
{
	if (name != "")
	{
		repair = !repair;
		cout << "New repair status for pipe \"" << name << "\": " << repair << endl;
	}
	else
		cout << "Pipe is not found" << endl;

}
