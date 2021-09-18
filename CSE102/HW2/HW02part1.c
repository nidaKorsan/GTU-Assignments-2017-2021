/*The code which gets a number of students then offers 4 choices to the user*/
#include <stdio.h>
#include <stdlib.h>

/*We define the functions that we're gonna use*/
void display_menu(int);
int exe_selection(int most_successful,int index_successful,int most_unsuccessful,int index_unsuccessful,int A,int B,int C,int D,int F,double average,int student);
void most_successful1(int most,int index);
void most_unsuccessful1(int most,int index);
void list_each_letter(int A,int B,int C,int D,int F);
void average_grade(int student,double average);
void all_four_data(int most1,int index1,int most2,int index2,int A,int B,int C,int D,int F,double average,int student);



int main()
{
	/*Define the variables*/
	int number_student,close,grade,most_successful,most_unsuccessful,index_successful,index_unsuccessful,i,counterA=0,counterB=0,counterC=0,counterD=0,counterF=0;
	double average=0;
	srand(40);/*To get random grades*/

	/*We get a student number from user*/
	printf("Enter student count:");
	scanf("%d",&number_student);
	
	/*If the number is not in the range we want we warn the user and agin ask for a number*/
	while(number_student > 50 || number_student < 3)
	{
		printf("Not in Range!!!\n");
		printf("Enter student count:");
		scanf("%d",&number_student);
	}
	/*After we get the number of students we calculate our values such as average*/
	for(i=1;i <= number_student;i++)
	{
		grade = rand() % 101;
		printf("%d ",grade);
		/*check for new line*/
		if(i==10 || i== 20 || i == 30 || i == 40 || i == 50)
			printf("\n");	

		/*check for most successful grade*/
		if(grade > most_successful)
		{
			most_successful = grade;
			index_successful = i;
		}
		/*check for most unsuccesful grade*/
		if(grade < most_unsuccessful)
		{
			most_unsuccessful = grade;
			index_unsuccessful = i;
		}
		/*calculate the average sum*/
		average += grade;

		/*add 1 to the spesific counter if the grade is ... range*/
		if(grade <= 100 && grade >= 90)
		{
			counterA++;
		}
		else if(grade <= 89 && grade >= 80)
		{
			counterB++;
		}
		else if(grade <= 79 && grade >= 70)
		{
			counterC++;
		}
		else if(grade <= 69 && grade >= 60)
		{
			counterD++;
		}
		else
		{ 
			counterF++;
		}
 	}
 	/*Calculate the grade average*/
 	average = average/i;
 	printf("\n");
	/*Display the menu untill the user enters -1*/
	while(close!=-1)
	{
		display_menu(number_student);
		
		close = exe_selection(most_successful,index_successful,most_unsuccessful, index_unsuccessful, counterA,counterB,counterC,counterD,counterF, average,number_student);
	}



	return 0;
}

void display_menu(int number_student)
{
	
	printf("-----------------------------------------------\n");
	printf("Student Score Calculator Menu for %d Student\n\n",number_student);
	printf("1) Most Successful Student\n");
	printf("2) Most Unsuccessful Student\n");
	printf("3) Letter Grade Statistics\n");
	printf("4) Calculate Average\n");
	printf("5) Show all Data\n");


}
/*Ask the user for a selection then execute the selection by calling the related func*/
int exe_selection(int most_successful,int index_successful,int most_unsuccessful,int index_unsuccessful,int A,int B,int C,int D,int F,double average,int student)
{	
	int selection;

	printf("\t\t\tMake Selection: ");
	scanf("%d",&selection);


	switch(selection)
	{
		case 1:
			most_successful1(most_successful,index_successful);
			break;
	
		case 2:	
			most_unsuccessful1(most_unsuccessful,index_unsuccessful);
			break;
	
		case 3:
			list_each_letter(A,B,C,D,F);
			break;
		
		case 4:
			average_grade(student,average);
			break;
	
		case 5:	
			all_four_data(most_successful,index_successful,most_unsuccessful,index_unsuccessful,A,B,C,D,F,average,student);
			break;
		
		case -1:
			break;
		
		default:
			printf("False Selection!!!\n");
	}
	

	return selection;
}
/*print the wanted most successful student info*/
void most_successful1(int most,int index)
{
	char letter;
	printf("Most Successfully student:\n");
	printf("Index %d:\n",index);
	printf("Score %d:\n",most);
	if(most <= 100 && most >= 90)
	{
		letter = 'A';
	}
	else if(most <= 89 && most >= 80)
	{
		letter = 'B';
	}
	else if(most <= 79 && most >= 70)
	{
		letter = 'C';
	}
	else if(most <= 69 && most >= 60)
	{
		letter = 'D';
	}
	else
	{ 
		letter = 'F';
	}

	printf("Letter grade: %c\n",letter);
}
/*print the wanted most unsuccessful student info*/

void most_unsuccessful1(int most,int index)
{
	char letter;
	printf("Most Unuccessfully student:\n");
	printf("Index %d:\n",index);
	printf("Score %d:\n",most);
	if(most <= 100 && most >= 90)
	{
		letter = 'A';
	}
	else if(most <= 89 && most >= 80)
	{
		letter = 'B';
	}
	else if(most <= 79 && most >= 70)
	{
		letter = 'C';
	}
	else if(most <= 69 && most >= 60)
	{
		letter = 'D';
	}
	else
	{ 
		letter = 'F';
	}

	printf("Letter grade: %c\n",letter);	
}
/*Print the grade counters*/
void list_each_letter(int A,int B,int C,int D,int F)
{
	printf("%d student got letter grade 'A'\n",A);
	printf("%d student got letter grade 'B'\n",B);
	printf("%d student got letter grade 'C'\n",C);
	printf("%d student got letter grade 'D'\n",D);
	printf("%d student got letter grade 'F'\n",F);

}
/*Print the average grade*/
void average_grade(int student,double average)
{
	printf("The average Score of %d Student is %2.f\n",student,average);
}
/*Print all four datas we calculated*/
void all_four_data(int most1,int index1,int most2,int index2,int A,int B,int C,int D,int F,double average,int student)
{
	most_successful1(most1,index1);
	printf("\n");
	most_unsuccessful1(most2,index2);
	printf("\n");	
	list_each_letter(A,B,C,D,F);
	printf("\n");
	average_grade(student,average);
}