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
	int ws; // workstations 
	int ws_repair; // // workstations in prepair
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
		cout << "wrong type --> try again: ";
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
		<< "ws in repair = " << cs.ws_repair << endl
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
	cout << "repair (bool: true or 1 - under repair, false or 0 - ready for use) = ";
	p.repair = inputCheck<bool>(in);

	return in;
}

istream& operator >> (istream& in, CS& cs) // как тут сделать проверку?
{
	cout << "name (str): ";
	cs.name = inputCheck<string>(in);
	cout << "ws (int) = ";
	cs.ws = inputCheck<int>(in);
	cout << "ws in repair (int) = ";
	cs.ws_repair = inputCheck<int>(in);
	cout << "eff (double) = ";
	cs.eff = inputCheck<double>(in);
	
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
	cout << "Current repair status for pipe: " << p.repair << endl;
	cout << "New status (true or 1 - under repair, false or 0 - ready for use): ";
	p.repair = inputCheck<bool>();
	return 0;
}

int editCS(CS& cs)
{
	cout << "Current numer of ws in repair for CS: " << cs.ws_repair << endl;
	cout << "New number (int): ";
	cs.ws_repair = inputCheck<int>();
	return 0;
}

int saveFile(const pipe& p, const CS& cs)
{

	return 0;
}

int downloadFile(const pipe& p, const CS& cs)
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
					saveFile(p, cs);
					break;
				case 7:
					downloadFile(p, cs);
					break;
				default:
					cout << "Error! Wrong number: " << option << endl
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