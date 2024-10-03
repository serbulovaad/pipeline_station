#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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
	int ws_work; // // workstations in work
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
T getCorrectNumber(T a, T b, bool included = true, istream& in = cin) // check that number is in range(a,b)
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

template <typename T> // как проверить красиво на полож число??? --> никак, сделали через флаг	
T getPositiveNumber(istream& in = cin)
{
	return getCorrectNumber<T>(0, std::numeric_limits<T>::max(), false, in);
}

string inputString(istream& in, const string& exeption = "") // string input for whole line
{
	string str;
	getline(in >> ws, str);
	if (exeption != "")
		while (str == exeption)
		{
			cerr << "ERROR wrong name: " << exeption << " --> try again: ";
			getline(in >> ws, str);
		}
	return str;
}

ostream& operator << (ostream& out, const pipe& p) // output for pipe
{
	cout << "Pipe" << endl;
	out << "name: " << p.name << endl
		<< "d: " << p.d << endl
		<< "l: " << p.l << endl
		<< "repair status: " << p.repair << endl;

	return out;
}

ostream& operator << (ostream& out, const CS& cs) // output for CS
{
	cout << "CS" << endl;
	out << "name: " << cs.name << endl
		<< "ws: " << cs.ws << endl
		<< "ws in work: " << cs.ws_work << endl
		<< "eff: " << cs.eff << endl;

	return out;
}

istream& operator >> (istream& in, pipe& p) // intput for pipe // как тут сделать проверку? -> сделали  inputCheck
{
	cout << "Pipe" << endl;
	cout << "name (str) = ";
	p.name = inputString(in, "pipe");
	cout << "d (int) = ";
	p.d = getPositiveNumber<int>(in);
	cout << "l (double) = ";
	p.l = getPositiveNumber<double>(in);
	cout << "repair status: 0 (ready for use)" << endl;

	return in;
}

istream& operator >> (istream& in, CS& cs) // intput for CS // как тут сделать проверку? -> сделали 
{
	cout << "CS" << endl;
	cout << "name (str): ";
	cs.name = inputString(in, "CS");
	cout << "ws (int) = ";
	cs.ws = getPositiveNumber<int>(in);
	cout << "ws in work (int) = ";
	cs.ws_work = getCorrectNumber<int>(0, cs.ws, true, in);
	cout << "eff (double) = ";
	cs.eff = getPositiveNumber<double>(in);

	return in;
}

bool confirm()
{
	cout << "Do you want to rewrite it?" << endl
		<< "yes - 1           no - 2" << endl;
	return getCorrectNumber(1, 2);
}

void addPipe(pipe& p) // add new pipe
{
	if (p.name == "")
	{
		cout << "Add object" << endl;
		cin >> p;
	}
	else
	{
		cout << "Pipe already exist" << endl;
		if (confirm)
			cin >> p;
	}
}

void addCS(CS& cs) // add new CS
{
	if (cs.name == "")
	{
		cout << "Add object" << endl;
		cin >> cs;
	}
	else
	{
		cout << "CS already exist" << endl;
		if (confirm)
			cin >> cs;
	}
}

void viewAll(const pipe& p, const CS& cs) // print pipe and CS
{
	cout << "View all objects" << endl;
	if (p.name != "")
		cout << p;
	else
		cout << "Pipe is not found" << endl;
	if (cs.name != "")
		cout << cs;
	else
		cout << "CS is not found" << endl;
}

void editPipe(pipe& p) // change status of repair for pipe
{
	if (p.name != "")
	{
		p.repair = !p.repair;
		cout << "New repair status for pipe \"" << p.name << "\": " << p.repair<< endl;
	}
	else
		cout << "Pipe is not found" << endl;

}

void editCS(CS& cs) // change number of ws in repair for cs
{
	if (cs.name != "")
	{
		cout << "Numer of all ws for CS \"" << cs.name << "\" :" << cs.ws << endl;
		cout << "Input number of ws in work (int): ";
		cs.ws_work = getCorrectNumber(0, cs.ws);;
	}
	else
		cout << "CS is not found" << endl;
}

void loadPipe(pipe& p, ifstream& fin)
{
	p.name = inputString(fin);
	fin >> p.l; 
	fin >> p.d;
	fin >> p.repair;
}

void loadCS(CS& cs, ifstream& fin)
{
	cs.name = inputString(fin);
	fin >> cs.ws;
	fin >> cs.ws_work;
	fin >> cs.eff;
}

void loadFile(pipe& p, CS& cs) // загружает 
{
	int npipe;
	int nCS;
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin)
	{
		fin >> npipe;
		if (npipe > 0) // проверка кол-ва труб
			loadPipe(p, fin);
		else
		{
			pipe empty_p;
			p = empty_p;
		}


		fin >> nCS;
		if (nCS > 0)
			loadCS(cs, fin); //проверка кол-ва кс
		else
		{
			CS empty_cs;
			cs = empty_cs;
		}

		cout << "Pipe loaded = " << npipe << endl
			<< "CS loaded = " << nCS << endl;
	}
	else
		cerr << "ERROR load" << endl;
	fin.close(); // см ниже
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
		<< cs.ws_work << endl 
		<< cs.eff << endl;
}

