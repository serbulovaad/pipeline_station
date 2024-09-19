#include <iostream>
#include <string>
using namespace std;



//properties
struct pipe
{
	string name = "";
	int l; // length;
	double d; // diameter;
	bool repair; // 0 False - ready for use, 1 True - under repair
};

struct CS //Compressor station
{
	string name = "";
	int ws; // workstations in use
	double eff; //efficienty;

};

template <typename T>
T inputCheck(istream& in = cin)
{
	T x;
	while ((in >> x).fail()	// check type
		|| in.peek() != '\n')	// is buffer empty (int/float check)
	{
		in.clear();
		in.ignore(10000, '\n');
		cout << "Try again\n ";
	}
	return x;
}

ostream& operator << (ostream& out, const pipe& p) //
{
	out << "name: " << p.name << endl
		<< "d = " << p.d << endl
		<< "l = " << p.l << endl
		<< "repair = " << p.repair << endl;

	return out;
}

ostream& operator << (ostream& out, const CS& cs)
{
	out << "name: " << cs.name << endl
		<< "ws = " << cs.ws << endl
		<< "eff = " << cs.eff << endl;

	return out;
}

istream& operator >> (istream& in, pipe& p) // как тут сделать проверку?
{
	cout << "name (str): ";
	p.name = inputCheck<string>(in);
	cout << "d (int) = ";
	p.d = inputCheck<int>(in);
	cout << "l (double) = ";
	p.l = inputCheck<double>(in);
	cout << "repair (true - under repair, false - ready for use) =";
	in >> p.repair;

	return in;
}

istream& operator >> (istream& in, CS& cs) // как тут сделать проверку?
{
	cout << "name (str): ";
	in >> cs.name;
	cout << "ws (int) = ";
	in >> cs.ws;
	cout << "eff (double) = ";
	in >> cs.eff;
	
	return in;
}

int addPipe(pipe& p)
{
	//if (p.name != "")
	//{
		cout << "Add pipe" << endl;
		cin >> p;
		cout << endl;
	//}
	//else
	//	cout << "Pipe already exist\n" << endl;

	return 0;
}

int addCS(CS& cs)
{
	if (cs.name != "")
	{
		cout << "Add CS" << endl;
		cin >> cs;
		cout << endl;
	}
	else
		cout << "CS already exist\n" << endl;
	return 0;
}

void viewAll(const pipe& p, const CS& cs)
{
	cout << "All objects\n\n";
	if (p.name != "")
		cout << "pipe:\n" << p << endl;
	else
		cout << "Pipe is not found\n" << endl;
	if (cs.name != "")
		cout << "CS:\n" << cs << endl;
	else
		cout << "CS is not found\n" << endl;
}

int editPipe(pipe& p)
{

	return 0;
}

int editCS(CS& cs)
{

	return 0;
}


int MenuOutput()
{
	pipe p;
	CS cs;

	while (1)
	{

		cout << "Menu\n\n"
			"1. Add pipe\n2. Add CS\n3. View all objects"
			"\n4. Edit pipe\n5. Edit CS\n"
			"6. Save\n7. Download\n"
			"0. Exit\n" << endl;

		int option;
		cout << "Choose option: ";
		option = inputCheck<int>();
		cout << endl;

		if (option != 0)
		{
			switch (option)
			{
				case 1:
				{
					addPipe(p);
					break;
				}
					
				case 2:
				{
					addCS(cs);
					break;
				}
					
				case 3:
				{
					viewAll(p, cs);
					break;
				}
					
				case 4:
				{
					editPipe(p);
					break;
				}
				case 5:
				{
					editCS(cs);
					break;
				}
				case 6:

					break;
				case 7:

					break;
				default:
					cout << "Error! Wrong number" << option << endl
						<< "Try again" << endl << endl;
					break;
			}
		} 
		else 
		{
			cout << "Goodbye!" << endl;
			return 0;
		}
		
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Привет Hello" << endl;

	MenuOutput();


	return 0;
}