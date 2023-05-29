/*Devam Desai 
IIT2022035 LA5 P3*/


#include <stdio.h>
#include <stdlib.h>
void swap(int *i,int *j)

{
    int temp;
    temp =*i;
    *i=*j;
    *j=temp;
}
void bubb_sort(int * arr,int n){
	for(int i=0;i<n-1;i++){
		
		for(int j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]){
				swap(arr+j,arr+j+1);
			}
		}

	}
	
}

int main(){
	int sums[3][10000];
	int ind=0;
	for(int i=1;i<=20;i++){
		for(int j=1;j<=20;j++){
			for(int k=1;k<=20;k++){
				int sum=i*i+j*j+k*k;
				int arr[]={i,j,k};
				if(sum){
					// printf("HELLO");
					bubb_sort(arr,3);
					int flag=0;
					for(int x=0;x<ind;x++){
                        //if an order of numbers is already present in the matrix
						if(sums[0][x]==arr[0] && sums[1][x]==arr[1] && sums[2][x]==arr[2]){
							flag=1;
							break;
						}
					}
					if(flag){
						continue;
					}
					else{
						//if not, add the order of numbers in the matrix
						sums[0][ind]=i;
						sums[1][ind]=j;
						sums[2][ind]=k;
						ind ++;
					}
				}
				

			}
		}
	}
	for(int i=0;i<ind;i++){
		for(int j=0;j<ind;j++){
			if(i==j || sums[0][j]<sums[0][i]){
				continue;
			}
			if(sums[0][i]*sums[0][i]+sums[1][i]*sums[1][i]+sums[2][i]*sums[2][i]==sums[0][j]*sums[0][j]+sums[1][j]*sums[1][j]+sums[2][j]*sums[2][j]){
				printf("\na1=%d a2=%d a3=%d and a4=%d a5=%d a6=%d\n",sums[0][i],sums[1][i],sums[2][i],sums[0][j],sums[1][j],sums[2][j]);
			}
		}
	}
}