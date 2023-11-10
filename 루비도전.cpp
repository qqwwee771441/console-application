#include <cstdio>
#include <vector>
#include <algorithm>

void init( int N, int M, std::vector<int> Y1, std::vector<int> Y2 ) ;
long long minimize( int A, int B ) ;

int main() {
	int N, M, Q;
	std::vector<int> Y1(3000), Y2(3000);
	int A, B;
	
	scanf("%d %d %d", &N, &M, &Q);
	
	for(int i=0, y1, y2; i<N; i++) {
		scanf("%d %d", &y1, &y2);
		Y1[i] = y1;
		Y2[i] = y2;
	}
	init(N, M, Y1, Y2);
	
	for(int i=0; i<Q; i++) {
		scanf("%d %d", &A, &B);
		printf("%lld\n", minimize(A, B));
	}
}

struct Slot {
	int start;
	int end;
	std::vector<int> A;
	std::vector<int> B;
	Slot* prev;
	Slot* next;
	bool done;
};

Slot* head;
Slot* tail;

void show() {
	printf("\n");
	for(Slot* slot=head->next; slot!=tail; slot=slot->next) {
		printf("[%d ", slot->start);
		for(int i=0, num=slot->A.size(); i<num; i++) {
			printf("(%d, %d) ", (slot->A)[i], (slot->B)[i]);
		}
		printf("%d]\n", slot->end);
	}
	printf("\n");
}

void optimize(std::vector<int>& A, std::vector<int>& B) {
	
}

void init( int N, int M, std::vector<int> Y1, std::vector<int> Y2 ) {
	head = new Slot;
	tail = new Slot;
	
	Slot* newSlot = new Slot;
	newSlot->start = 0;
	newSlot->end = M-1;
	newSlot->A.push_back(0);
	newSlot->B.push_back(0);
	newSlot->prev = head;
	newSlot->next = tail;
	newSlot->done = true;
	head->next = newSlot;
	tail->prev = newSlot;
	
	Slot* slot;
	int num;
	int start, end;
	int y1, y2;
	std::vector<int> sideA, sideB;
	for(int i=0; i<N; i++) {
		y1 = Y1[i]; 
		y2 = Y2[i];
		sideA.clear();
		sideB.clear();
		for(slot=head->next; slot!=tail; slot=slot->next) {
			start = slot->start;
			end = slot->end;
			if(start>y2 || end<y1) {
				sideA.insert(sideA.end(), slot->A.begin(), slot->A.end());
				sideB.insert(sideB.end(), slot->B.begin(), slot->B.end());
				slot->done = true;
			}
			else if(start>=y1 && end<=y2) {
				num = slot->B.size();
				for(int i=0; i<num; i++) (slot->B)[i]++;
				slot->done = false;
			}
			else if(start < y1) {
				newSlot = new Slot;
				newSlot->start = y1;
				newSlot->end = end;
				newSlot->prev = slot;
				newSlot->next = slot->next;
				newSlot->A.insert(newSlot->A.end(), slot->A.begin(), slot->A.end());
				newSlot->B.insert(newSlot->B.end(), slot->B.begin(), slot->B.end());
				newSlot->done = false;
				slot->end = y1-1;
				slot->next = newSlot;
				sideA.insert(sideA.end(), slot->A.begin(), slot->A.end());
				sideB.insert(sideB.end(), slot->B.begin(), slot->B.end());
				slot->done = true;
			}
			else {
				newSlot = new Slot;
				newSlot->start = y2+1;
				newSlot->end = end;
				newSlot->prev = slot;
				newSlot->next = slot->next;
				newSlot->A.insert(newSlot->A.end(), slot->A.begin(), slot->A.end());
				newSlot->B.insert(newSlot->B.end(), slot->B.begin(), slot->B.end());
				newSlot->done = true;
				slot->end = y2;
				slot->next = newSlot;
				num = slot->B.size();
				for(int i=0; i<num; i++) (slot->B)[i]++;
				slot->done = false;
			}
		}
		
		for(slot=head->next; slot!=tail; slot=slot->next)
			if( !(slot->done) ) {
				num = sideA.size();
				for(int i=0; i<num; i++) {
					slot->A.push_back( sideA[i]+1 );
					slot->B.push_back( sideB[i] );
				}
				optimize(slot->A, slot->B);
			}
	}
}

long long minimize( int A, int B ) {
	Slot* slot;
	int num;
	long long score;
	long long minScore = 9223372036854775807LL;
	for(slot=head->next; slot!=tail; slot=slot->next) {
		num = slot->A.size();
		for(int i=0; i<num; i++) {
			score = (long long)(slot->A)[i]*A + (long long)(slot->B)[i]*B;
			if(score < minScore) minScore = score;
		}
	}
	return minScore;
}

