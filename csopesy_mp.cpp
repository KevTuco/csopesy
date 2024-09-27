//our functions
#include "Headers/Utils.h"
//import all libraries
#include "Headers/stdc++.h"

using namespace std;

class ScreenProcess;

void printActiveProcesses(vector <ScreenProcess> processList);


//------------------------------------------

class ScreenProcess {
private:
	string processName;
	string timeMade;
	int linesCompleted;

public:
	ScreenProcess(const string& name) {
		processName = name;
		timeMade = getTime();
		linesCompleted = 0;
	}
	void runCommand(const string& command) {
		// Here, you can add logic to handle commands
		cout << "Running command: " << command << endl;
		// You can implement the command handling logic here
	}
	void showProcessInfo() {
		cout << "Process Name: " << processName << endl;
		cout << "Time Created: " << timeMade << endl;
		cout << "Lines Completed: " << linesCompleted << endl;
	}
	void open() {
		//takeOver
		showProcessInfo();

		string input;
		vector <ScreenProcess> processList;
		while (true) {
			cout << "INSIDE_"<<processName <<">";
			getline(cin, input);
			vector<string> tokenizedInput = splitInput(input);
			string temp_command = tokenizedInput[0];

			//----------------------------------------------
			if (temp_command == "screen") {
				if (tokenizedInput.size() == 1) {
					cout << "no arguments provided please use -r or -s" << endl;
					continue;
				}
				string temp_arg = tokenizedInput[1];
				if (temp_arg == "-r") {
					// reattach
					bool found = false;
					for (auto& element : processList) {
						if (element.getProcessName() == tokenizedInput[2]) {
							element.open();  // Found the process, open it
							found = true;    // Set found flag to true
							break;           // Exit the loop after finding the process
						}
					}
					if (!found) {
						cout << "Process not found, try using 'screen -ls' to list currently active processes" << endl;
					}
				}
				else if (temp_arg == "-s") {
					// check if the process with the same name already exists
					bool exists = false;
					for (auto& element : processList) {
						if (element.getProcessName() == tokenizedInput[2]) {
							exists = true;
							break;
						}
					}

					if (exists) {
						cout << "A process with the name '" << tokenizedInput[2] << "' already exists. Please use a unique name." << endl;
					}
					else {
						// create new process if the name is unique
						ScreenProcess newScreen(tokenizedInput[2]);
						processList.push_back(newScreen);
						cout << "New process '" << tokenizedInput[2] << "' added!" << endl;
						newScreen.open();
					}
				}
				else if (temp_arg == "-ls") {
					printActiveProcesses(processList);
				}
			}
			else if (temp_command == "clear") {
				system("cls");
			}
			else {
				if (!handleInput(input)) { break; }
			}
			//----------------------------------------------
		}

	}
	
	string getProcessName(){
		return processName;
	}
};


void printActiveProcesses(vector <ScreenProcess> processList){
	cout << ESC << YELLOW_TXT << "------------------------------" << RESET << endl;
	cout << processList.size() << " ACTIVE PROCESSES" << endl;  // Print vector size

	for (auto element : processList) {
		element.showProcessInfo();
		cout << endl;
	}
	cout << ESC << YELLOW_TXT << "------------------------------" << RESET << endl;
}

int main() {

	string input;
	printHeader();

	vector <ScreenProcess> processList;
	while (true) {
		cout << "Enter a command: ";
		getline(cin, input);

		vector<string> tokenizedInput = splitInput(input);
		//splits the input by space and puts it in vector

		// DUBUGGING: prints all elements of a vector
		//printVector(tokenizedInput);

		//LAZY IMPLEMENTATION
		string temp_command = tokenizedInput[0];

		//override screen input handling
		if (temp_command == "screen") {
			if (tokenizedInput.size() == 1) {
				cout << "no arguments provided please use -r or -s" << endl;
				continue;
			}
			string temp_arg = tokenizedInput[1];
			if (temp_arg == "-r") {
				// reattach
				bool found = false;
				for (auto& element : processList) {
					if (element.getProcessName() == tokenizedInput[2]) {
						element.open();  // Found the process, open it
						found = true;    // Set found flag to true
						break;           // Exit the loop after finding the process
					}
				}
				if (!found) {
					cout << "Process not found, try using 'screen -ls' to list currently active processes" << endl;
				}
			}
			else if (temp_arg == "-s") {
				// check if the process with the same name already exists
				bool exists = false;
				for (auto& element : processList) {
					if (element.getProcessName() == tokenizedInput[2]) {
						exists = true;
						break;
					}
				}

				if (exists) {
					cout << "A process with the name '" << tokenizedInput[2] << "' already exists. Please use a unique name." << endl;
				}
				else {
					// create new process if the name is unique
					ScreenProcess newScreen(tokenizedInput[2]);
					processList.push_back(newScreen);
					cout << "New process '" << tokenizedInput[2] << "' added!" << endl;
					newScreen.open();
				}
			}
			else if (temp_arg == "-ls") {
				printActiveProcesses(processList);
			}

		}
		else {
			if (!handleInput(input)) { return 0; }
		}



	}
}