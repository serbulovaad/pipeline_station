#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// поменять на getline()?

//properties
struct pipe
{
	string name = "";
	double l; // length;
	int d; // diameter;
	bool repair = 0; // 0 False - ready for use, 1 True - under repair
};

struct CS //Compressor station
{
	string name = "";
	int ws; // workstations 
	int ws_repair = 0; // // workstations in prepair
	double eff; //efficienty;

};

template <typename T> // template to check different types of variables
T inputCheck(istream& in = cin) // check type
{
	T x;
	while ((in >> x).fail()	// check type
		|| in.peek() != '\n')	// is buffer empty (int/float check)
	{
		in.clear();
		in.ignore(10000, '\n');
		cerr << "ERROR wrong type --> try again: ";
	}
	return x;
}

template <typename T>
T getCorrectNumber(T a, T b, bool included = true, istream& in = cin) // check that nu,ber is in range(a,b)
{
	T x = inputCheck<T>(in);
	while ( (included && (x<a || x>b))
		|| (!included && (x<=a || x>=b)) )
 	{
		string str_included = included ? "= " : " ";
		cerr << "ERROR wrong number: min >"<< str_included << a << " and max <" << str_included << b << " --> try again: ";
		x = inputCheck<T>(in);
	}
	return x;
}

template <typename T> // как проверить красиво на полож число???	
T getPositiveNumber(istream& in = cin)
{
	return getCorrectNumber<T>(0, std::numeric_limits<T>::max(),false, in);
}

ostream& operator << (ostream& out, const pipe& p) // output for pipe
{
	cout << "Add pipe" << endl;
	out << "name: " << p.name << endl
		<< "d: " << p.d << endl
		<< "l: " << p.l << endl
		<< "repair status: " << p.repair << endl;

	return out;
}

ostream& operator << (ostream& out, const CS& cs) // output for CS
{
	out << "name: " << cs.name << endl
		<< "ws: " << cs.ws << endl
		<< "ws in repair: " << cs.ws_repair << endl
		<< "eff: " << cs.eff << endl;

	return out;
}

istream& operator >> (istream& in, pipe& p) // как тут сделать проверку? -> сделали // intput for pipe
{
	cout << "Add pipe" << endl;
	cout << "name (str) = ";
	p.name = inputCheck<string>(in);
	cout << "d (int) = ";
	p.d = getPositiveNumber<int>(in);
	cout << "l (double) = ";
	p.l = getPositiveNumber<double>(in);
	cout << "repair status: 0 (ready for use)\n" << endl;
	//cout << "repair (bool: true or 1 - under repair, false or 0 - ready for use) = ";
	//p.repair = inputCheck<bool>(in);

	return in;
}

istream& operator >> (istream& in, CS& cs) // как тут сделать проверку? -> сделали // intput for CS
{
	cout << "Add CS" << endl;
	cout << "name (str): ";
	cs.name = inputCheck<string>(in);
	cout << "ws (int) = ";
	cs.ws = getPositiveNumber<int>(in);
	cout << "ws in repair (int) = 0 (all ready for use)\n";
	//cout << "ws in repair (int) = ";
	//cs.ws_repair = inputCheck<int>(in);
	cout << "eff (double) = ";
	cs.eff = getPositiveNumber<double>(in);
	cout << endl;

	return in;
}



void addPipe(pipe& p) // add new pipe
{
	if (p.name == "")
		cin >> p;
	else
	{
		cout << "Pipe already exist\n" << endl
			<< "Do you want to rewrite it?" << endl
			<< "yes - 1           no - 2" << endl;
		if (getCorrectNumber(1, 2) == 1)
			cin >> p;
		else
			cout << "Ok" << endl << endl;
	}
}

void addCS(CS& cs) // add new CS
{
	if (cs.name == "")
	{
		cin >> cs;
	}
	else
	{
		cout << "CS already exist\n" << endl
			<< "Do you want to rewrite it?" << endl
			<< "yes - 1           no - 2" << endl;
		if (getCorrectNumber(1, 2) == 1)
			cin >> cs;
		else
			cout << endl << "Ok" << endl << endl;;
	}
}

