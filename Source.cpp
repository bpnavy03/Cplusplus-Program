/* Bryan Pirrone
   CS - 210
   Project 3
   6/17/2022
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>


using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("python_modules.PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python_modules.PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python_modules.PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}



void DisplayMenu() {
	/* Prints menu to console
	   Do While until appropriate command entered
	   Verified input desired
	*/
	bool program_run = true; //runs loop
	int userInput; //user input for menu
	string grocery; //for grocery lookup selection

	do {
		cout << "****************************************************************" << endl;
		cout << "****************************************************************" << endl;
		cout << "\t\t\t" << "Corner Grocer" << endl;
		cout << "\t\t\t" << "Select Option" << endl;
		cout << "****************************************************************" << endl;
		cout << "1 - Display a list of items purchased today and quantities" << endl;
		cout << "2 - Display total quantity purchased of an item" << endl;
		cout << "3 - Display histogram of items purchase" << endl;
		cout << "4 - Exit" << endl;
		cout << "****************************************************************" << endl;
		cout << endl;
		cin >> userInput;
		cout << endl;

		if (userInput == 1) {
			//prints total items purchased today and quantities
			cout << "Total items purchased today and quantities" << endl;
			//reads file in python
			CallProcedure("readFile");
		}

		else if (userInput == 2) {
			//Prompts user for product to look up, calls on python function
			//Prints product and frequency to the console
			string userString;
			cout << "Enter the item you want to look up: " << endl;
			cout << endl;
			cin >> userString; //user input for product to look up
			cout << endl;
			int tot = callIntFunc("getInventory", userString); //determines frequency of user selected product
			if (tot == -1) {
				cout << "None of that item was purchased" << endl; //Prints if product is not listed
			}
			else {
				cout << tot << " " << userString << " were purchased" << endl; //Prints product and frequency to the console
				cout << endl;
			}
		}

		else if (userInput == 3) {
			//Calls python function to read a file, count and sort product information
			//Writes to frequency.dat file
			//reads frequency.dat file and creates histogram
			cout << "Historgram" << endl;
			cout << endl;
			CallProcedure("output");
		}

		else if (userInput == 4) {
			//Terminates program based on user input
			cout << "Goodbye!" << endl;
			return;
		}

		else if (userInput > 4 || userInput < 1) {
			//Prints request to select a correct value
			cout << "Please select 1, 2, 3, or 4" << endl;
		}
	} while (program_run == true); //Control program
}

int main() {
	DisplayMenu(); //Displays menu
}
