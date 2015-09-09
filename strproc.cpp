//Lab 10, Post-lab	strproc.cpp	4/13/15	Author: Kurt Davis

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char *argv[]){
	
	vector<string> filedata1;
	vector<string> filedata2;

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

	//set<string> intersectiondata;
	//set<string> uniondata;

	int i;
	int first = 1;
	int strpos;
	int htmlfile = 0;
	string linein;
	string processed_word;
	
	//read in file 1
	while(!datafile1.eof()){
		processed_word.clear();		//reset processed string
		wordin.clear();
		datafile1 >> wordin;		//read line		

		//check if file is html
		if(first){
			if(wordin.find("<html>") != string::npos){
				//file is html
				htmlfile = 1;
				cout << "File is HTML." << endl;
			}
		}
		first = 0;



		if(!htmlfile){	//not html, regular string input
			//remove non-alphanumeric characters
			for(i = 0 ; i < wordin.size(); i++){
				if(isalnum(wordin[i])){
					processed_word += tolower(wordin[i]);	//concatenate valid chars to make new string
				}
			}

			//add word to list
			filedata1.push_back(processed_word);


		}else{		//file is html, special string input
			//if(wordin.find("<") != npos){
			//	strpos = wordin.find("a href=");
			//	if(strpos != npos){		//target tag, get string
					
			//	}else{		//regular tag, ignore
					
			//	}

			//}
		}
	}	

	//read in file 2
	/*	
	while(!datafile2.eof()){
		processed_word.clear();		//reset processed string
		datafile2 >> wordin;		//read line		

		//remove non-alphanumeric characters
		for(i = 0 < wordin.size(); i++){
			if(isalnum(wordin[i])){
				processed_string += tolower(wordin[i]);	//concatenate valid chars to make new string
			}
		}

		//add word to list
		if(processed_word.size() != 0){
			filedata2.push_back(processed_word);
		}
	}
	*/
	
	//close files
	datafile1.close();
	datafile2.close();

	vector<string>::const_iterator it;
	for(it = filedata1.begin(); it != filedata1.end(); ++it){
		cout << *it << endl;
	}

	//process strings

	//calculate Jaccard Similarity
	//set_intersection(filedata1.begin(), filedata1.end(), filedata2.begin(), filedata2.end(), inserter(intersectiondata, intersectiondata.end()));

	//set_union(filedata1.begin(), filedata1.end(), filedata2.begin(), filedata2.end(), inserter(uniondata, uniondata.end()));

	return 0;
}