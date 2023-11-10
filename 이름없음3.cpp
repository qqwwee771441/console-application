#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int get(int state, int index) {
	return (state >> (index*2)) & 3;
}
int set(int state, int index, int value) {
	return (state & ~(3 << (index*2))) | (value << (index*2));
}
int increment(int value) {
	return (value<0) ? (value-1) : (value+1);
}

int C[1<<(12*2)];

int bfs(int n, int start, int end) {
	queue<int> Q;
	Q.push(start);
	Q.push(end);
	memset(C, 0, sizeof(C));
	C[start] = 1;
	C[end] = -1;
	for(int here; !Q.empty(); Q.pop()) {
		here = Q.front();
		int top[4] = { 100, 100, 100, 100 };
		for(int i=n; i>=1; i--) top[get(here, i)] = i;
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				if(i!=j && top[j]>top[i]) {
					int there = set(here, top[i], j);
					if(C[there] == 0) {
						C[there] = increment(C[here]);
						Q.push(there);
					} else if(C[here]*C[there] < 0) {
						return abs(C[here]) + abs(C[there]) - 1;
					}
				}
	}
	return -1;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int C;
	cin>>C;
	while(C--) {
		int n;
		cin>>n;
		
		int start = 0;
		for(int i=0; i<4; i++) {
			int numOfDisk;
			cin>>numOfDisk;
			for(int j=0; j<numOfDisk; j++) {
				int disk;
				cin>>disk;
				start = set(start, disk, i);
			}
		}
		
		int end = 0;
		for(int i=0; i<4; i++) {
			int numOfDisk;
			cin>>numOfDisk;
			for(int j=0; j<numOfDisk; j++) {
				int disk;
				cin>>disk;
				end = set(end, disk, i);
			}
		}
		
		cout<<bfs(n, start, end)<<"\n";
	}
}
/*
3
5
1 1
1 3
2 5 4
1 2
0 0 0
5 5 4 3 2 1
3
1 2
0
2 3 1
0
0
0
0
3 3 2 1
10
2 8 7
2 5 4
3 6 3 2
3 10 9 1
0
0
0
10 10 9 8 7 6 5 4 3 2 1

1
3
1 2
0
2 3 1
0
0
0
0
3 3 2 1
*/

