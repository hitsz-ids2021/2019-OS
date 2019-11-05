void sum_rows1(double *a, double *b, long n) {
    long i, j;

    for (i = 0; i < n; i++) {
	b[i] = 0;
	for (j = 0; j < n; j++)
	    	b[i] += a[i*n + j];
    }
}


