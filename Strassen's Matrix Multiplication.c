#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define SIZE 1024

int realsize;
void read();
void multiply(int a[][realsize],int b[][realsize],int c[][realsize],int realsize);



int main(){
	
	double start,end;
	int i,j;
	printf("Size:");
	scanf("%d",&realsize);
	int a[realsize][realsize],b[realsize][realsize];
	long int c[realsize][realsize];
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
	start = time(NULL);
	multiply(a,b,c,realsize);
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

void multiply(int a[][realsize],int b[][realsize],int c[][realsize],int realsize){
	
	int p1[realsize/2][realsize/2],p2[realsize/2][realsize/2];
	int p3[realsize/2][realsize/2],p4[realsize/2][realsize/2];
	int p5[realsize/2][realsize/2],p6[realsize/2][realsize/2];
	int p7[realsize/2][realsize/2];

	int temp1[realsize/2][realsize/2],temp2[realsize/2][realsize/2];

	int q1,q2,q3,q4,q5,q6,q7,i,j;

	if(realsize>=2) {
		for(i=0;i<realsize/2;i++){
			for(j=0;j<realsize/2;j++){
				temp1[i][j]=a[i][j]+a[i+realsize/2][j+realsize/2];
			}
		}
		
		for(i=0;i<realsize/2;i++){
			for(j=0;j<realsize/2;j++){
				temp2[i][j] = b[i][j]+b[i+realsize/2][j+realsize/2];
			}
		}
		
	multiply(temp1,temp2,p1,realsize/2);


	}
}
