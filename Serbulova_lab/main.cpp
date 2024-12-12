#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
#include "refinary.h"
using namespace std;
using namespace chrono;

int MenuOutput()
{
	refinary ref;
	while (1)
	{
		cout << "---------------\nMenu\n"
			"1. Add pipe\n2. Add CS\n3. View all objects\n" 
			"4. Pipe's editor\n5. CS's editor\n"
			"6. Save refinary system\n7. Download refinary system\n8. Delete refinary system\n"
			"0. Exit\n---------------\n";
		cout << "Choose option: ";

		switch (getCorrectNumber(0, 8))
		{
		case 0:
		{
			cout << "Goodbye" << endl;
			return 0;
		}
		case 1:
		{  
			cout << "Adding pipe" << endl << endl;
			ref.startPipe();
			break;
		}
		case 2:
		{
			cout << "Adding CS" << endl << endl;
			ref.startCS();
			break; 
		}
		case 3:
		{
			cout << "Viewing all objects" << endl << endl;
			ref.viewAll();
			break;
		}
		case 4:
		{
			cout << "Opening Pipe's editor" << endl << endl;
			ref.pipeEditor();
			break;
		}
		case 5:
		{
			cout << "Opening CS's editor" << endl << endl;
			ref.CSEditor();
			break;
		}
		case 6:
		{
			cout << "Saving your system" << endl << endl;
			ref.saveFile();
			break;
		}
		case 7:
		{
			cout << "Downloading refinary system" << endl << endl;
			ref.loadFile();
			break;
		}
		case 8:
		{
			cout << "Deleting refinary system" << endl << endl;
			ref.deleteAll();
			break;
		}
		default:
		{
			cerr << "ERROR unexpected" << endl << "Prigrammer forgot to use getCorrectNumber function :)" << endl;
			return 0;
		}
		}
		cout << endl;
		//cin.get(); cin.get();
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Привет Hello" << endl;

	//логирование в отдельный файл
	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);

	MenuOutput();

	return 0;
}