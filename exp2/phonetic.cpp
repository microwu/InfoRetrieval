#include<iostream>
#include<string>

int main(){
	std::string ipstring;
	std::cin >> ipstring;
	auto it = ipstring.begin();
	it++;
	while(it!=ipstring.end()){
		switch(*it){
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
			case 'h':
			case 'w':
			case 'y':
				*it='0';
				it++;
				break;
			case 'b':
			case 'f':
			case 'p':
			case 'v':
				*it='1';
				it++;
				break;
			case 'c':
			case 'g':
			case 'j':
			case 'k':
			case 'q':
			case 's':
			case 'x':
			case 'z':
				*it='2';
				it++;
				break;
			case 'd':
			case 't':
				*it='3';
				it++;
				break;
			case 'l':
				*it='4';
				it++;
				break;
			case 'm':
			case 'n':
				*it='5';
				it++;
				break;
			case 'r':
				*it='6';
				it++;
				break;
		}
	}
	it = ipstring.begin();
	it++;
	while(it!=ipstring.end()){
		if(*it==*(it-1)){ipstring.erase(it);continue;}
		it++;
	}
	it = ipstring.begin();
	it++;
	while(it!=ipstring.end()){
		if(*it=='0'){ipstring.erase(it);continue;}
		it++;
	}
	std::cout << ipstring << std::endl;
	return 0;
}
