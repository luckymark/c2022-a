int sum(int arr[])
{
	int i,k;
	int len;
	k = 0;
	len = sizeof(arr)/sizeof(arr[0]);
	for(i = 0;i <= len;i++)
	{
		k = k+arr[i];
	}
	return k;
}
