#include<iostream>
#include<map>
#include<tuple>
#include<list>
#include<vector>

std::list<std::tuple<int,int,int>> PosIntersect(std::list<std::pair<int,std::list<int>>> p1,std::list<std::pair<int,std::list<int>>> p2,int k){
	std::list<std::tuple<int,int,int>> answer;
	auto it1 = p1.begin();
	auto it2 = p2.begin();
	while(it1!=p1.end()&&it2!=p2.end()){
		if((*it1).first==(*it2).first){//two tearms are in same doc
			std::vector<int> l;
			std::list<int> pp1 = (*it1).second;
			std::list<int> pp2 = (*it2).second;
			auto iit1 = pp1.begin();
			auto iit2 = pp2.begin();
			while(iit1!=pp1.end()){
				while(iit2!=pp2.end()){
					if(std::abs(*iit1-*iit2)<=k){
						l.push_back(*iit2);
					}else if(*iit2>*iit1)
						break;
					iit2++;
				}
				while(!l.empty()&&std::abs(l.front()-*iit1)>k)
					l.pop_back();
				for(auto ps:l){
					answer.push_back(std::make_tuple((*it1).first,*iit1,ps));
					iit1++;
				}
				iit1++;
			}
			it1++;
			it2++;
		}else if((*it1).first<(*it2).first){
			it1++;
		}else
			it2++;
		
	}
	return answer;
}

int main(){
	std::list<std::pair<int,std::list<int>>> p1;
	std::list<std::pair<int,std::list<int>>> p2;
	p1.push_back(std::make_pair(1,(std::list<int>){7,18,33,72,86,231}));
	p1.push_back(std::make_pair(2,(std::list<int>){1,17,74,222,255}));
	p1.push_back(std::make_pair(4,(std::list<int>){8,16,190,429,433}));
	p1.push_back(std::make_pair(5,(std::list<int>){363,367}));
	p1.push_back(std::make_pair(7,(std::list<int>){13,23,191}));
	

	p2.push_back(std::make_pair(1,(std::list<int>){17,25}));
	p2.push_back(std::make_pair(4,(std::list<int>){17,191,291,430,434}));
	p2.push_back(std::make_pair(5,(std::list<int>){14,19,101}));

	std::cout << "p1:" << std::endl ;
	for(auto pl:p1){
		std::cout << pl.first << ":<";
		for(auto it=pl.second.begin();it!=pl.second.end();it++){
			if(it!=pl.second.begin()){
				std::cout<<",";
			}
			std::cout<<*it;
		}
		std::cout << ">" <<std::endl;
	}
	std::cout << "p2:" << std::endl ;
	for(auto pl:p2){
		std::cout << pl.first << ":<";
		for(auto it=pl.second.begin();it!=pl.second.end();it++){
			if(it!=pl.second.begin()){
				std::cout<<",";
			}
			std::cout<<*it;
		}
		std::cout << ">" <<std::endl;
	}

	std::list<std::tuple<int,int,int>> answer = PosIntersect(p1,p2,1);
	std::cout << "answer:" <<std::endl;
	for(auto ans:answer){
		int docID,pos,ps;
		std::tie(docID,pos,ps) = ans;
		std::cout << docID << "," << pos << "," << ps << std::endl;
	}
	return 0;
}
