#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string s, std::vector<char> unnecessary) {
	// split the input line to terms
	std::string::size_type pos1, pos2;
	std::vector<std::string> v;
	pos2 = s.find(unnecessary[0]);
	for (auto c : unnecessary) {
		// std::cout << c << ":" << s.find(c) << std::endl;
		if (s.find(c) < pos2 && s.find(c) != std::string::npos) {
			pos2 = s.find(c);
			std::cout << pos2 << std::endl;
		}
	}
	pos1 = 0;
	while (std::string::npos != pos2) {
		if (pos1 == pos2) {
			// std::cout << pos2 << std::endl;
			pos1 = pos2 + 1;
			pos2 = s.find(unnecessary[0], pos1);
			for (auto c : unnecessary) {
				if (s.find(c, pos1) < pos2 &&
					(s.find(c, pos1) != std::string::npos)) {
					pos2 = s.find(c, pos1);
				}
			}
			continue;
		}
		// std::cout << (s.substr(pos1,pos2-pos1))<< " " << pos1 << " " << pos2
		// << std::endl;
		v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
		// pos2 = std::string::npos;
		pos2 = s.find(unnecessary[0], pos1);
		for (auto c : unnecessary) {
			// std::cout << c << ":" << s.find(c,pos1) << std::endl;
			if (s.find(c, pos1) < pos2 &&
				(s.find(c, pos1) != std::string::npos)) {
				pos2 = s.find(c, pos1);
			}
		}
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
	return v;
}

class TokenCounter {
  private:
	unsigned tokenNum;
	unsigned termNum;
	std::set<std::string> tokens;
	std::vector<std::string> terms;

  public:
	TokenCounter();
	TokenCounter(std::string fn);
	void display();
	void cleanStopWords(std::set<std::string> rule);
};

TokenCounter::TokenCounter() {
	tokenNum = 0;
	termNum = 0;
}

TokenCounter::TokenCounter(std::string fn) {
	//tokenNum and termNum initial
	tokenNum = 0;
	termNum = 0;
	// get the file line by line
	std::string line;
	std::ifstream myfile;
	myfile.open(fn);
	std::vector<char> unnecessary = {' '};
	int linenum = 0;
	while (std::getline(myfile, line)) {
		std::istringstream iss(line);
		// split the words into terms
		std::vector<std::string> lineterms =
			split(line, unnecessary);
		for (auto term : lineterms) {
			// add them to the tokens and terms
			// std::cout << term << std::endl;
			if(tokens.find(term)==tokens.end()){// can't find this token in tokens
				tokens.insert(term);
				tokenNum++;
			}
			termNum++;
			// terms.push_back(term);
		}
		linenum++;
	}
	// tokenNum = tokens.size();
	// termNum = terms.size();
}

void TokenCounter::cleanStopWords(std::set<std::string> rules) {
	// if the terms is in the stop words rules, remove it from tokens and terms
	auto it = terms.begin();
	while (it != terms.end()) {
		if (rules.find(*it) != rules.end())
			terms.erase(it);
		it++;
	}
	for(auto rule:rules){
		auto exist = tokens.find(rule);
		if(exist!=tokens.end()){
			tokens.erase(exist);
		}
	}
	tokenNum = tokens.size();
	termNum = terms.size();
}

void TokenCounter::display() {
	std::cout << "tokenNum:" << tokenNum << " termNum:" << termNum << std::endl;
}

int main() {

	// token counter for the whole abstract
	TokenCounter *tc1=new TokenCounter("./AMiner-Paper-Abs.txt");
	tc1->display();
	delete tc1;
	// token counter for the abstract without stop words
	TokenCounter *tc2=new TokenCounter("./AMiner-Paper-Abs-Stop.txt");
	tc2->display();
	delete tc2;
	// token counter for the filtered abstract that handled with porter stemmer
	TokenCounter *tc3=new TokenCounter("./AMiner-Paper-Stop-PS.txt");
	tc3->display();
	delete tc3;

	return 0;
}
