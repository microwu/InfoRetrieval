#include<iostream>
#include<list>
#include<iterator>
#include<algorithm>

std::list<std::pair<int,int>> intersectWithSkips(std::list<std::pair<int,int>> p1,std::list<std::pair<int,int>> p2){
	std::list<std::pair<int,int>> answer;
	auto it1 = p1.begin();
	auto it2 = p2.begin();
	while(it1!=p1.end()&&it2!=p2.end()){
		if((*it1).first==(*it2).first){//if idDoc(p1)=idDoc(p2)  then ADD(p1,answer)
			answer.push_back(*it1);
			it1++;
			it2++;
		}else if ((*it1).first<(*it2).first){
			int skip1 = (*it1).second;
			auto skip1to = p1.begin();
			std::advance(skip1to,skip1);//skip1to += skip1
			if(skip1>0&&((*skip1to).first<(*it2).first||(*skip1to).first==(*it2).first)){
				while(skip1>0&&((*skip1to).first<(*it2).first||(*skip1to).first==(*it2).first)){
					it1=skip1to;
					skip1=(*it1).second;
					skip1to=p1.begin();
					std::advance(skip1to,skip1);
				}
			}else
				it1++;
		}else{ 
			int skip2 = (*it2).second;
			auto skip2to = p2.begin();
			std::advance(skip2to,skip2);//skip2to += skip2
			if(skip2>0&&((*skip2to).first<(*it1).first||(*skip2to).first==(*it1).first)){
				while(skip2>0&&((*skip2to).first<(*it1).first||(*skip2to).first==(*it1).first)){
					it2=skip2to;
					skip2=(*it2).second;
					skip2to=p1.begin();
					std::advance(skip2to,skip2);
				}
			}else
				it2++;
		}
	}
	return answer;
}

int main(){
	std::list<std::pair<int,int>> jpl1;
	std::list<std::pair<int,int>> jpl2;
	jpl1={std::make_pair(3,3),std::make_pair(5,0),std::make_pair(9,0),std::make_pair(24,7),std::make_pair(39,0),std::make_pair(60,0),std::make_pair(68,0),std::make_pair(75,11),std::make_pair(81,0),std::make_pair(84,0),std::make_pair(89,0),std::make_pair(92,0)};
	jpl2={std::make_pair(3,3),std::make_pair(4,0),std::make_pair(6,0),std::make_pair(8,7),std::make_pair(11,0),std::make_pair(23,0),std::make_pair(24,0),std::make_pair(26,11),std::make_pair(29,0),std::make_pair(40,0),std::make_pair(50,0),std::make_pair(89,0)};
	std::list<std::pair<int,int>> answer = intersectWithSkips(jpl1,jpl2);

	std::cout << "p1: " ;
	for(auto num:jpl1){
		std::cout << num.first << " ";
	}
	std::cout << std::endl;

	std::cout << "p2: ";
	for(auto num:jpl2){
		std::cout << num.first << " ";
	}
	std::cout << std::endl;


	std::cout << "answer: ";
	for(auto num:answer){
		std::cout << num.first << " ";
	}
	std::cout << std::endl;
	return 0;
}

