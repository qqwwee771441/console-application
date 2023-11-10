#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

enum { _GB, R_B, RG_ };

struct Tuple {
	int R, G, B;
	Tuple(int r, int g, int b) : R(r), G(g), B(b) { }
	Tuple() { Tuple(0, 0, 0); }
};

int cache[1000];

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int N;
	cin>>N;
	
	vector<Tuple> house(N);
	for(int i=0; i<N; i++) cin>>house[i].R>>house[i].G>>house[i].B;
	
	paint(house, 1, );
	paint(house, 1, );
	paint(house, 1, );
}

