/*The code which finds all digits of the given number*/
#include <stdio.h>


int main()
{
	
	int number,digit1,digit2,digit3,digit4,digit5;
	printf("Enter the number: ");
	scanf("%d",&number);
	printf("\n");
	while(number<23 || number>98760)
	{	
		printf("The number must be between 23 and 98760!!\n");
		printf("Enter the number: ");
		scanf("%d",&number);
		printf("\n");
	}
/*Check whether the number has fifth digit then calculate and print*/
	if((number / 10000) > 0 )
	{
		digit5 = number/10000;
		printf("The fifth digit is %d\n",digit5);
	}
/*Check whether the number has fourth digit then calculate and print*/
	if((number / 1000) > 0)
	{
		digit4 = (number % 10000)/1000;
		printf("The fourth digit is %d\n",digit4);
	}
/*Check whether the number has third digit then calculate and print*/
	if((number / 100) > 0)
	{
		digit3 = (number % 1000)/100;
		printf("The third digit is %d\n", digit3);
	}
/*Check whether the number has second digit then calculate and print*/
	if((number / 10) > 0)
	{
		digit2 = (number % 100)/10;
		printf("The second digit is %d\n",digit2 );
	}
/*Calculate the first digit then print*/
	digit1 = number % 10;
	printf("The first digit is %d\n",digit1 );


	return 0;
}
