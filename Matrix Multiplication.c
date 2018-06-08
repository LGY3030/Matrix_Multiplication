#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define SIZE 1024


int a[SIZE][SIZE],b[SIZE][SIZE];
long int c[SIZE][SIZE];
void read();
int realsize;
void multiply();

int main() {
	double start,end;
	int i,j;
	printf("Size:");
	scanf("%d",&realsize);
	read();
	start = time(NULL);
	multiply();
	printf("\nMatrix C:\n");
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			if(j==0)
			printf("%d",c[i][j]);
			else
			printf(" %d",c[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	end = time(NULL);
	printf("Total time %lf\n",end-start);
	return 0;
}

void read(){
	int i,j;
	printf("\nMatrix A:\n");
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			scanf("%d",&a[i][j]);
		}
	}
	printf("\nMatrix B:\n");
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

void multiply(){
	int i,j,k;	
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			for(k=0;k<realsize;k++){
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	return NULL;
}
