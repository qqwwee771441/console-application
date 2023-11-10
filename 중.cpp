#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int k;
string str[16];

int cache[16][1<<16];

int connect(int left, int right) {
	int sum = str[left].length() + str[right].length();
	int ret = sum;
	for(int i=1, len=str[left].length(); i<=len; i++)
		if(str[left].substr(len-i, i) == str[right].substr(0, i))
			ret = sum - i*2;
	return ret;
}

int restore(int front, int visited) {
	int& ret = cache[front][visited];
	if(ret != -1) return ret;
	
	for(int i=1; i<=k; i++) {
		if(visited & (1<<i)) continue;
		if(ret == -1) ret = connect(front, i) + restore(i, visited + (1<<i));
		else ret = min(ret, connect(front, i) + restore(i, visited + (1<<i)));
	}
	if(ret == -1) ret = 0;
	cout<<"tap "<<front<<" "<<ret<<"\n";
	return ret;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int C;
	cin>>C;
	while(C--) {
		cin>>k;
		str[0] = ""; for(int i=1; i<=k; i++) cin>>str[i];
		memset(cache, -1, sizeof(cache));
		cout<<restore(0, 1)<<"\n";
	}
}
/*
3
3
geo
oji
jing
2
world
hello
3
abrac
cadabra
dabr
*/

