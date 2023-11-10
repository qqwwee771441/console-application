#include <cstdio>
#include <vector>

void init( int N, int M, std::vector<int> Y1, std::vector<int> Y2 );
long long minimize( int A, int B );

int main() {
	int N, M, Q;
	std::vector<int> Y1(3000), Y2(3000);
	int A, B;
	
	scanf("%d %d %d", &N, &M, &Q);
	
	for(int i=0, y1, y2; i<N; i++) {
		scanf("%d %d", &y1, &y2);
		Y1.push_back(y1);
		Y2.push_back(y2);
	}
	init(N, M, Y1, Y2);
	
	for(int i=0; i<Q; i++) {
		scanf("%d %d", &A, &B);
		printf("%d\n", minimize(A, B));
	}
}

// int tunnel[10000][1000000000];
// int membrane;

void init( int N, int M, std::vector<int> Y1, std::vector<int> Y2 ) {
	
}

long long minimize( int A, int B ) {
	
}