void viewAll(const pipe& p, const CS& cs) // print pipe and CS
{
	cout << "All objects\n\n";
	if (p.name != "")
		cout << "Pipe\n" << p << endl;
	else
		cout << "Pipe is not found\n" << endl;
	if (cs.name != "")
		cout << "CS\n" << cs << endl;
	else
		cout << "CS is not found\n" << endl;
}

void editPipe(pipe& p) // change status of repair for pipe
{
	if (p.name != "")
	{
		p.repair = !p.repair;
		cout << "New repair status for \"" << p.name << "\" pipe: " << p.repair << endl << endl;
		//cout << "Current repair status for pipe: " << p.repair << endl;
		//cout << "New status (true or 1 - under repair, false or 0 - ready for use): ";
		//p.repair = inputCheck<bool>();
	}
	else
		cout << "Pipe is not found\n" << endl;

}

void editCS(CS& cs) // change number of ws in repair for cs
{
	if (cs.name != "")
	{
		cout << "Current numer of ws in repair for \"" << cs.name << "\" CS: " << cs.ws_repair << endl;
		cout << "New number (int): ";
		cs.ws_repair = getCorrectNumber(0, cs.ws);;
	}
	else
		cout << "CS is not found\n" << endl;
}

void loadPipe(pipe& p, ifstream& fin)
{
	getline(fin, p.name);
	fin >> p.l; 
	fin >> p.d;
	fin >> p.repair;
}

void loadCS(CS& cs, ifstream& fin)
{
	getline(fin, cs.name);
	fin >> cs.ws;
	fin >> cs.ws_repair;
	fin >> cs.eff;
}


void loadFile(pipe& p, CS& cs) // загружает когда трубы КС отсутсств что делать?
{
	int npipe;
	int nCS;
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin)
	{
		fin >> npipe;
		if (npipe > 0)
			loadPipe(p, fin);

		fin >> nCS;
		if (nCS > 0)
			loadCS(cs, fin);

		cout << "Pipe loaded = " << npipe << endl
			<< "CS loaded = " << nCS << endl;
	}
	else
		cerr << "ERROR load" << endl;
	fin.close();
}

void savePipe(const pipe& p, ofstream& fout)
{
	fout << p.name << endl 
		<< p.l << endl 
		<< p.d << endl 
		<< p.repair << endl;;
}

void saveCS(const CS& cs, ofstream& fout)
{
	fout << cs.name << endl 
		<< cs.ws << endl 
		<< cs.ws_repair << endl 
		<< cs.eff << endl;
}

void saveFile(const pipe& p, const CS& cs) // как правильно сохранять?
{
	int npipe;
	int nCS;

	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout)
	{
		if (p.name == "")
		{
			npipe = 0;
			fout << npipe << endl;
		}
		else
		{
			npipe = 1;
			fout << npipe << endl;
			savePipe(p, fout);
		}
			
		if (cs.name == "")
		{
			nCS = 0;
			fout << nCS << endl;
		}
		else
		{
			nCS = 1;
			fout << nCS << endl;
			saveCS(cs, fout);
		}


		cout << "Pipe saved = " << npipe << endl
			<< "CS saved = " << nCS << endl;
	}
	else
		cerr << "ERROR save" << endl;
	fout.close();
}

int MenuOutput()
{

	pipe p;
	CS cs;

	while (1)
	{

		cout << "Menu\n\n"
			"1. Add pipe\n2. Add CS\n3. View all objects"
			"\n4. Edit pipe (repair status) \n5. Edit CS (numder of ws in repair)\n"
			"6. Save\n7. Download\n"
			"0. Exit\n" << endl;

		int option;
		cout << "Choose option 0-7 (int): ";
		option = getCorrectNumber(0, 7);
		cout << endl << endl;

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
				{
					saveFile(p, cs);
					break;
				}
				case 7:
				{
					loadFile(p, cs);
					break;
				}
				default:
				{
					cerr << "ERROR unexpected" << endl << "End of program" << endl;
					return 0;
					break;
				}
			}
		}
		else
		{
			cout << "Goodbye" << endl;
			return 0;
		}

		cout << endl << "Press Enter to continue";
		cin.get(); cin.get();
		cout << endl << endl;

	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Привет Hello" << endl;

	//unsigned int a = 0;
	//cout << a;

	//return 0;
	
	MenuOutput();


	return 0;
}