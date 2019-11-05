# include <stdio.h>
# include <time.h>
# include <stdlib.h>

void sum_rows1(double *a, double *b, long n) {
    long i, j;

    for (i = 0; i < n; i++) {
	b[i] = 0;
	for (j = 0; j < n; j++)
	    	b[i] += a[i*n + j];
    }
}

void sum_rows2(double *a, double *b, long n) {
    long i, j;
    for (i = 0; i < n; i++) {
	double val = 0;
	for (j = 0; j < n; j++)
	    	val += a[i*n + j];
        b[i] = val;
    }
}

int main()
{
	int size_a = 90000;
	int size_b = 300;
	double a[size_a],b[size_b];
	for (int i = 0; i < size_a; i++) {
		a[i] = rand()%10; 
	}
	for (int i = 0; i < size_b; i++) {
		b[i] = rand()%10; 
	}
    	//printf("\n");
    	clock_t start1 = clock();
    	sum_rows1(a,b,size_b);
    	clock_t end1 = clock();
    	printf("time1 = %lu\n", end1-start1);

	clock_t start2 = clock();
    	sum_rows2(a,b,size_b);
    	clock_t end2 = clock();
    	printf("time2 = %lu\n", end2-start2);
	/* code */
	return 0;
}
