/*

a  |  b     e  |  f
c  |  d     g  |  h

p1=a(f-h)
p2=(a+b)h
p3=(c+d)e
p4=d(g-e)
p5=(a+d)(e+h)
p6=(b-d)(g+h)
p7=(a-c)(e+f)

c11=p4+p5-p2+p6
c12=p1+p2
c21=p3+p4
c22=p1+p5-p3-p7

*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int squarematrix(int num){
	int original_num = num, lower_power = 0, i, actual_num = 1;
	if(num==1){ 
		return 1;
	} 
	while(num>1){ 
		lower_power++;
		num /= 2;
	}
	for(i=0;i<lower_power;i++) {
		actual_num *= 2;
	}

	if(actual_num == original_num){
		return original_num;
	} 
	else{
		return actual_num * 2;
	} 
}

void freethat(double ** a, double ** b, double ** c, int n){
	int i;
	for(i=0;i<n;i++){
		free(a[i]);
		free(b[i]);
		free(c[i]);
	}
	free(a);
	free(b);
	free(c);
}

double ** creatematrix(int row,int col){
	int i;
	double ** m = (double **) calloc(row, sizeof(double *));
	for(i=0; i<row; i++)
	{
		m[i] = (double *) calloc(col, sizeof(double));
	}
	return m;
}

double ** addmatrix(double ** a, double ** b, int size){
	int i,j;
	double ** c = creatematrix(size,size);
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			c[i][j]=a[i][j]+b[i][j];
		}
	}
	return c;
}

double ** submatrix(double ** a, double ** b, int size){
	int i,j;
	double ** c = creatematrix(size,size);
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			c[i][j]=a[i][j]-b[i][j];
		}
	}
	return c;
}	

double ** multiply(double ** a, double ** b, int size){
	int i,j;
	int resize = size/2;
	double ** c = creatematrix(size,size);
	if(size==1){
		c[0][0] = a[0][0] * b[0][0];
	}
	else{
		double ** a11 = creatematrix(resize,resize);
		double ** a12 = creatematrix(resize,resize);
		double ** a21 = creatematrix(resize,resize);
		double ** a22 = creatematrix(resize,resize);
		double ** b11 = creatematrix(resize,resize);
		double ** b12 = creatematrix(resize,resize);
		double ** b21 = creatematrix(resize,resize);
		double ** b22 = creatematrix(resize,resize);
		double ** ctemp;

		for(i=0;i<resize;i++){
			for(j=0;j<resize;j++){
				a11[i][j] = a[i][j];
				b11[i][j] = b[i][j];
			}
		}
		int k=0;
		for(i=resize;i<size;i++){
			for(j=0;j<resize;j++){
				a21[k][j] = a[i][j];
				b21[k][j] = b[i][j];
			}
			k++;
		}
		int l=0;
		for(i=0;i<resize;i++){
			for(j=resize;j<size;j++){
				a12[i][l] = a[i][j];
				b12[i][l] = b[i][j];
				l++;
			}
			l=0;
		}
		k=0;
		l=0;
		for(i=resize;i<size;i++){
			for(j=resize;j<size;j++){
				a22[k][l] = a[i][j];
				b22[k][l] = b[i][j];
				l++;
			}
			l=0;
			k++;
		}
		
		double ** S1 = submatrix(b12, b22, resize);
		double ** S2 = addmatrix(a11, a12, resize);
		double ** S3 = addmatrix(a21, a22, resize);
		double ** S4 = submatrix(b21, b11, resize);
		double ** S5 = addmatrix(a11, a22, resize);
		double ** S6 = addmatrix(b11, b22, resize);
		double ** S7 = submatrix(a12, a22, resize);
		double ** S8 = addmatrix(b21, b22, resize);
		double ** S9 = submatrix(a11, a21, resize);
		double ** S10 = addmatrix(b11, b12, resize);
		
		double ** P1=multiply(a11, S1, resize);
		double ** P2=multiply(S2, b22, resize);
		double ** P3=multiply(S3, b11, resize);
		double ** P4=multiply(a22, S4, resize);
		double ** P5=multiply(S5, S6, resize);
		double ** P6=multiply(S7, S8, resize);
		double ** P7=multiply(S9, S10, resize);
		
		

		double ** t1;
		t1 = addmatrix(P5, P4, resize);
		double ** t2;
		t2 = addmatrix(t1, P6, resize);
		
		ctemp = submatrix(t2, P2, resize);
		
		for(i=0;i<resize;i++){
			for(j=0;j<resize;j++){
				c[i][j] = ctemp[i][j];
			}
		}
		freethat(t1, t2, ctemp, resize);
		
		ctemp=addmatrix(P1, P2, resize);
		l = 0;
		for(i=0;i<resize;i++){
			for(j=resize;j<size;j++){
				c[i][j] = ctemp[i][l];
				l++;
			}
			l = 0;
		}
		for(i=0;i<resize;i++){
			free(ctemp[i]);
		}
		free(ctemp);
		
		ctemp=addmatrix(P3, P4, resize);
		k = 0;
		for(i=resize;i<size;i++){
			for(j=0;j<resize;j++){
				c[i][j] = ctemp[k][j];		
			}
			k++;
		}
		for(i=0; i<resize;i++){
			free(ctemp[i]);
		}
		free(ctemp);
		
		t1 = addmatrix(P5, P1, resize);
		t2 = submatrix(t1, P3, resize);
		ctemp = submatrix(t2, P7, resize);
		k = 0;
		l = 0;
		for(i=resize;i<size;i++){
			for(j=resize;j<size;j++){
				c[i][j] = ctemp[k][l];
				l++;
			}
			l = 0;
			k++;
		}
		freethat(t1, t2, ctemp, resize);
		
		
		freethat(a11, a12, a21, resize);
		freethat(a22, b11, b12, resize);
		freethat(b21, b22, S10,  resize);
		freethat(S1, S2, S3, resize);
		freethat(S4, S5, S6, resize);
		freethat(S7, S8, S9, resize);
		freethat(P6, P1, P2, resize);
		freethat(P3, P4, P5, resize);
		for(i=0;i<resize;i++){
			free(P7[i]);
		}
		free(P7);
	}
	return c;
}


int main(){
	int i,j;
	clock_t start, end;
	double time;
	FILE *infile, *outfile;
	int arow,acol,brow,bcol;
	int size;
	infile = fopen("input.txt", "r");
	if(infile == NULL) {
    	printf("Error in Opening infile");
    	return EXIT_FAILURE;
	}

	fscanf(infile, "%d %d", &arow, &acol);
	if(arow>=acol){
		size=squarematrix(arow);
	}
	else{
		size=squarematrix(acol);
	}
	double ** a = creatematrix(size,size);
	for(i=0;i<arow;i++){
		for(j=0;j<acol;j++){
			fscanf(infile, "%lf", &a[i][j]);	
		}			
	}
	
	fscanf(infile, "%d %d", &brow, &bcol);
	double ** b = creatematrix(size,size);
	for(i=0;i<brow;i++){
		for(j=0;j<bcol;j++){
			fscanf(infile, "%lf", &b[i][j]);	
		}			
	}

	start = clock();
	
	double ** c = multiply(a,b,size);

	end = clock();
	time=((double)end-start);
	
	outfile = fopen("output.txt", "w+");
	fprintf(outfile, "Time: %lf ms\n", time);
	fprintf(outfile, "%d %d \n", arow, bcol);
	for(i=0;i<arow;i++) {
		for(j=0;j<bcol;j++){
				fprintf(outfile, "%lf ", c[i][j]);
		}
		fprintf(outfile, "\n");		
	}
	fclose(outfile);
	
	freethat(a, b, c, size);
	return 0;
}
