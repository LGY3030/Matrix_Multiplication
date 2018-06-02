#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define SIZE 1024
#define MAXTHREADS 2

int a[SIZE][SIZE],b[SIZE][SIZE];
long int c[SIZE][SIZE];
void read();
int realsize;
static void print(int start,int end,int tid);
void *multiply(void *arg);
pthread_t pt[MAXTHREADS];

int main() {
	void *exit_status;
	double start,end;
	float diff;
	int i,j,rp;
	scanf("%d",&realsize);
	printf("reading the values\n");
	read();
	printf("multiplying the matrics \n");
	/*start = time(NULL);
	printf("start time %lf \n",start);*/
	for(i=0;i<MAXTHREADS;i++){
		pthread_create(&pt[i],NULL,multiply,(void *)i);			
	}
	for(i=0;i<MAXTHREADS;i++){
		pthread_join(pt[i],NULL);
	}
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			printf("%d",c[i][j]);
		}
		printf("\n");
	}
	/*end = time(NULL);
	printf("Final time %lf\n",end-start);*/
	return 0;
}

void read(){
	int i,j;
	printf("Matrix A:\n");
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			scanf("%d",&a[i][j]);
		}
	}
	printf("Matrix B:\n");
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			scanf("%d",&b[i][j]);
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
	printf("THREAD %d CREATED \n",l);
	for(i=start;i<end;i++){
		for(j=0;j<SIZE;j++){
			for(k=0;k<SIZE;k++){
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	return NULL;
}

void print(int start,int end,int tid){
	int i,j;
	//printf("THREAD %d PRINTING THE VALUES \n",tid);
	for(i=start;i<end;i++){
		for(j=0;j<SIZE;j++){
			printf("c[%d][%d] : %d ",i,j,c[i][j]);
		}
	}
	printf("\n");
	//printf("THREAD %d PRINTED THE VALUES \n",tid);
}
