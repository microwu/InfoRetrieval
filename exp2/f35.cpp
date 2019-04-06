#include<iostream>
#include<string>

int min(int a,int b,int c){
	return a<b?a:b<c?b:c;
}

int** EditDistance(std::string s1,std::string s2){
	int ii=s1.size();
	int jj=s2.size();
	int** m;
	m = (int**)malloc(sizeof(int)*(jj+1)*(ii+1));
	for(int i=0;i<=ii;i++){
		m[i] = (int*)malloc(sizeof(int)*(jj+1));
	}
	for(int i=1;i<=ii;i++){
		m[i][0]=0;
	}
	for(int i=1;i<=jj;i++){
		m[0][i]=0;
	}
	for(int i=1;i<=ii;i++){
		for(int j=1;j<=jj;j++){
			m[i][j] = min(m[i-1][j-1]+(s1[i]==s2[j]?0:1),m[i-1][j]+1,m[i][j-1]+1);
		}
	}
	return m;
}

int main(){
	std::string s1;
	std::string s2;
	std::cin >> s1;
	std::cin >> s2;
	std::cout << EditDistance(s1,s2)[s1.size()-1][s2.size()-1] <<std::endl;
	return 0;
}
