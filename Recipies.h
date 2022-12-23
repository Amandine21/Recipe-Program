#ifndef RECIPIES_H
#define RECIPIES_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <climits>
#include <fstream>
#include <sstream>

using namespace std;
//----------------------------------------------------------------------------------------------------
//store unordered recipies on a 2D array genre by recipie sorted
//Put each recipie into a unordered map as page number and book from the 2D array
class empty_book{};
//--------------------------------------------------------
struct Recipie{
		string genre;
		string title;
		vector<string> recipie;
		Recipie():genre("N/A"), title("N/A"), recipie(){}												//Use that cool constructor from PA 2
		Recipie(string passed_genre, string passed_title, vector<string> passed_vector): 
		genre(passed_genre), title(passed_title), recipie(passed_vector){} 
		Recipie& operator=(const Recipie& rhs);	
};
//--------------------------------------------------------
class Recipie_Book{
	private:
	  	unordered_map<int,Recipie> book;																//Organize the book into their respected recpiies according to page numbers
		vector<vector<Recipie>> unordered_recipies;
	public:
		Recipie_Book(){}
		void add_new_recipie();//																						
		void add_recipie(Recipie new_recipie);
		void readfile();																				//Read files into the the thing
		void sort_genres();																				//Define an equal operator and use Selection Sort!!!																			
		void view_recipies();//
		void create_book();//
		void view_book();//
		bool cannidate_minimum_strings(string string_one, string string_two);
		bool remove_recipie(int page_number);//
		void download_recipie();
};
//--------------------------------------------------------
ostream& operator<<(ostream& os, const Recipie& rhs){
	os << rhs.genre << endl;
	os << rhs.title << endl;
	for(auto& instructions: rhs.recipie){
		os << instructions << endl;
	}
	return os;	
}
//--------------------------------------------------------
Recipie& Recipie::operator=(const Recipie& rhs){
	genre = rhs.genre;
	title = rhs.title;
	recipie = rhs.recipie;
	return *this;
}
//--------------------------------------------------------
bool Recipie_Book::remove_recipie(int page_number){
	if(book.find(page_number) == book.end())
		return false;
	book.erase(page_number);
	return true;
}
//--------------------------------------------------------
void Recipie_Book::create_book(){																//Assume the unordered_recipies is sorted properly
	long unsigned int page_number = 0;
	for(long unsigned int genre = 0; genre < unordered_recipies.size(); genre++){
		page_number += genre;
		for(long unsigned int recipie = 0; recipie < unordered_recipies[genre].size(); recipie++)
				book.insert({page_number, unordered_recipies[genre][recipie]});
	}
}	
//--------------------------------------------------------
Recipie create_new_recipie(){  //
	Recipie new_recipie;
	string genre, title, line;

	cout << "Please Enter the Genre: ";
	getline(cin, genre);
	cout << "Please Enter the Title: ";
	getline(cin, title);
	new_recipie.genre = genre;
	new_recipie.title = title;
	cout << "--------------------------------------------------------" << endl;
	cout << "Type The directions for the Recipie" << endl << endl;
	cout << "\"Measurement - Ingredient\" for the Ingredient Format" << endl;
	cout << "Type exit when you are finished" << endl;
	line = "Ingredient:";
	cout << "--------------------" << endl;
	new_recipie.recipie.push_back(line);
	while(line != "exit"){
		getline(cin, line);
		new_recipie.recipie.push_back(line);
	}

	cout << "\n\"Step #.) Directions \" for the Directions Format" << endl;
	cout << "Type exit when you are finished" << endl;
	line = "Directions:";
	cout << "--------------------" << endl;
	new_recipie.recipie.push_back(line);
	while(line != "exit"){
		getline(cin, line);
		new_recipie.recipie.push_back(line);
	}
	return new_recipie;
}
//--------------------------------------------------------
void Recipie_Book::add_new_recipie(){
	Recipie new_recipie = create_new_recipie();
}
//--------------------------------------------------------
void Recipie_Book::readfile(){
	int file_number = 0;

	for(int i = 0; i < INT_MAX; i++){
		string filename = "/mnt/c/Users/lxhan/Documents/Recipie_Program/Recipies/Recipie_" + to_string(file_number) + ".txt";
		ifstream ifs(filename);
		
		if(!ifs.is_open()){
			break;
		}

		string genre;
		string line;
		string title;
		vector<string> recipie;

		getline(ifs, genre);
		getline(ifs, line);
		getline(ifs, title);

		while(getline(ifs, line)){
			recipie.push_back(line);
		}
		Recipie new_recipie(genre, title, recipie);
		// unordered_recipies.push_back(new_recipie);
		file_number++;
	}
}
//--------------------------------------------------------
void Recipie_Book::add_recipie(Recipie new_recipie){
	for(long unsigned int genre = 0; genre < unordered_recipies.size(); genre++){
		for(long unsigned int recipie = 0; recipie < unordered_recipies[genre].size(); recipie++){
			if(unordered_recipies[genre][recipie].genre == new_recipie.genre){
					unordered_recipies[genre].push_back(new_recipie);
					//Sort the strings in respect to recipie
			}
		}
	}
	// unordered_recipies.push_back(new_recipie);
	// unordered_recipies.back().push_back(new_recipie);
	// Sort the strings in respect to genre
}
//--------------------------------------------------------
void Recipie_Book::sort_genres(){																		//Use Bubble sort, SORT THE VECTOR STRINGS, use at function to get the INDEX
	// for(long unsigned int i = 0; i < unordered_recipies.size(); i++){
	// 	int current_minimum = i;
	// 	for(long unsigned int j = i + 1; j < unordered_recipies.size(); j++){
	// 		if(cannidate_minimum_strings(unordered_recipies[j],unordered_recipies[current_minimum])){
	// 			current_minimum = j;
	// 		}
	// 	}
	// 	Recipie temp = unordered_recipies[i];
	// 	unordered_recipies[i] = unordered_recipies[current_minimum];
	// 	unordered_recipies[current_minimum] = temp;
	// }
}
//--------------------------------------------------------
void Recipie_Book::view_book(){
	cout << "Page Number:\tRecipie" << endl;
	for(auto& recipie: book){
		cout << recipie.first << ".)" << '\t' << recipie.second.title << endl;
	}
}
//--------------------------------------------------------
string minimum_strings(string string_one, string string_two){
	int smaller_string_size = string_one.size();
	string smaller_string = string_one;
	string larger_string = string_two;

	if(string_two.size() < string_one.size()){
		smaller_string_size = string_two.size();
		smaller_string = string_two;
		larger_string = string_one;
	}

	for(int i = 0; i < smaller_string_size; i++){
		if(larger_string[i] < smaller_string[i])
			return larger_string;
	}
	return smaller_string;
}
//--------------------------------------------------------
bool Recipie_Book::cannidate_minimum_strings(string string_one, string string_two){
	int string_one_size = string_one.size();

	for(int i = 0; i < string_one_size; i++){
		if(string_two[i] < string_one[i])
			return false;
	}
	return true;
}
//----------------------------------------------------------------------------------------------------
#endif

// void Recipie_Book::sort_string_vector(){																	
// 	for(long unsigned int i = 0; i < genre_list.size(); i++){
// 		int current_minimum = i;
// 		for(long unsigned int j = i + 1; j < genre_list.size(); j++){
// 			if(genre_list[j][0] < genre_list[current_minimum][0]){
// 				current_minimum = j;
// 			}
// 		}
// 		string temp = genre_list[i];
// 		genre_list[i] = genre_list[current_minimum];
// 		genre_list[current_minimum] = temp;
// 	}
// }