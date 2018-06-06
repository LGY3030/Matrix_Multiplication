#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define SIZE 1024


int a[SIZE][SIZE],b[SIZE][SIZE];
int c[SIZE][SIZE];
void read();
int realsize;
int MAXTHREADS;
void *multiply(void *arg);

int main() {
	clock_t start,end;
	int i,j;
	double time;
	int arow,acol,brow,bcol;
	FILE *infile, *outfile;
	infile = fopen("input.txt", "r");
	
	if(infile == NULL) {
    	printf("Error in Opening infile");
    	return EXIT_FAILURE;
	}

	fscanf(infile, "%d %d", &arow, &acol);	
	realsize=arow;
	for(i = 0; i < realsize; i++)
		for(j = 0; j < realsize; j++)
			fscanf(infile, "%d", &a[i][j]);
	
	fscanf(infile, "%d %d", &brow, &bcol);
	for(i = 0; i < realsize; i++)	
		for(j = 0; j < realsize; j++)
			fscanf(infile, "%d", &b[i][j]);
	fclose(infile);
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			c[i][j] = 0;
		}
	}
	outfile = fopen("output.txt", "w+");
	MAXTHREADS=realsize;
	pthread_t pt[MAXTHREADS];
	start = clock();
	for(i=0;i<MAXTHREADS;i++){
		pthread_create(&pt[i],NULL,multiply,(void *)i);			
	}
	for(i=0;i<MAXTHREADS;i++){
		pthread_join(pt[i],NULL);
	}
	end = clock();
	time = ((double) (end - start));
	fprintf(outfile, "Time:%f \n", time);
	fprintf(outfile, "%d %d \n", realsize, realsize);
	for(i = 0; i < realsize; i++) {
		for(j = 0; j < realsize; j++){
			if(j==0)
				fprintf(outfile, "%d", c[i][j]);
			else
				fprintf(outfile, " %d", c[i][j]);
		}
		fprintf(outfile, "\n");		
	}
	fclose(outfile);

	return 0;
}

void *multiply(void *arg){
	int i,j,k,l;
	l = (int)arg;
	int part,start,end;
	part = realsize/MAXTHREADS;
	start = l*part;
	end = start + part;
	//printf("THREAD %d CREATED \n",l);
	for(i=start;i<end;i++){
		for(j=0;j<realsize;j++){
			for(k=0;k<realsize;k++){
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	return NULL;
}

