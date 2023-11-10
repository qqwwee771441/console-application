#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum { U, R, D, L };

struct Tuple {
	int h, d, y, x;
	Tuple(int h, int d, int y, int x) : h(h), d(d), y(y), x(x) { }
	bool operator<(const Tuple& comp) const { return h>comp.h; }
};

int totalVolume(int N, int M, int H, vector< vector<int> >& horizontal, vector< vector<int> >& vertical) {
	vector< vector<int> > waterTank(N+2, vector<int>(M+2, 0));
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) waterTank[i][j] = H;
	priority_queue<Tuple> Q;
	for(int i=1; i<=M; i++) {
		if(horizontal[1][i] != -1) Q.push(Tuple(horizontal[1][i], D, 0, i));
		if(horizontal[N+1][i] != -1) Q.push(Tuple(horizontal[N+1][i], U, N+1, i));
	}
	for(int i=1; i<=N; i++) {
		if(vertical[i][1] != -1) Q.push(Tuple(vertical[i][1], R, i, 0));
		if(vertical[i][M+1] != -1) Q.push(Tuple(vertical[i][M+1], L, i, M+1));
	}
	for(int h, d, y, x; !Q.empty(); Q.pop()) {
		h = Q.top().h;
		d = Q.top().d;
		y = Q.top().y;
		x = Q.top().x;
		switch(d) {
		case U:
			if(horizontal[y][x]!=-1 && waterTank[y-1][x]==H) {
				waterTank[y-1][x] = h;
				Q.push(Tuple(max(waterTank[y-1][x], horizontal[y-1][x]), U, y-1, x));
				Q.push(Tuple(max(waterTank[y-1][x], vertical[y-1][x]), L, y-1, x));
				Q.push(Tuple(max(waterTank[y-1][x], vertical[y-1][x+1]), R, y-1, x));
			}
			break;
		case R:
			if(vertical[y][x+1]!=-1 && waterTank[y][x+1]==H) {
				waterTank[y][x+1] = h;
				Q.push(Tuple(max(waterTank[y][x+1], horizontal[y][x+1]), U, y, x+1));
				Q.push(Tuple(max(waterTank[y][x+1], vertical[y][x+2]), R, y, x+1));
				Q.push(Tuple(max(waterTank[y][x+1], horizontal[y+1][x+1]), D, y, x+1));
			}
			break;
		case D:
			if(horizontal[y+1][x]!=-1 && waterTank[y+1][x]==H) {
				waterTank[y+1][x] = h;
				Q.push(Tuple(max(waterTank[y+1][x], vertical[y+1][x+1]), R, y+1, x));
				Q.push(Tuple(max(waterTank[y+1][x], horizontal[y+2][x]), D, y+1, x));
				Q.push(Tuple(max(waterTank[y+1][x], vertical[y+1][x]), L, y+1, x));
			}
			break;
		case L:
			if(vertical[y][x]!=-1 && waterTank[y][x-1]==H) {
				waterTank[y][x-1] = h;
				Q.push(Tuple(max(waterTank[y][x-1], horizontal[y][x-1]), U, y, x-1));
				Q.push(Tuple(max(waterTank[y][x-1], horizontal[y+1][x-1]), D, y, x-1));
				Q.push(Tuple(max(waterTank[y][x-1], vertical[y][x-1]), L, y, x-1));
			}
			break;
		}
	}
	int total = 0;
	for(int i=1; i<=N; i++)
		for(int j=1; j<=M; j++)
			total += waterTank[i][j];
	return total;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int N, M, H;
	cin>>N>>M>>H;
	
	vector< vector<int> > horizontal(N+3, vector<int>(M+2, -1));
	for(int i=1; i<=N+1; i++)
		for(int j=1, hole; j<=M; j++) {
			cin>>hole;
			horizontal[i][j] = hole;
		}
	
	vector< vector<int> > vertical(N+2, vector<int>(M+3, -1));
	for(int i=1; i<=N; i++)
		for(int j=1, hole; j<=M+1; j++) {
			cin>>hole;
			vertical[i][j] = hole;
		}
	
	cout<<totalVolume(N, M, H, horizontal, vertical);
}

