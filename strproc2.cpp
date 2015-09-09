//Lab 10, Post-lab	strproc.cpp	4/13/15	Author: Kurt Davis

#include <iostream>
#include <fstream>
#include <string>
//#include <cctype>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]){
	
	int i;
	int tag;	//flag, true: currently inside <>
	int htmlfile = 0;
	string linein;
	string processed_word;

	multiset<string> filedata1;
	multiset<string> filedata2;
	
	//to hold a href tags for each file
	multiset<string> tag1;
	multiset<string> tag2;

	//check for valid arguments
	if(argc != 3){
		cout << "Invalid use. Program requires exactly 2 arguments." << endl;
		return 3;
	}

	//open file 1
	ifstream datafile1(argv[1]);
	if(!datafile1.is_open()){
		cout << "Error: File " << argv[1] << " failed to open." << endl;
		return 1;	
	}
	//open file 2
	ifstream datafile2(argv[2]);
	if(!datafile1.is_open()){
		cout << "Error: File " << argv[2] << " failed to open." << endl;	
		return 2;	
	}

	//test first line/process first line
	getline(datafile1, linein);
	if((linein.find("<html>") == string::npos) && (linein.find("<!DOCTYPE html>") == string::npos)){
		//html tag not found	
		for(i = 0; i < linein.size(); i++){
			if(!(isspace(linein[i]))){
				if(isalnum(linein[i])){
					processed_word += tolower(linein[i]);
				}
			}else{
				filedata1.insert(processed_word);
				processed_word.clear();
			}
		}
		filedata1.insert(processed_word);
		processed_word.clear();
		cout << "Plaintext file." << endl;
	}else{
		//html tag found
		/*This assumes that the first line has ONLY the <html> tag or the <!DOCTYPE html>
		with this assumption, there are no words to add from the first line*/
		cout << "HTML file." << endl;
		htmlfile = 1;
	}
	
	if(!htmlfile){
		//read regular file
		while(!datafile1.eof()){
			linein.clear();
			getline(datafile1, linein);
			for(i = 0; i < linein.size(); i++){
				if(!(isspace(linein[i]))){
					if(isalnum(linein[i])){
						processed_word += tolower(linein[i]);
					}
				}else{
					filedata1.insert(processed_word);
					processed_word.clear();
				}
			}
			filedata1.insert(processed_word);
			processed_word.clear();
		}
	
		//filedata1.pop_back();

	}else{
		//read html file
		while(!datafile1.eof()){
			linein.clear();
			getline(datafile1, linein);
			
			if(linein.find("<a href=") == string::npos){	//target tag not found				
				cout << "Target tag not found." << endl;				
				tag = 0;				
				for(i = 0; i < linein.size(); i++){
					if(!tag){
						if(linein[i] == '<'){	//tag started
							tag = 1;	
							if(!processed_word.size() != 0){	//empty current word to vector
								filedata1.insert(processed_word);
								processed_word.clear();
							}
						}else{			//outside tag, process normally
							if(!(isspace(linein[i]))){
								if(isalnum(linein[i])){
									processed_word += tolower(linein[i]);
								}
							}else{
								filedata1.insert(processed_word);
								processed_word.clear();
							}
						}
					}else{
						if(linein[i] == '>'){	//tag ended
							tag = 0;
							//processed_word.clear();
						}
					}
				}
				filedata1.insert(processed_word);
				processed_word.clear();

			}else{		//target tag found
				cout << "Target tag found." << endl;
			}
			processed_word.clear();
		}
	}	

	htmlfile = 0;	//reset flag between files

	//close files
	datafile1.close();
	datafile2.close();

	multiset<string>::const_iterator it;
	//remove empty strings
	for(it = filedata1.begin(); it != filedata1.end(); ++it){	
		if(!isalnum((*it)[0])){
			filedata1.erase(it);
		}
	}

	//print strings
	for(it = filedata1.begin(); it != filedata1.end(); ++it){	
		cout << *it << endl;
	}


	return 0;
}
