#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct student {
	int id;
	char name[12];
	double points;
} STUD;

STUD * read_students_text(char *filename) {

	return NULL;			
}

STUD * read_students_binary(char *filename) {
	FILE* fd = fopen(filename, "rb");
	
	fseek(fd, 0, SEEK_END);
	int size = ftell(fd) / sizeof(STUD) + 1;
	STUD* students = (STUD*)malloc(sizeof(STUD)*size);
	fseek(fd, 0, SEEK_SET);
	
	fread(students, sizeof(STUD), size-1, fd);
	students[size-1].id = -1;
	
	return students;
}

void save_students_text(STUD *ps, char *filename) {
	FILE *fd = fopen(filename, "wt");
	
	if (fd) {
		while (ps->id > 0) {
			fprintf(fd, "%d %s %lf\n", ps->id, ps->name, ps->points);
			ps++;
		}
		fclose(fd);
	}		
}

void save_students_binary(STUD *ps, char *filename) {
	FILE *fd = fopen(filename, "wb");
	STUD *pcur = ps;
	int nitem = 0;
	
	if (fd) {
		while (pcur->id > 0) pcur++;
		fwrite(ps, sizeof(STUD), pcur - ps, fd);
		fclose(fd);
	}		
}

void stud_print(STUD *ps) {
	printf("%03d %-12s %5.1lf\n", ps->id, ps->name, ps->points);
}

void print_students(STUD *ps) {
	while (ps->id > 0) stud_print(ps++);
}

void print_tops(STUD *sorted_ps) {
	double highest_points = sorted_ps->points;
	do {
		stud_print(sorted_ps++);
	} while (sorted_ps->points == highest_points);
}

STUD * sort_students(STUD *ps) {
	int len;
	for(len=0; ps[len].id>=0; len++);
	
	for(int i=0; i<len; i++)
		for(int j=i+1; j<len; j++)
			if(ps[i].points > ps[j].points) {
				STUD temp = ps[i];
				ps[i] = ps[j];
				ps[j] = temp;
			}
	
	return ps;
}

int main(void) {
	char *filename = "output.bin";
	STUD test_data[] = { {1, "Choi", 9.9}, {2, "Park", 0.1}, {3, "Kim", 5.0 }, 
	{4, "Lee", 9.9 }, {5, "Moon", 9.5 }, {6, "Kang", 7.0 }, {7, "Jeon", 0.9 }, {-1, "", 0 } };
	STUD *students = test_data, *readin_students = NULL, *sorted_students = NULL;
	int test_case = 1, bbinary = 1;
	
	if (bbinary) {
		save_students_binary(students, filename);
		readin_students = read_students_binary(filename);
	}
	else {
		save_students_text(students, filename);
		readin_students = read_students_text(filename);
	}
	if (readin_students) {
		sorted_students = sort_students(readin_students);	
		print_tops(sorted_students);
	}	
	return 0;	
}

