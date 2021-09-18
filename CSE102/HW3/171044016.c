#include <stdio.h>
#include <stdlib.h>


void menu();
int getInt(int mini,int maxi);
int numberGeneratorBetweenRange(int min,int max);
void horseRacingGame();
void countOccurence();
void triangleOfSequences();
int takePower10(int a);


int main()
{
	
	srand(10);
	menu();

	return 0;
}
/*Displays menu,gets choice and calls related function.
In case of wrong input program sends a warning message.While choice is 
not 0 menu displayment continues.*/
void menu()
{
	int choice;
	do
	{
		printf("1. Horse Racing Game\n");
		printf("2. Occurence Counter\n");
		printf("3. Triangle of Sequences\n");
		printf("0. Exit\n");

		printf("\t\tMake a choice: ");
		scanf("%d",&choice);
	
		switch(choice)
		{
			case 1:
				horseRacingGame();
				break;
			case 2:
				countOccurence();
				break;
			case 3:
				triangleOfSequences();
			case 0:
				break;
			default:
				printf("Wrong Input!!\n\n");
				break;
		}
	}while(choice != 0);


}
/*Gets an integer from the user.If the value is not in the
range of mini and maxi waits for a new value.*/
int getInt(int mini,int maxi)
{
	int number;
	do
	{
		scanf("%d",&number);

	}while(number < mini || number > maxi);

	return number;

}
/*Generates an integer and takes modular of it to place it in
the range of min and max values.*/
int numberGeneratorBetweenRange(int min,int max)
{
	int randomNumber;
	randomNumber = rand() % max;
	if(randomNumber < min)
	{
		randomNumber += min;
	}

	return randomNumber;
}

/*Calls numberGeneratorBetweenRange function to get number of horses.
Gets a number from the user. Prints the speed of horses.Checks if the number and 
the winner are equal and prints the result.*/
void horseRacingGame()
{
	int i,j,numberHorse,unit1=10,unit2=20,counter=0,counterDraw=0,winnerCounter=unit2,winner,number,draw,flag;
	numberHorse = numberGeneratorBetweenRange(3,5);
	printf("\nNumber of Horse: %d\n",numberHorse);
	printf("Horse Number: ");
	number = getInt(1,numberHorse);
	printf("Racing starts...\n");

	for(i=1;i <= numberHorse;i++)
	{
		printf("Horse %d: ",i);
		for(j=1;j <= numberGeneratorBetweenRange(unit1,unit2);j++)
		{
			printf("-");
			counter++;
		}
		printf("\n");
		if(counter < winnerCounter)
		{
			winner = i;
			winnerCounter = counter;
		}
		else if(counter == winnerCounter)
		{
			draw = winner;
			flag = i;
			winnerCounter = counter;
			counterDraw++;
		}
		
		counter = 0;
	}
	
	
	
	if(number == winner)
	{
		printf("You win! Winner is Horse %d.\n\n",winner);
	}
	else if(draw == winner && (number==flag || number ==winner))
	{
		printf("You win! Winner is Horse %d.\n\n",number);
	}
	else if(counterDraw != 0 && number != draw && number!= winner)
	{
		printf("You lose! Winner is Horse %d(or %d.It does not matter.).\n\n",winner,flag);
	}
	
	else
	{
		printf("You lose! Winner is Horse %d.\n\n",winner);
	}

}
/*Gets two positive numbers from the user and then searches the 
big number for search number.*/
void countOccurence()
{
	int bigNumber,searchNumber,countDigit=0,i,counterOccurence=0,check;
	printf("Big Number: ");
	scanf("%d",&bigNumber);
	printf("Search Number: ");
	scanf("%d",&searchNumber);
	
	
	for(i=0;bigNumber-takePower10(i) > 0;i++)
	{
		countDigit++;				
	}
	
	for(i=0;i<countDigit;i++)
	{
		check = (bigNumber / takePower10(i));
		if(check % 10 == searchNumber)
			counterOccurence++;
		else if(check % 100 == searchNumber)
			counterOccurence++;
		else if(check % 1000 == searchNumber)
			counterOccurence++;
		else if(check % 10000 == searchNumber)
			counterOccurence++;
		else if(check % 100000 == searchNumber)
			counterOccurence++;
		else if(check % 1000000 == searchNumber)
			counterOccurence++;
		else if(check % 10000000 == searchNumber)
			counterOccurence++;
		else if(check % 100000000 == searchNumber)
			counterOccurence++;
		else if(check % 1000000000 == searchNumber)
			counterOccurence++;
		else if(check % 10000000000 == searchNumber)
			counterOccurence++;
	}

	printf("Occurence: %d\n\n",counterOccurence);
}

/*Calls rnadom number generator function and then displays a sequence of numbers 
which consist a triangle-like shape.*/
void triangleOfSequences()
{
	int randomNumber,i,j;
	randomNumber = numberGeneratorBetweenRange(2,10);
	
	for(i=1;i<=randomNumber;i++)
	{	
		for(j=1;j<=i;j++)
		{
			printf("%d ",i*j);
		}
		printf("\n");
	}
	printf("\n");
}
/*Written for using in the function countOccurence.Calculates powers of 10.*/
int takePower10(int a)
{
	int i,result=1;
	for(i=0;i<a;i++)
	{
		result = result*10;
	}
	return result;
}
