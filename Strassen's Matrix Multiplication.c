#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define SIZE 1024

int realsize;
void read();
void multiply(int a[][realsize],int b[][realsize],int c[][realsize],int size);



int main(){
	
	double start,end;
	int i,j,temp;
	printf("Size:");
	scanf("%d",&realsize);
	temp=realsize;
	int a[realsize][realsize],b[realsize][realsize];
	int c[realsize][realsize];
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
	for(i=0;i<temp;i++){
		for(j=0;j<temp;j++){
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

void multiply(int a[][realsize],int b[][realsize],int c[][realsize],int size){
	
	int p1[size/2][size/2],p2[size/2][size/2];
	int p3[size/2][size/2],p4[size/2][size/2];
	int p5[size/2][size/2],p6[size/2][size/2];
	int p7[size/2][size/2];

	int temp1[size/2][size/2],temp2[size/2][size/2];

	int q1,q2,q3,q4,q5,q6,q7,i,j;
	
	if(size==1) {
		c[0][0]=a[0][0]*b[0][0];
	}
	else{
		//P1 
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp1[i][j] = a[i][j];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp2[i][j] = b[i][j+size/2]-b[i+size/2][j+size/2];
			}
		}
		realsize=size/2;
		multiply(temp1,temp2,p1,size/2);

		//P2 
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){		
				temp1[i][j]=a[i][j]+a[i][j+size/2];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){	
				temp2[i][j]=b[i+size/2][j+size/2];
			}
		}
		realsize=size/2;
		multiply(temp1,temp2,p2,size/2);

		//p3
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp1[i][j]=a[i+size/2][j]+a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp2[i][j] = b[i][j];
			}
		}
		realsize=size/2;
		multiply(temp1,temp2,p3,size/2);
		
		//p4
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp1[i][j]=a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp2[i][j]=b[i+size/2][j]-b[i][j];
			}
		}
		realsize=size/2;
		multiply(temp1,temp2,p4,size/2);

		//p5
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp1[i][j]=a[i][j]+a[i+size/2][j+size/2];
			}
		}		
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp2[i][j]=b[i][j]+b[i+size/2][j+size/2];
			}
		}
		realsize=size/2;
		multiply(temp1,temp2,p5,size/2);

		//p6
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp1[i][j] = a[i][j+size/2]-a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp2[i][j] = b[i+size/2][j]+b[i+size/2][j+size/2];
			}
		}
		realsize=size/2;
		multiply(temp1,temp2,p6,size/2);

		//p7
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp1[i][j] = a[i][j]-a[i+size/2][j];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				temp2[i][j]=b[i][j]+b[i][j+size/2];
			}
		}
		realsize=size/2;
		multiply(temp1,temp2,p7,size/2);

		//c11
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				c[i][j]=p5[i][j]+p4[i][j]-p2[i][j]+p6[i][j];
			}
		}

		//c12
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				c[i][j+size/2]=p1[i][j]+p2[i][j];
			}
		}

		//c21
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				c[i+size/2][j]=p3[i][j]+p4[i][j];
			}
		}

		//c22
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				c[i+size/2][j+size/2]=p1[i][j]+p5[i][j]-p3[i][j]-p7[i][j];
			}
		}
	}
}


