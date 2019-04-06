#include<iostream>
#include<vector>
#include<cstring>
#include<vector>
#include<queue>
#include<fstream>
#include<locale>
#include<list>
#include<map>
#include<utility>
#include<iomanip>

using namespace std;

struct token{
	string term;
	int docID;
	friend bool operator> (const token t1,const token t2){
		return (t1.term>t2.term||(t1.term==t2.term&&t1.docID>t2.docID));
	}
	token(string term,int docID){this->term=term;this->docID=docID;}
};

struct tokenInfo{
	int times=0;
	list<int> idList;
	tokenInfo(int id){
		times = 1;
		idList.push_back(id);
	}
};

class invIndex{
private:
	vector<token> tokens;
	priority_queue<token,vector<token>,greater<token>> tqueue;
	map<string,tokenInfo> indexMap;
public:
	void addtokens(string term,int docID){
		token mytoken(term,docID);
		tokens.push_back(mytoken);
	}
	void addtomap(token mytoken){
		if(indexMap.find(mytoken.term)!=indexMap.end()){
			(*(indexMap.find(mytoken.term))).second.idList.push_back(mytoken.docID);
			(*(indexMap.find(mytoken.term))).second.times++;
		}
		else{
			tokenInfo tInfo(mytoken.docID);
			indexMap.insert(make_pair(mytoken.term,tInfo));
		}
	}
	void tqdisplay(){
		for(auto token:tokens){
			tqueue.push(token);
		}
		cout << left << setw(10) << "term";
		cout << left << setw(10) << "docID" << endl;
		cout << "----------------" << endl ;
		while(!tqueue.empty()){
			token temp = tqueue.top();
			cout << left << setw(10) << temp.term << temp.docID << endl;
			addtomap(temp);
			tqueue.pop();
		}
		cout << endl;
	}
	void display(){
		cout << left << setw(10) << "term"
			<< left << setw(10) << "doc.freq"
			<< left << "postings lists" << endl;
		cout << "------------------------------------" << endl ;
		for(auto tInfo:indexMap){
			cout << left << setw(10) << tInfo.first << left << setw(10) << tInfo.second.times << "[";
			for(auto it = tInfo.second.idList.begin();it!=tInfo.second.idList.end();it++){
				if(it!=tInfo.second.idList.begin()) cout << ",";
				cout << (*it);
			}
			cout << "]" << endl;
		}
	}

};
	
list<int> intersect(list<int> p1,list<int> p2){
	list<int> answer;
	list<int>::iterator itp1 = p1.begin();
	list<int>::iterator itp2 = p2.begin();
	while(itp1!=p1.end()&&itp2!=p2.end()){
		if(*itp1==*itp2){
			answer.push_back(*itp1);
			itp1++;
			itp2++;
		}else if(*itp1<*itp2){
			itp1++;
		}else{
			itp2++;
		}
	}
	return answer;
}

int main(int argc,char* argv[]){
	if(argc==1) cout << "No file input!" << endl;
	else{ // build the inverted index for the input files
		fstream fin;
		invIndex dic;
		for(int docID = 1 ;docID<argc;docID++){
			char* filename = argv[docID];
			fin.open(filename,ios::in); //read the files
			if(fin.is_open()){
				string term;
				locale loc;
				while(fin >> term){
					// for(auto word:term) tolower(term,loc); //turn the token to lower case
					dic.addtokens(term,docID); // add tokens to dic
				}
				fin.close();
			}else{
				cout << "File " << filename <<" is not open correctly!" << endl ;
			}
		}
		dic.tqdisplay();
		dic.display();
	}
	//intersect posting list
	list<int> p1 = {1,2,4,5,9,10};
	list<int> p2 = {2,3,5,6,10};
	for(auto docID:intersect(p1,p2)){
		cout << docID << " ";
	}
	cout << endl;
	return 0;
}
