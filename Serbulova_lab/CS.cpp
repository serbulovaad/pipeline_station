#include "CS.h"
#include "help.h"
using namespace std;

int CS::MaxID = 0;

CS::CS()
{
	ID = ++MaxID;
	name = "";
	ws_work = 0;
};

ostream& operator << (ostream & out, const CS & cs) // output for CS
{
	cout << "CS ID = " << cs.ID << endl;
	out << "name: " << cs.name << endl
		<< "ws: " << cs.ws << endl
		<< "ws in work: " << cs.ws_work << endl
		<< "eff: " << cs.eff << endl;

	return out;
}

istream& operator >> (istream & in, CS & cs) // intput for CS // ��� ��� ������� ��������? -> ������� 
{
	cout << "CS ID = " << cs.ID << endl;
	cout << "name (str): ";
	cs.name = inputString(in);
	cout << "ws (int) = ";
	cs.ws = getPositiveNumber<int>(in);
	cout << "ws in work (int) = ";
	cs.ws_work = getCorrectNumber<int>(0, cs.ws, true, in);
	cout << "eff (double) = ";
	cs.eff = getPositiveNumber<double>(in);

	return in;
}

ofstream& operator << (ofstream& fout, const CS& cs) // output for CS
{
	fout << cs.name << endl
		<< cs.ws << endl
		<< cs.ws_work << endl
		<< cs.eff << endl;

	return fout;
}

ifstream& operator >> (ifstream& fin, CS& cs)
{
	cs.name = inputString(fin);
	fin >> cs.ws;
	fin >> cs.ws_work;
	fin >> cs.eff;

	return fin;
}

CS CS::addCS() // add new CS
{
	CS cs;
	cin >> cs;
	return cs;
}

void CS::editCS() // change number of ws in repair for cs
{
	if (ws_work < ws)
		ws_work += 1;
}