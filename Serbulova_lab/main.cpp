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
			"1. Print all objects\n2. Print Refinary\n3. Add pipe\n4. Add CS\n" 
			"5. Pipe's editor\n6. CS's editor\n7. Connect CS\n8. Disconnect CS\n"
			"9. Topological sorting\n10. Max flow\n11. Best path\n"
			"12. Save refinary system\n13. Download refinary system\n14. Delete refinary system\n"
			"0. Exit\n---------------\n";
		cout << "Choose option: ";

		switch (getCorrectNumber(0, 14))
		{
		case 0:
		{
			cout << "Goodbye" << endl;
			return 0;
		}
		case 1:
		{
			cout << "Print all objects" << endl << endl;
			ref.viewAll();
			break;
		}
		case 2:
		{
			cout << "Print Refinary" << endl << endl;
			ref.printConnection();
			break;
		}
		case 3:
		{  
			cout << "Adding pipe" << endl << endl;
			ref.startPipe();
			break;
		}
		case 4:
		{
			cout << "Adding CS" << endl << endl;
			ref.startCS();
			break; 
		}
		case 5:
		{
			cout << "Opening Pipe's editor" << endl << endl;
			ref.pipeEditor();
			break;
		}
		case 6:
		{
			cout << "Opening CS's editor" << endl << endl;
			ref.CSEditor();
			break;
		}
		case 7:
		{
			cout << "Connecting CSs" << endl << endl;
			ref.connectCS();
			break;
		}
		case 8:
		{
			cout << "Disconnect CS" << endl << endl;
			ref.disconnectCS();
			break;
		}
		case 9:
		{
			cout << "Topological sorting" << endl << endl;
			//ref.start_sort();
			break;
		}
		case 10:
		{
			cout << "Max flow" << endl << endl;
			//ref.start_pathlen();
			break;
		}
		case 11:
		{
			cout << "Best path" << endl << endl;
			//ref.start_short();
			break;
		}
		case 12:
		{
			cout << "Saving your system" << endl << endl;
			ref.saveFile();
			break;
		}
		case 13:
		{
			cout << "Downloading refinary system" << endl << endl;
			ref.loadFile();
			break;
		}
		case 14:
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
	cout << "������ Hello" << endl;

	//����������� � ��������� ����
	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);

	MenuOutput();

	return 0;
}