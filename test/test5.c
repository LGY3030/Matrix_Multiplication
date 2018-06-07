/* Strassen's Matrix multiplication */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>



//function to free allocated memory
void freeThat(float ** a, float ** b, float ** c, int n)
{
	for(int i=1; i<=n; ++i)
	{
		free(a[i]);
		free(b[i]);
		free(c[i]);
	}
	free(a);
	free(b);
	free(c);
}

//function to allocate memory to the matrix types
double ** createMatrix(int row,int col)
{
	int i;
	double ** m = (double **) calloc(row, sizeof(double *));
	for(i=0; i<row; i++)
	{
		m[i] = (double *) calloc(col, sizeof(double));
	}
	return m;
}



//function to add two matrices and return the result
float ** addMatrix(float ** a, float ** b, int n)
{
	float ** c = initMatrix(n);
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

//function to subtract a matrix from another and return the result
float ** subMatrix(float ** a, float ** b, int n)
{
	float ** c = initMatrix(n);
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
			c[i][j] = a[i][j] - b[i][j];
		}
	}
	return c;
}	

//Recursive multiplication implemented by following the strassen's algorithm
float ** multiply(float ** a, float ** b, int n)
{
	int N = n/2;
	float ** c = initMatrix(n);
	
	//Base condition
	if(n==1)
	{
		c[1][1] = a[1][1] * b[1][1];
	}
	else
	{
		//Allocate memory to the submatrices
		float ** A11 = initMatrix(N);
		float ** A12 = initMatrix(N);
		float ** A21 = initMatrix(N);
		float ** A22 = initMatrix(N);
		float ** B11 = initMatrix(N);
		float ** B12 = initMatrix(N);
		float ** B21 = initMatrix(N);
		float ** B22 = initMatrix(N);
		float ** Ctemp;
		//Form the submatrices
		for(int i=1; i<=(N); ++i)
		{
			for(int j=1; j<=(N); ++j)
			{
				A11[i][j] = a[i][j];
				B11[i][j] = b[i][j];
			}
		}
		int k=1;
		for(int i=(N)+1; i<=n; ++i)
		{
			for(int j=1; j<=(N); ++j)
			{
				A21[k][j] = a[i][j];
				B21[k][j] = b[i][j];
			}
			k++;
		}
		int l = 1;
		for(int i=1; i<=(N); ++i)
		{
			for(int j=(N)+1; j<=n; ++j)
			{
				A12[i][l] = a[i][j];
				B12[i][l] = b[i][j];
				l++;
			}
			l = 1;
		}
		k = 1;
		l = 1;
		for(int i=(N)+1; i<=n; ++i)
		{
			for(int j=(N)+1; j<=n; ++j)
			{
				A22[k][l] = a[i][j];
				B22[k][l] = b[i][j];
				l++;
			}
			l = 1;
			k++;
		}
		float ** S1 = subMatrix(B12, B22, N);
		float ** S2 = addMatrix(A11, A12, N);
		float ** S3 = addMatrix(A21, A22, N);
		float ** S4 = subMatrix(B21, B11, N);
		float ** S5 = addMatrix(A11, A22, N);
		float ** S6 = addMatrix(B11, B22, N);
		float ** S7 = subMatrix(A12, A22, N);
		float ** S8 = addMatrix(B21, B22, N);
		float ** S9 = subMatrix(A11, A21, N);
		float ** S10 = addMatrix(B11, B12, N);
		
		//Compute the 7 multiplications specified by Strassen's
		float ** P1 = multiply(A11, S1, N);
		float ** P2 = multiply(S2, B22, N);
		float ** P3 = multiply(S3, B11, N);
		float ** P4 = multiply(A22, S4, N);
		float ** P5 = multiply(S5, S6, N);
		float ** P6 = multiply(S7, S8, N);
		float ** P7 = multiply(S9, S10, N);
		
		//the resultant matrices are then coupled together for further operations as specified by the algorithm
		float ** t1;
		t1 = addMatrix(P5, P4, N);
		float ** t2;
		t2 = addMatrix(t1, P6, N);
		Ctemp = subMatrix(t2, P2, N);
		for(int i=1; i<=(N); ++i)
		{
			for(int j=1; j<=(N); ++j)
			{
				c[i][j] = Ctemp[i][j];
			}
		}
		freeThat(t1, t2, Ctemp, N);
		
		Ctemp = addMatrix(P1, P2, N);
		l = 1;
		for(int i=1; i<=(N); ++i)
		{
			for(int j=(N)+1; j<=n; ++j)
			{
				c[i][j] = Ctemp[i][l];
				l++;
			}
			l = 1;
		}
		for(int i=1; i<=N; ++i)
		{
			free(Ctemp[i]);
		}
		free(Ctemp);
		
		Ctemp = addMatrix(P3, P4, (N));
		k = 1;
		for(int i=(N)+1; i<=n; ++i)
		{
			for(int j=1; j<=(N); ++j)
			{
				c[i][j] = Ctemp[k][j];
				
			}
			k++;
		}
		for(int i=1; i<=N; ++i)
		{
			free(Ctemp[i]);
		}
		free(Ctemp);
		
		t1 = addMatrix(P5, P1, N);
		t2 = subMatrix(t1, P3, N);
		Ctemp = subMatrix(t2, P7, N);
		k = 1;
		l = 1;
		for(int i=(N)+1; i<=n; ++i)
		{
			for(int j=(N)+1; j<=n; ++j)
			{
				c[i][j] = Ctemp[k][l];
				l++;
			}
			l = 1;
			k++;
		}
		freeThat(t1, t2, Ctemp, N);
		freeThat(A11, A12, A21, N);
		freeThat(A22, B11, B12, N);
		freeThat(B21, B22, S10,  N);
		freeThat(S1, S2, S3, N);
		freeThat(S4, S5, S6, N);
		freeThat(S7, S8, S9, N);
		freeThat(P6, P1, P2, N);
		freeThat(P3, P4, P5, N);
		for(int i=1; i<=N; ++i)
		{
			free(P7[i]);
		}
		free(P7);
	}
	
	return c; 
}


int main()
{
	clock_t start, end;
	double time;
	FILE *infile, *outfile;
	int arow,acol,brow,bcol;
	infile = fopen("input.txt", "r");
	if(infile == NULL) {
    	printf("Error in Opening infile");
    	return EXIT_FAILURE;
	}

	fscanf(infile, "%d %d", &arow, &acol);
	if(arow>=acol){
		
	}
	double ** a = createMatrix(arow,acol);
	for(i=0;i<arow;i++){
		for(j=0;j<acol;j++){
			fscanf(infile, "%lf", &a[i][j]);	
		}
			
	}
	
	fscanf(infile, "%d %d", &brow, &bcol);
	double ** b = createMatrix(brow,bcol);
	for(i=0;i<brow;i++){
		for(j=0;j<bcol;j++){
			fscanf(infile, "%lf", &b[i][j]);	
		}
			
	}
	
	fclose(infile);
	
	double ** c = createMatrix(arow,bcol);

	start = clock();
	
	multiply(a,b,c,);

	end = clock();
	time=((double)end-start);
	
	printf("Time: %lf ms\n", time);
	for(int i=1; i<=n; ++i)
	{
		free(M1[i]);
		free(M2[i]);
		free(M3[i]);
	}
	free(M1);
	free(M2);
	free(M3);
	return 0;
}
