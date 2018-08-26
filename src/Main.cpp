/*
 * Main.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: valerio
 */

#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <exception>
#include "AVLTree.h"
using namespace std;

int main(int argc, char ** argv) {
	ifstream t(argv[1]);
	string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
	vector<int> nums;
	string delimiter = ",";

	size_t pos = 0;
	string token;

	while ((pos = str.find(delimiter)) != string::npos) {
		token = str.substr(0, pos);
		nums.push_back(stoi(token));
		str.erase(0, pos + delimiter.length());
	}
	nums.push_back(stoi(str));

	AVLTree * avlTree = new AVLTree();

	for (int i = 0; i < nums.size(); i++) {
		avlTree->insert(nums.at(i));
	}

	avlTree->printPretty(avlTree->getRoot(), 1, 4, cout);

	while(1) {
		cout << "Upisite add za dodavanje cvora, remove za brisanje cvora, exit za izlaz iz programa" << endl;
		string s;
		getline (cin, s);
		if (s == "add") {
			cout << "Upišite koji broj zelite dodati" << endl;
			string num;
			getline(cin, num);
			try {
				int i = stoi(num);
				avlTree->insert(i);
				avlTree->printPretty(avlTree->getRoot(), 1, 4, cout);
			}
				catch(exception& e) {
				cout << "Nesto je proslo po zlu, pokusajte ponovno" << endl;
				continue;
			}
		}
		else if (s == "remove") {
			cout << "Upišite koji broj zelite izbrisati" << endl;
			string num;
			getline(cin, num);
			try {
				int i = stoi(num);
				avlTree->remove(i);
				avlTree->printPretty(avlTree->getRoot(), 1, 4, cout);
			}
			catch(exception& e) {
				cout << "Nešto je prošlo po zlu, pokušajte ponovno" << endl;
			}
		}
		else if (s == "exit") {
			break;
		}
		else {
			cout << "Unijeli ste krivu naredbu, pokusajte ponovno" << endl;
		}
	}

	return 0;
}

