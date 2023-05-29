// #include <stdio.h>
// #include <stdlib.h>
// struct Date {
// 	int day;
// 	int month;
// 	int year;
// };
// typedef struct Date date;
// void swap(date **d1,date **d2){
// 	date* tmp=*d1;
// 	*d1=*d2;
// 	*d2=tmp;
// }
// void print_dates(date **arr, int n){
// 	for(int i=0;i<n;i++){
		
// 		printf("\nDate (dd mm yyyy): %d/%d/%d",arr[i]->day,arr[i]->month,arr[i]->year);
		
// 	}
// 	printf("\n\n");
// }
// int partition (date **arr, int low, int high)
// {
//     date* pivot = arr[high]; // pivot
//     int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
    
//     for (int j = low; j <= high - 1; j++)
//     {
//         // If current element is smaller than the pivot
//         if (arr[j]->year < pivot->year)
//         {
//             i++; // increment index of smaller element
//             swap(&arr[i], &arr[j]);
//         }
//     }
//     swap(&arr[i + 1], &arr[high]); //pivot is placed in the correct position
//     return (i + 1);
// }

// void quicksort(date** arr, int low, int high)
// {
//     if (low < high)
//     {
//         /* pi is partitioning index, arr[p] is now
//          at right place */
//         int pi = partition(arr, low, high);
        
//         // Separately sort elements before
//         // partition and after partition
//         quicksort(arr, low, pi - 1);
//         quicksort(arr, pi + 1, high);
//     }
// }
// void date_sort(arr,n){
// 	date** count[31];

// 	for(int i=arr)
	
// }

// void sort_dates(date **arr,int n){
// 	date_sort(arr,n);
// 	month_sort(arr,n);
// 	quicksort(arr,0,n-1);//sorts year wise
	
// }
// int main(){
	
// 	int n;
// 	printf("Enter length of array: ");
// 	scanf("%d",&n);
// 	date **arr=(date **)malloc(sizeof(date*)*n);
	
// 	printf("\nEnter the array: ");
// 	for(int i=0;i<n;i++){
// 		date * ele=(date*)malloc(sizeof(date));
// 		printf("\nEnter date (dd mm yyyy): ");
// 		scanf("%d %d %d",&(ele->day),&(ele->month),&(ele->year));
// 		arr[i]=ele;
// 	}
// 	sort_dates(arr,n);
// 	print_dates(arr,n);
// 	return 0;
// }
// #include<stdio.h>



// struct DATE

// {

// 	int day,month,year;

// };

// int main()

// {

// 	struct DATE d[100];

// 	int n,i,k,j;

// 	printf("Enter the value of n\n");

// 	scanf("%d",&n);

// 	for(i=0; i<n; i++)

// 	{

// 		printf("Enter %d date\n",i+1);

// 		scanf("%d%d%d",&d[i].day,&d[i].month,&d[i].year);

// 	}

// 	for(i=0; i<n; i++)

// 	{

// 		for(j=0; j<=i; j++)

// 		{

// 			if(d[j].year>d[i].year)

// 			{

// 				k=d[j].year;

// 				d[j].year=d[i].year;

// 				d[i].year=k;

// 				k=d[j].month;

// 				d[j].month=d[i].month;

// 				d[i].month=k;

// 				k=d[j].day;

// 				d[j].day=d[i].day;

// 				d[i].day=k;

// 			}

// 			else

// 			{		

// 				if(d[j].year==d[i].year)

// 				{

// 					if(d[j].month>d[i].month)

// 					{

// 						k=d[j].year;

// 						d[j].year=d[i].year;

// 						d[i].year=k;

// 						k=d[j].month;

// 						d[j].month=d[i].month;

// 						d[i].month=k;

// 						k=d[j].day;

// 						d[j].day=d[i].day;

// 						d[i].day=k;

// 					}

// 				else

// 				{

// 					if(d[j].month==d[i].month)

// 					{

// 						if(d[j].day>d[i].day)

// 						{

// 							k=d[j].year;

// 							d[j].year=d[i].year;

// 							d[i].year=k;

// 							k=d[j].month;

// 							d[j].month=d[i].month;

// 							d[i].month=k;

// 							k=d[j].day;

// 							d[j].day=d[i].day;

// 							d[i].day=k;

// 						}

// 					}		

// 				}

// 			}

// 		}

// 	}

// 	}

// 	for(i=0; i<n; i++)

// 	{

// 		printf("\n%d/%d/%d",d[i].day,d[i].month,d[i].year);

// 	}

// 	return 0;

// }







#include <stdio.h>
#include <stdlib.h>
  

int getMax(int arr[][3],int n, int q)
{
    int maxi = -100000000;
    for(int i=0;i<n;i++){
        
        maxi=(maxi>arr[i][q])?maxi:arr[i][q];
    }
    return maxi;
}
  

void sortDatesUtil(int arr[][3], 
                   int n, int q)
{
    int maxi = getMax(arr,n,q);
    int p = 1;
    while(maxi>0){
        
        int cnt[10]={0};
          
        for(int i=0;i<n;i++)
        {
            cnt[(arr[i][q]/p)%10]++;
        }
        for(int i=1;i<10;i++)
        {
            cnt[i]+=cnt[i-1];
        }
        int ans[n][3];
        for(int i=n-1;i>=0;i--)
        {
            int lastDigit = (arr[i][q]/p)%10;
              
            
            for(int j=0;j<3;j++)
            {
                ans[cnt[lastDigit]-1][j]
                  =arr[i][j];    
            }
            cnt[lastDigit]--;
        }
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<3;j++)
            {
                arr[i][j] = ans[i][j];
            }
        }
        
        p*=10;
        maxi/=10;
    }
}
  

void sortDates(int dates[][3], int n)
{
    // First sort by day
    sortDatesUtil(dates, n, 0);
    
    // Then by month
    sortDatesUtil(dates, n, 1); 
    // Finally by year
    sortDatesUtil(dates, n, 2);
}
  

void printArr(int arr[][3], int n)
{
   for(int i=0;i<n;i++)
   {
        for(int j=0;j<3;j++)
        {
            
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}
  

int main() 
{ 
		int n;
	printf("Enter length of array: ");
	scanf("%d",&n);
	
	int dates[n][3];
	printf("\nEnter the array: ");
	for(int i=0;i<n;i++){
		
		printf("\nEnter date (dd mm yyyy): ");
		scanf("%d %d %d",&(dates[i][0]),&(dates[i][1]),&(dates[i][2]));
		
	}
    
   
    
    
    sortDates(dates,n);
    
    printf("\nSorted Dates: \n");
    printArr(dates,n);
    return 0; 
} 