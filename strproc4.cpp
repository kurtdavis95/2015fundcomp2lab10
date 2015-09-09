//Lab 10, Post-lab	strproc.cpp	4/13/15	Author: Kurt Davis
//Program to calculate Jaccard similarity for text files and html files

//Note on string parsing: My implementation uses spaces (or tags as well in html) exclusively as word delimiters.
//So, for instance, if a file contained "word.Here", that string would be read in as "wordhere", while "word. Here" would
//be "word" and "here".

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]){
	
	int i;
	int tag;	//flag, true: currently inside <>
	int wordpresent;
	int htmlfile = 0;
	int file1_ishtml = 0;
	int file2_ishtml = 0;
	string linein;
	string processed_word;

	multiset<string> filedata1;
	multiset<string> filedata2;
	
	set<string> unique_words1;
	set<string> unique_words2;

	map<string, int> wordcount1;
	map<string, int> wordcount2;

	//to hold a href tags for each file
	set<string> tag1;
	set<string> tag2;

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

	//********* FILE INPUT *********

	//Program reads files one line at a time, then parses lines one character at a time.

	//test first line/process first line
	getline(datafile1, linein);
	if((linein.find("<html>") == string::npos) && (linein.find("<!DOCTYPE html>") == string::npos)){
		//html tag not found	
		for(i = 0; i < linein.size(); i++){	//break line into words, add words to set
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
		//cout << "Plaintext file." << endl;
	}else{
		//html tag found
		/*This assumes that the first line has ONLY the <html> tag or the <!DOCTYPE html>
		with this assumption, there are no words to add from the first line*/
		//cout << "HTML file." << endl;
		htmlfile = 1;
		file1_ishtml = 1;
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
				//cout << "Target tag not found." << endl;				
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
				//extract address from tag, continue breaking line into words outside of tags
				//cout << "Target tag found." << endl;
				int pos = linein.find("<a href=") + 9;				
				int j = pos;
				string tagcontents;				
				while(linein[j] != '"'){
					tagcontents += linein[j];
					j++;
				}
				
				//cout << tagcontents << endl;
				tag1.insert(tagcontents);
				j++;				

				while(linein[j] != '>'){
					j++;
				}

				j++;

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
			}
			processed_word.clear();
		}
	}		

	
	htmlfile = 0;	//reset flag between files


	//----------Repeat for 2nd file----------


	//test first line/process first line
	getline(datafile2, linein);
	if((linein.find("<html>") == string::npos) && (linein.find("<!DOCTYPE html>") == string::npos)){
		//html tag not found	
		for(i = 0; i < linein.size(); i++){
			if(!(isspace(linein[i]))){
				if(isalnum(linein[i])){
					processed_word += tolower(linein[i]);
				}
			}else{
				filedata2.insert(processed_word);
				processed_word.clear();
			}
		}
		filedata2.insert(processed_word);
		processed_word.clear();
		//cout << "Plaintext file." << endl;
	}else{
		//html tag found
		/*This assumes that the first line has ONLY the <html> tag or the <!DOCTYPE html>
		with this assumption, there are no words to add from the first line*/
		//cout << "HTML file." << endl;
		htmlfile = 1;
		file2_ishtml = 1;
	}
	
	if(!htmlfile){
		//read regular file
		while(!datafile2.eof()){
			linein.clear();
			getline(datafile2, linein);
			for(i = 0; i < linein.size(); i++){
				if(!(isspace(linein[i]))){
					if(isalnum(linein[i])){
						processed_word += tolower(linein[i]);
					}
				}else{
					filedata2.insert(processed_word);
					processed_word.clear();
				}
			}
			filedata2.insert(processed_word);
			processed_word.clear();
		}
	
		//filedata2.pop_back();

	}else{
		//read html file
		while(!datafile2.eof()){
			linein.clear();
			getline(datafile2, linein);
			
			if(linein.find("<a href=") == string::npos){	//target tag not found				
				//cout << "Target tag not found." << endl;				
				tag = 0;				
				for(i = 0; i < linein.size(); i++){
					if(!tag){
						if(linein[i] == '<'){	//tag started
							tag = 1;	
							if(!processed_word.size() != 0){	//empty current word to vector
								filedata2.insert(processed_word);
								processed_word.clear();
							}
						}else{			//outside tag, process normally
							if(!(isspace(linein[i]))){
								if(isalnum(linein[i])){
									processed_word += tolower(linein[i]);
								}
							}else{
								filedata2.insert(processed_word);
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
				filedata2.insert(processed_word);
				processed_word.clear();

			}else{		//target tag found
				//cout << "Target tag found." << endl;
				int pos = linein.find("<a href=") + 9;				
				int j = pos;
				string tagcontents;				
				while(linein[j] != '"'){
					tagcontents += linein[j];
					j++;
				}
				
				//cout << tagcontents << endl;
				tag2.insert(tagcontents);
				j++;				

				while(linein[j] != '>'){
					j++;
				}

				j++;

				tag = 0;				
				for(i = 0; i < linein.size(); i++){
					if(!tag){
						if(linein[i] == '<'){	//tag started
							tag = 1;	
							if(!processed_word.size() != 0){	//empty current word to vector
								filedata2.insert(processed_word);
								processed_word.clear();
							}
						}else{			//outside tag, process normally
							if(!(isspace(linein[i]))){
								if(isalnum(linein[i])){
									processed_word += tolower(linein[i]);
								}
							}else{
								filedata2.insert(processed_word);
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
				filedata2.insert(processed_word);
				processed_word.clear();
			}
			processed_word.clear();
		}
	}		

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
	//for(it = filedata1.begin(); it != filedata1.end(); ++it){	
	//	cout << *it << endl;
	//}

	set<string>::const_iterator it2;
	
	if(file1_ishtml){
		cout << "Unique a href links in file " << argv[1] << " : " << endl;
		//print contents of tag1
		for(it2 = tag1.begin(); it2 != tag1.end(); ++it2){	
			cout << *it2 << endl;
		}
	}

	cout << endl; 
	
	
	
	//remove empty strings
	for(it = filedata2.begin(); it != filedata2.end(); ++it){	
		if(!isalnum((*it)[0])){
			filedata2.erase(it);
		}
	}
	
	//print strings
	//for(it = filedata2.begin(); it != filedata2.end(); ++it){	
	//	cout << *it << endl;
	//}

	if(file2_ishtml){
		cout << "Unique a href links in file " << argv[2] << " : " << endl;
		//print contents of tag2
		for(it2 = tag2.begin(); it2 != tag2.end(); ++it2){	
			cout << *it2 << endl;
		}
	}
	
	//********* END FILE INPUT *********
	//At this point, all of the strings and tag contents are in their appropriate data structures.

	//********* DATA PROCESSING *********

	//create sets of unique words for each file
	for(it = filedata1.begin(); it != filedata1.end(); ++it){	
		unique_words1.insert(*it);
	}

	for(it = filedata2.begin(); it != filedata2.end(); ++it){	
		unique_words2.insert(*it);
	}
	
	
	map<string, int>::iterator it3;	

	//create maps of word counts for each file
	for(it = filedata1.begin(); it != filedata1.end(); ++it){	
		wordpresent = wordcount1.count((*it));	//search for next word in count map
				
		if(wordpresent == 0){	//word not found, create new map element
			wordcount1.insert(pair<string, int>( (*it), 1) );
		}else{			//word found, increment counter
			wordcount1[(*it)]++;
		}
	}

	//map for file 2
	for(it = filedata2.begin(); it != filedata2.end(); ++it){	
		wordpresent = wordcount2.count((*it));	//search for next word in count map
				
		if(wordpresent = 0){	//word not found, create new map element
			wordcount2.insert(pair<string, int>( (*it), 1) );
		}else{			//word found, increment counter
			wordcount2[(*it)]++;
		}
	}

	for(it3 = wordcount1.begin(); it3 != wordcount1.end(); ++it3){
		cout << it3->first << " " << it3->second << endl;
	}
	
	

	//********* OUTPUT TO USER *********
	//total word count in each file
	cout << endl;
	cout << "Total word count of file " << argv[1] << " : " << filedata1.size() << endl;
	cout << "Total word count of file " << argv[2] << " : " << filedata2.size() << endl;

	//unique words in file 1
	cout << "Unique words in file " << argv[1] << " : " << unique_words1.size() << endl;

	//calculate Jaccard similarity
	set<string>::iterator in;	//intersection
	set<string>::iterator un;	//union

	set<string> inResult;
	set<string> unResult;

	set_intersection( unique_words1.begin(), unique_words1.end(), unique_words2.begin(), unique_words2.end(), inserter(inResult, inResult.end()));
	set_union( unique_words1.begin(), unique_words1.end(), unique_words2.begin(), unique_words2.end(), inserter(unResult, unResult.end()));

	//inResult.resize(in-inResult.begin());
	//unResult.resize(un-unResult.begin());

	double result = (double)inResult.size() / (double)unResult.size();
	
	cout << "Jaccard similarity = " << result << endl;

	return 0;
}

