#include<stdio.h>
int main()
{
	int arr[] = {1,43,23,52,54,234,12,432,32,5,756,482};
	int i,temp,len,k;
	len = sizeof(arr)/sizeof(arr[0]);
	for(i = 1;i < len;i++)
	{
		if(arr[i-1]>arr[i])
		{
			temp = arr[i - 1];
			arr[i-1] = arr[i];
			arr[i] = temp;
		 } 
	}
	printf("%d",arr[len-1]);
	return 0;
}
