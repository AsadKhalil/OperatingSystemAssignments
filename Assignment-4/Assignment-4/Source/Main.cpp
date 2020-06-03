#include <iostream>

#include "VirtualFileSystem.h"
#include <string.h>
using namespace std;


vector<string> Tokenize(const string& line) {

	vector<string> result;

	char* buffer = new char[line.length() + 1];

	strcpy(buffer, &line[0]);

	char* token = strtok(buffer, " \n");

	if (token)
		result.push_back(token);

	while (token = strtok(nullptr, " \n"))
		result.push_back(token);

	return result;
}

void Menu() 
{

	cout << endl << "Required System Calls    \t   Explaination     " << endl << endl;
	cout << "ls \t\t --List All Direcctoriees--" << endl<< endl;
	cout << "cd \t\t --Change Directory--" << endl<< endl;
	cout << "mkdir \t\t --Make Directory--" << endl<< endl;
	cout << "rm \t\t --Remove Directory--" << endl<< endl;
	cout << "import \t\t --Import Files to Virtual File--" << endl<< endl;
	cout << "status \t\t --Show Disk's Status" << endl<< endl;
	cout << "Q    \t\t ---Quit--" << endl<< endl;
}

int main() {
	
	VFS::Start();

	char line[256];
	bool running = true;

	Menu();

	while (running) {

		string dir = VFS::GetInstance()->GetCurrentDirectory();

		cout << dir << ">> ";

		cin.getline(line, 256);

		auto tokens = Tokenize(line);

		if (tokens.size()) {

			if (tokens[0] == "ls") 
			{

				VFS::GetInstance()->ListDirectory();
			}
			else if (tokens[0] == "cd") {

				if (tokens.size() >= 2)
				{
					VFS::GetInstance()->ChangeDirectory(tokens[1]);
				}
				else
					cout << endl << "Incorrect Syntax ! Check Again" << endl << endl;
			}
			
			else if (tokens[0] == "rm") {

				if (tokens.size() >= 2)
				{
					VFS::GetInstance()->RemoveDirectory(tokens[1]);
				}
				else
					cout << endl << "Incorrect Syntax ! Check Again" << endl << endl;
			}
			else if (tokens[0] == "mkdir") {

				if (tokens.size() >= 2)
				{
					VFS::GetInstance()->MakeDirectory(tokens[1]);
				}
				else
					cout << endl << "Incorrect Syntax ! Check Again" << endl << endl;
			}			

			else if (tokens[0] == "status") {
			
				VFS::GetInstance()->DiskStatus();
			}
			else if (tokens[0] == "import") {
			
				if (tokens.size() >= 2)
				{
					VFS::GetInstance()->ImportFile(tokens[1]);
				}
				else
					cout << endl << "Incorrect Syntax ! Check Again" << endl << endl;
			}
			else if (tokens[0] == "q" || tokens[0] == "Q") {

				break;
			}
			else {

				cout << endl << "You Entered an Invalid Command !!!! Try again" << endl << endl;
			}
		}
	}

	VFS::PowerOff();
	return 0;
}
