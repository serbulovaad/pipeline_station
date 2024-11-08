#include "help.h"
using namespace std;

string inputString(istream& in) // string input for whole line
//string inputString(istream& in, const string& exeption)

{
	string str;
	getline(in >> ws, str);
	/*if (exeption != "")
		while (str == exeption)
		{
			cerr << "ERROR wrong name " << exeption << " --> try again: ";
			getline(in >> ws, str);
		}*/
	cerr << str; // LOGGING!!!!!!!
	return str;
}

template <typename T> // template to check different types of variables
T inputNumber(istream& in) // check type
{
	T x;
	while ((in >> x).fail()	// check type
		|| in.peek() != '\n')	// is buffer empty (int/float check)
	{
		in.clear();
		in.ignore(10000, '\n');
		cerr << "ERROR wrong type --> try again: ";
	}
	cerr << x; // LOGGING!!!!!!!
	return x;
}
template int inputNumber(istream& in);
template double inputNumber(istream& in);

template <typename T>
T getCorrectNumber(T a, T b, bool included, istream& in) // check that number is in range(a,b)
{
	T x = inputNumber<T>(in);
	while ((included && (x<a || x>b))
		|| (!included && (x <= a || x >= b)))
	{
		string str_included = included ? "= " : " ";
		cerr << "ERROR wrong number: min >" << str_included << a << " and max <" << str_included << b << " --> try again: ";
		x = inputNumber<T>(in);
	}
	return x;
}
template int getCorrectNumber(int a, int b, bool included, istream& in);
template double getCorrectNumber(double a, double b, bool included, istream& in);

template <typename T> // ��� ��������� ������� �� ����� �����??? --> �����, ������� ����� ����	
T getPositiveNumber(istream& in)
{
	return getCorrectNumber<T>(0, std::numeric_limits<T>::max(), false, in);
}
template int getPositiveNumber(istream& in);
template double getPositiveNumber(istream& in);


bool confirm()
{
	cout << "Do you want to do it?" << endl
		<< "yes - 1           no - 2" << endl;
	return getCorrectNumber(1, 2);
}