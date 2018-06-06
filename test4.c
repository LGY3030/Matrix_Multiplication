#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define SIZE 1000


int a[SIZE][SIZE],b[SIZE][SIZE];
long int c[SIZE][SIZE];
void read();
int realsize=SIZE;
int MAXTHREADS;
void *multiply(void *arg);

int main() {
	clock_t start,end;
	int i,j;
	double time;
	MAXTHREADS=4;
	pthread_t pt[MAXTHREADS];
	read();
	start = clock();
	for(i=0;i<MAXTHREADS;i++){
		pthread_create(&pt[i],NULL,multiply,(void *)i);			
	}
	for(i=0;i<MAXTHREADS;i++){
		pthread_join(pt[i],NULL);
	}

	end = clock();
	time=((double) (end - start));
	printf("Total time %f\n",time);
	return 0;
}

void read(){
	int i,j;
	
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			a[i][j]=1;
		}
	}
	
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			b[i][j]=1;
		}
	}
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			c[i][j] = 0;
		}
	}
	/*for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}*/
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
