void sum_rows2(double *a, double *b, long n) {
    long i, j;
    for (i = 0; i < n; i++) {
	double val = 0;
	for (j = 0; j < n; j++)
	    	val += a[i*n + j];
        b[i] = val;
    }
}
