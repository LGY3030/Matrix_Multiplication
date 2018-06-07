#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define SIZE 1024

  struct mypara
	{
       int a[50][50];
       int b[50][50];
       long int c[50][50];
	};


int realsize;
int MAXTHREADS;
void *multiply(void *arg);

int main() {
	double start,end;
	int i,j;
	printf("Size:");
	scanf("%d",&realsize);
	
	struct mypara para;
	printf("\nMatrix A:\n");
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			scanf("%d",&para.a[i][j]);
		}
	}
	printf("\nMatrix B:\n");
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			scanf("%d",&para.b[i][j]);
		}
	}
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			para.c[i][j] = 0;
		}
	}
	MAXTHREADS=realsize;
	pthread_t pt[MAXTHREADS];
	start = time(NULL);
	for(i=0;i<MAXTHREADS;i++){
		pthread_create(&pt[i],NULL,multiply,&para);			
	}
	for(i=0;i<MAXTHREADS;i++){
		pthread_join(pt[i],NULL);
	}
	printf("\nMatrix C:\n");
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			if(j==0)
			printf("%d",para.c[i][j]);
			else
			printf(" %d",para.c[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	end = time(NULL);
	printf("Total time %lf\n",end-start);
	return 0;
}



void *multiply(void *arg){
	
	
	struct mypara *para;
    para = (struct mypara *) arg;
	(*para).c[0][0] = 5;
	/*int i,j,k,l;
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
	return NULL;*/
}


