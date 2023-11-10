#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int m, q;
string word[500];
double B[500];
double T[500][500];
double M[500][500];
int n; int R[100];

double cache[100][500];
int choice[100][500];

double ocr(int idx, int prev) {
	if(idx == n) return 1.0;
	
	double& ret = cache[idx][prev];
	if(ret >= 0.0) return ret;
	
	ret = 0.0;
	if(idx == 0) {
		for(int i=0; i<m; i++) {
			double prob = M[i][R[idx]]*B[i]*ocr(idx+1, i);
			if(prob > ret) {
				ret = prob;
				choice[idx][prev] = i;
			}
		}
	}
	else {
		for(int i=0; i<m; i++) {
			double prob = M[i][R[idx]]*T[prev][i]*ocr(idx+1, i);
			if(prob > ret) {
				ret = prob;
				choice[idx][prev] = i;
			}
		}
	}
	return ret;
}

string reconstruct(int idx, int prev) {
	int choose = choice[idx][prev];
	string ret = word[choose];
	if(idx < n-1) ret = ret + " " + reconstruct(idx+1, choose);
	return ret;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin>>m>>q;	
	for(int i=0; i<m; i++) cin>>word[i];
	for(int i=0; i<m; i++) cin>>B[i];
	for(int i=0; i<m; i++) for(int j=0; j<m; j++) cin>>T[i][j];
	for(int i=0; i<m; i++) for(int j=0; j<m; j++) cin>>M[i][j];
	for(int i=0; i<q; i++) {
		cin>>n;
		for(int j=0; j<n; j++) {
			string str; cin>>str;
			for(int k=0; k<m; k++) if(str == word[k]) { R[j] = k; break; }
		}
		memset(cache, -1, sizeof(cache));
		ocr(0, 0);
		cout<<reconstruct(0, 0)<<"\n";
	}
}
/*
5 3
I am a boy buy
1.0 0.0 0.0 0.0 0.0
0.1 0.6 0.1 0.1 0.1
0.1 0.1 0.6 0.1 0.1
0.1 0.1 0.1 0.6 0.1
0.2 0.2 0.2 0.2 0.2
0.2 0.2 0.2 0.2 0.2
0.8 0.1 0.0 0.1 0.0
0.1 0.7 0.0 0.2 0.0
0.0 0.1 0.8 0.0 0.1
0.0 0.0 0.0 0.5 0.5
0.0 0.0 0.0 0.5 0.5
4 I am a buy
4 I I a boy
4 I am am boy
*/

