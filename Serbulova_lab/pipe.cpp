#include "pipe.h"
#include "help.h"
using namespace std;

int pipe::MaxID = 0;

pipe::pipe()
{
	ID = ++MaxID;
	name = "";
	in_repair = 0;
};

pipe::pipe(string nam, double len, int diam)
{
	ID = ++MaxID;
	name = "";
	in_repair = 0;
	d = diam;
	l = len;
	name = nam;
};

ostream& operator<<(std::ostream& out, const pipe& p)
{
	cout << "ID = " << p.ID << endl;
	 out << "name = " << p.name << endl
		 << "d = " << p.d << endl
		 << "l = " << p.l << endl
		 << "in_repair status = " << p.in_repair << endl;
	return out;
}
 
istream& operator>>(istream& in, pipe& p)
{
	cout << "pipe ID = " << p.ID << endl;
	cout << "name (str) = ";
	p.name = inputString(in);
	cout << "d (int) = ";
	p.d = getPositiveNumber<int>(in);
	cout << "l (double) = ";
	p.l = getPositiveNumber<double>(in);
	cout << "in_repair status: 0 (ready for use)" << endl;

	return in;
}

ofstream& operator << (ofstream& fout, const pipe& p) // output for CS
{
	fout << p.ID << endl
		<< p.name << endl // ������ ID ����� ��������� ��� ������� fout'�� � main
		<< p.d << endl
		<< p.l << endl
		<< p.in_repair << endl;;

	return fout;
}

ifstream& operator >> (ifstream& fin, pipe& p)
{
	fin >> p.ID;
	getline(fin >> ws, p.name); // ������ ID ����� ��������� ��� ������� fin'�� � main
	fin >> p.d;
	fin >> p.l;
	fin >> p.in_repair;

	return fin;
}

pipe pipe::addPipe() // add new pipe
{
	pipe p;
	cin >> p;
	return p;
}

void pipe::resetMaxID()
{
	MaxID = 0;
}

void pipe::editPipe(int status) // change status of in_repair for pipe
{
	if (status == 2)
		in_repair = !in_repair;
	else 
		if ((status == 0) or (status == 1)) in_repair = status;
}



