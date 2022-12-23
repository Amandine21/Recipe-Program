#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Recipies.h"
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------
void interface(){
	cout << "--------------------------------------------------------" << endl;
	cout <<"Recipie Program" << endl;
	cout << "1.) Look up Recipie" << endl;
	cout << "2.) Add Recipie" << endl;
	cout << "3.) Remove Recipie" << endl;
	cout << "4.) Download Recipie into a PDF file" << endl;
}

int main(){
	Recipie_Book book;
	book.readfile();
	book.create_book();
	string option, iteration;

	while((iteration != "n")){
		interface();	
		cout << "--------------------------------------------------------" << endl;
		cout << "Pick an option: ";
		getline(cin, option); 
		if(option == "1")
			cout << "something" << endl;					//Use the map function
		else if(option == "2")
			book.add_new_recipie();			
		else if(option == "3"){
			book.view_book();
			bool if_remove = false;
			int page_number;
			while(if_remove != true){
				cout << "Please Enter the page number of the Recipie you would like to remove: ";
				cin >> page_number;
				if_remove = book.remove_recipie(page_number);
				string verify;
				if(if_remove == false){
					cout << "Would you like to try again? (Y/n): ";
					getline(cin, verify);
					if(verify == "n")
						break;
				}
			}

		}
		else if(option == "4")
			cout << "something 2" << endl; 					//download the map
		else{
			cout << "Error: " << "\"" << option << "\"" << " is not an option "  << endl;
			continue;
		}
		interface();
		cout << "--------------------------------------------------------" << endl;
		cout << "Wold you like to go again (Y/n): ";
		getline(cin, iteration);	
	}
	return 0;	
}
