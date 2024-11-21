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
			cout << "ERROR wrong name " << exeption << " --> try again: ";
			cerr << str << endl;
			getline(in >> ws, str);
		}*/
	cerr << str << endl; // LOGGING!!!!!!!
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
		cout << "ERROR wrong type --> try again: ";
		cerr << x << endl; // LOGGING!!!!!!!
	}
	cerr << x << endl; // LOGGING!!!!!!!
	return x;
}
template int inputNumber(istream& in);
template double inputNumber(istream& in);

template <typename T = int>
T getCorrectNumber(T a, T b, bool included, istream& in) // check that number is in range(a,b)
{
	T x = inputNumber<T>(in);
	while ((included && (x<a || x>b))
		|| (!included && (x <= a || x >= b)))
	{
		string str_included = included ? "= " : " ";
		cout << "ERROR wrong number: min >" << str_included << a << " and max <" << str_included << b << " --> try again: ";
		x = inputNumber<T>(in);
	}
	return x;
}
template int getCorrectNumber<int>(int a, int b, bool included, istream& in);
template double getCorrectNumber<double>(double a, double b, bool included, istream& in);

template <typename T> // как проверить красиво на полож число??? --> никак, сделали через флаг	
T getPositiveNumber(istream& in)
{
	return getCorrectNumber<T>(0, std::numeric_limits<T>::max(), false, in);
}
template int getPositiveNumber(istream& in);
template double getPositiveNumber(istream& in);

bool confirm(string message)
{
	cout << message <<"\n0.no\n1.yes" << endl;
	return getCorrectNumber(0, 1);
}