void saveFile(const pipe& p, const CS& cs) // как правильно сохранять? --> либо флагами - любой порядок, либо отображ числа труб и кс - строгий порядок
{
	int npipe = 0;
	int nCS = 0;

	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout)
	{
		if (p.name == "") // for pipe
			fout << npipe << endl;
		else
		{
			npipe = 1;
			fout << npipe << endl;
			savePipe(p, fout);
		}

		if (cs.name == "") // for cs
			fout << nCS << endl;
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
	fout.close(); // необязательная т.к диструктор разрушает fout после закрытия функции
}



int MenuOutput()
{
	pipe p;
	CS cs;

	while (1)
	{
		cout << "Menu\n"
			"1. Add pipe\n2. Add CS\n3. View all objects"
			"\n4. Edit pipe (repair status) \n5. Edit CS (numder of ws in repair)\n"
			"6. Save\n7. Download\n"
			"0. Exit\n";
		cout << "Choose option 0-7 (int): ";

		switch (getCorrectNumber(0, 7))
		{
		case 0:
		{
			cout << "Goodbye" << endl;
			return 0;
		}
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
			cerr << "ERROR unexpected" << endl << "Prigrammer forgot to use getCorrectNumber function :)" << endl;
			return 0;
		}
		}
		//cout << endl << "Press Enter to continue";
		//cin.get(); cin.get();
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Привет Hello" << endl;

	MenuOutput();

	return 0;
}

//void saveFile(const pipe& p, const CS& cs) // как правильно сохранять? --> либо флагами - любой порядок, либо отображ числа труб и кс - строгий порядок
//{
//	int npipe = 0;
//	int nCS = 0;
//
//	ofstream fout;
//	fout.open("data.txt", ios::out);
//	if (fout)
//	{
//		if (p.name == "") // for pipe
//			fout << npipe << endl;
//		else
//		{
//			npipe = 1;
//			fout << npipe << endl;
//			savePipe(p, fout);
//		}
//		if (cs.name == "") // for cs
//			fout << nCS << endl;
//		else
//		{
//			nCS = 1;
//			fout << nCS << endl;
//			saveCS(cs, fout);
//		}
//		cout << "Pipe saved = " << npipe << endl
//			<< "CS saved = " << nCS << endl;
//	}
//	else
//		cerr << "ERROR save" << endl;
//	fout.close(); // необязательная т.к диструктор разрушает fout после закрытия функции
//}

//void loadAllPipe(pipe& p)
//{
//	int npipe{};
//
//	ifstream fin;
//	fin.open("data.txt", ios::in);
//	if (fin)
//	{
//		while (fin)
//		{
//			if (inputString(fin) == "pipe")
//			{
//				fin >> npipe;
//				if (npipe > 0) // проверка кол-ва труб
//					loadPipe(p, fin);
//				else
//				{
//					pipe empty_p;
//					p = empty_p;
//				}
//			}
//		}
//	}
//	else
//		cerr << "ERROR load pipe" << endl;
//	fin.close();
//	cout << "Pipe loaded = " << npipe << endl;
//}
//
//void loadAllCS(CS& cs)
//{
//	int nCS{};
//
//	ifstream fin;
//	fin.open("data.txt", ios::in);
//	if (fin)
//	{
//		while (fin)
//		{
//			if (inputString(fin) == "CS")
//			{
//				fin >> nCS;
//				if (nCS > 0)
//					loadCS(cs, fin); //проверка кол-ва кс
//				else
//				{
//					CS empty_cs;
//					cs = empty_cs;
//				}
//
//			}
//		}
//	}
//	else
//		cerr << "ERROR load CS" << endl;
//	fin.close();
//	cout << "CS loaded = " << nCS << endl;
//}
//
//void loadFile(pipe& p, CS& cs) // загружает когда трубы КС отсутсств что делать?
//{
//	loadAllPipe(p);
//	loadAllCS(cs);
//}



//void saveFile(const pipe& p, const CS& cs) // как правильно сохранять? --> либо флагами - любой порядок, либо отображ числа труб и кс - строгий порядок
//{
//	int npipe = 0;
//	int nCS = 0;
//
//	ofstream fout;
//	fout.open("data.txt", ios::out);
//	if (fout)
//	{
//
//		fout << "pipe" << endl;
//		if (p.name == "") // for pipe
//			fout << npipe << endl;
//		else
//		{
//			npipe = 1;
//			fout << npipe << endl;
//			savePipe(p, fout);
//		}
//
//
//		fout << "CS" << endl;
//		if (cs.name == "") // for cs
//			fout << nCS << endl;
//		else
//		{
//			nCS = 1;
//			fout << nCS << endl;
//			saveCS(cs, fout);
//		}
//		cout << "Pipe saved = " << npipe << endl
//			<< "CS saved = " << nCS << endl;
//	}
//	else
//		cerr << "ERROR save" << endl;
//	fout.close(); // необязательная т.к диструктор разрушает fout после закрытия функции
//}