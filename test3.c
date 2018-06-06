#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>


int realsize=4;
int a[4][4],b[4][4];
int c[4][4];
void *multiply(void* arg);
void firstmultiply(int size);



int main(){
	
	double start,end;
	int i,j,temp;
	temp=realsize;
	printf("\nMatrix A:\n");
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			a[i][j]=1;
			printf("%d",a[i][j]);
		}
		printf("\n");
	}
	printf("\nMatrix B:\n");
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			b[i][j]=1;
			printf("%d",b[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<realsize;i++){
		for(j=0;j<realsize;j++){
			c[i][j] = 0;
		}
	}
	start = time(NULL);
	firstmultiply(realsize);
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

void firstmultiply(int size){
	int p1[size/2][size/2],p2[size/2][size/2];
	int p3[size/2][size/2],p4[size/2][size/2];
	int p5[size/2][size/2],p6[size/2][size/2];
	int p7[size/2][size/2];
	int temp1[size/2][size/2],temp2[size/2][size/2];
	int i,j;
	pthread_t pt[7];
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
		pthread_create(&pt[1],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[2],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[3],NULL,multiply,(void *)realsize);
		
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
		pthread_create(&pt[4],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[5],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[6],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[7],NULL,multiply,(void *)realsize);
		for(i=0;i<7;i++){
		pthread_join(pt[i],NULL);
		}
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
void *multiply(void* arg){
	int size;
	size = (int)arg;
	int p1[size/2][size/2],p2[size/2][size/2];
	int p3[size/2][size/2],p4[size/2][size/2];
	int p5[size/2][size/2],p6[size/2][size/2];
	int p7[size/2][size/2];
	int temp1[size/2][size/2],temp2[size/2][size/2];
	int i,j;
	pthread_t pt[7];
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
		pthread_create(&pt[1],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[2],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[3],NULL,multiply,(void *)realsize);
		
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
		pthread_create(&pt[4],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[5],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[6],NULL,multiply,(void *)realsize);

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
		pthread_create(&pt[7],NULL,multiply,(void *)realsize);
		for(i=0;i<7;i++){
		pthread_join(pt[i],NULL);
		}
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


