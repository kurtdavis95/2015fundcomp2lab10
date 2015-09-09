//Lab 10, Part 1	wordenum.cpp	4/7/15	Author: Kurt Davis

#include <iostream>
#include <cmath>
#include <set>
using namespace std;

int main(){
	long int valid_count = 0;

	//iterate through all possible strings
	int i, j, k, l, m, n, o;
	for(i = 0; i < 26; i++){
		for(j = 0; j < 26; j++){
			for(k = 0; k < 26; k++){
				//test for 3 letters in a row
				if((i == j) && (j == k) && (k == i)){
					continue;	//skip remaining downstream iterations if invalid
				}
				for(l = 0; l < 26; l++){
					if((j == k) && (k == l) && (l == j)){
						continue;
					}
					for(m = 0; m < 26; m++){
						if((k == l) && (l == m) && (m == k)){
							continue;
						}
						for(n = 0; n < 26; n++){
							if((l == m) && (m == n) && (n == l)){
								continue;
							}
							for(o = 0; o < 26; o++){
								if((m == n) && (n == o) && (o == m)){
									continue;
								}else{
									//name is valid, increment counter
									valid_count++;
								}
							}
						}				
					}
				}
			}
		}
	}	

	cout << "Total: " << valid_count << endl;
}
