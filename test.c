int main()
{
	int len;
	len = 0;
	if ((len = 5) > 9)
		printf("ok 1\n");
	if ((len = 10) > 9)
		printf("ok 2\n");
	printf("%d\n",len);
}