﻿#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
#include "refinary.h"
#include "graph.h"
using namespace std;
using namespace chrono;

void christmasTree()
{
	std::cout << "        *"<< endl;
	std::cout << "       / \\" << endl;
	std::cout << "      /о/_\\" << endl;
	std::cout << "      / /о\\" << endl;
	std::cout << "     /8/ / \\   Happy New Year!" << endl;
	std::cout << "    /_/8/_/_\\  С Новым Годом!" << endl;
	std::cout << "    /о/ /8/ \\  " << endl;
	std::cout << "   / /о/ /8/ \\ " << endl;
	std::cout << "  /8/ /о/ /8/ \\" << endl;
	std::cout << " /_/8/_/о/_/8/_\\" << endl;
	std::cout << "       |_|" << endl;
}

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
			christmasTree();
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
			if (!ref.getLinkset().empty())
				graph::topological_sort(graph::create_matrix(ref.getLinkset()));
			else
				cout << "Graph do not found" << endl;
			break;
		}
		case 10:
		{
			cout << "Max flow" << endl << endl;
			if (!ref.getLinkset().empty())
			{
				cout << "From CS ID = ";
				int fromID = inputNumber<int>();
				cout << "To CS ID = ";
				int toID = inputNumber<int>();
				cout << endl;

				vector<vector<double>> mtr = graph::create_double_matrix(ref.getLinkset(), ref.pipemap);
				double maxFlow = graph::max_flow(mtr, fromID-1, toID-1);
				std::cout << "Max flow from ID = " << fromID << " to ID = " << toID << " is " << maxFlow << std::endl << std::endl;
			}
			else
				cout << "Graph do not found" << endl;
			break;
		}
		case 11:
		{
			cout << "Best path" << endl << endl;
			if (!ref.getLinkset().empty())
			{
				cout << "From CS ID = ";
				int fromID = inputNumber<int>();
				cout << "To CS ID = ";
				int toID = inputNumber<int>();
				vector<vector<double>> mtr = graph::create_double_matrix(ref.getLinkset(), ref.pipemap);

				vector<int> path = graph::short_path(mtr, fromID - 1, toID - 1);

				if (path.empty() || path.size() == 1) {
					cout << "Path not found!" << endl;
				}
				else {
					cout << "Found Way: ";
					for (int node : path) {
						cout << node+1 << " ";
					}
					cout << endl;

					double length = graph::path_length(mtr, path);
					cout << "Len: " << length << endl;
				}
			}
			else
				cout << "Graph do not found" << endl;
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
	cout << "Привет Hello" << endl;
	cout << "Happy new year!" << endl;


	//логирование в отдельный файл
	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);

	MenuOutput();

	return 0;
}