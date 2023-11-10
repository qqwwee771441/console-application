#include <iostream>
#include <vector>

using namespace std;

int makeUp[101][10001];

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int n, k;
	cin>>n>>k;
	
	vector<int> coin(n);
	for(int i=0; i<n; i++) cin>>coin[i];
	
	for(int i=0; i<101; i++) makeUp[i][0] = 1;
	
	for(int i=1; i<=k; i++) {
		makeUp[0][i] = (i-coin[0]>=0) ? (makeUp[0][i-coin[0]]) : (0);
		for(int cur=1; cur<n; cur++) {
			makeUp[cur][i] = makeUp[cur-1][i];
			if(i-coin[cur] >= 0) makeUp[cur][i] += makeUp[cur][i-coin[cur]];
		}
	}
	
	for(int i=0; i<n; i++, cout<<"\n")
		for(int j=0; j<=k; j++)
			cout<<makeUp[i][j]<<" ";
	
	cout<<makeUp[n-1][k];
}

