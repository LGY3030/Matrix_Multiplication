#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define SIZE 4

int realsize,size=4;
void read();
struct mypara
	{
		
        int p1[SIZE/2][SIZE/2],p2[SIZE/2][SIZE/2];
		int p3[SIZE/2][SIZE/2],p4[SIZE/2][SIZE/2];
		int p5[SIZE/2][SIZE/2],p6[SIZE/2][SIZE/2];
		int p7[SIZE/2][SIZE/2];
		int temp1[SIZE/2][SIZE/2],temp2[SIZE/2][SIZE/2];
		int a[SIZE][SIZE],b[SIZE][SIZE];
		int c[SIZE][SIZE];
		
	};
void *multiply(void *arg);
	


int main(){
	
	struct mypara para;
	double start,end;
	int i,j,temp;
	pthread_t initial;
	temp=SIZE;
	
	printf("\nMatrix A:\n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			para.a[i][j]=1;
			printf("%d ",para.a[i][j]);
		}
		printf("\n");
	}
	printf("\nMatrix B:\n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			para.b[i][j]=1;
			printf("%d ",para.b[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			para.c[i][j] = 0;
		}
	}
	start = time(NULL);
	pthread_create(&initial,NULL,multiply,&para);
	pthread_join(initial,NULL);
	
	printf("\nMatrix C:\n");
	for(i=0;i<temp;i++){
		for(j=0;j<temp;j++){
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
	int i,j,k=0;	
	struct mypara *para;
	para = (struct mypara *) arg;
	struct insidepara
	{
		
        int p1[SIZE/2][SIZE/2],p2[SIZE/2][SIZE/2];
		int p3[SIZE/2][SIZE/2],p4[SIZE/2][SIZE/2];
		int p5[SIZE/2][SIZE/2],p6[SIZE/2][SIZE/2];
		int p7[SIZE/2][SIZE/2];
		int temp1[SIZE/2][SIZE/2],temp2[SIZE/2][SIZE/2];
		int a[SIZE][SIZE],b[SIZE][SIZE];
		int c[SIZE][SIZE];
		
	};
	pthread_t pt[7];
	k=k+1;
	if(size==1) {
		printf("\n%d\n",k);
		(*para).c[0][0]=(*para).a[0][0]*(*para).b[0][0];
		
	}
	else{
		
		//P1 
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp1[i][j] = (*para).a[i][j];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp2[i][j] = (*para).b[i][j+size/2]-(*para).b[i+size/2][j+size/2];
			}
		}
		size=size/2;
		pthread_create(&pt[1],NULL,multiply,&para);	


		//P2 
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){		
				(*para).temp1[i][j]=(*para).a[i][j]+(*para).a[i][j+size/2];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){	
				(*para).temp2[i][j]=(*para).b[i+size/2][j+size/2];
			}
		}
		size=size/2;
		pthread_create(&pt[2],NULL,multiply,&para);

		//p3
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp1[i][j]=(*para).a[i+size/2][j]+(*para).a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp2[i][j] = (*para).b[i][j];
			}
		}
		size=size/2;
		pthread_create(&pt[3],NULL,multiply,&para);
		
		//p4
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp1[i][j]=(*para).a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp2[i][j]=(*para).b[i+size/2][j]-(*para).b[i][j];
			}
		}
		size=size/2;
		pthread_create(&pt[4],NULL,multiply,&para);

		//p5
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp1[i][j]=(*para).a[i][j]+(*para).a[i+size/2][j+size/2];
			}
		}		
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp2[i][j]=(*para).b[i][j]+(*para).b[i+size/2][j+size/2];
			}
		}
		size=size/2;
		pthread_create(&pt[5],NULL,multiply,&para);

		//p6
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp1[i][j] = (*para).a[i][j+size/2]-(*para).a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp2[i][j] = (*para).b[i+size/2][j]+(*para).b[i+size/2][j+size/2];
			}
		}
		size=size/2;
		pthread_create(&pt[6],NULL,multiply,&para);
		
		//p7
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp1[i][j] = (*para).a[i][j]-(*para).a[i+size/2][j];
			}
		}
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).temp2[i][j]=(*para).b[i][j]+(*para).b[i][j+size/2];
			}
		}
		size=size/2;
		pthread_create(&pt[7],NULL,multiply,&para);
		//c11
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).c[i][j]=(*para).p5[i][j]+(*para).p4[i][j]-(*para).p2[i][j]+(*para).p6[i][j];
			}
		}

		//c12
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).c[i][j+size/2]=(*para).p1[i][j]+(*para).p2[i][j];
			}
		}

	//c21
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).c[i+size/2][j]=(*para).p3[i][j]+(*para).p4[i][j];
			}
		}

	//c22
		for(i=0;i<size/2;i++){
			for(j=0;j<size/2;j++){
				(*para).c[i+size/2][j+size/2]=(*para).p1[i][j]+(*para).p5[i][j]-(*para).p3[i][j]-(*para).p7[i][j];
			}
		}
		for(i=0;i<7;i++){
		pthread_join(pt[i],NULL);
		}
	}
	
}


