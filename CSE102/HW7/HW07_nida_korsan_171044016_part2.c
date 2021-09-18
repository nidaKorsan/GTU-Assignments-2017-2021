#include <stdio.h>
#define DATE_LNGTH 12
void menu();
void enterDate(char startDate[],char endDate[]);
void convertToDigit(char text[],int digText[]);
void makeMeNum(int *day,int *month,int *year,int digText[]);
void gnrtDate();
void newDate();
int is31(int sMonth);
int is30(int sMonth); 
int findDay(int day,int month,int year);/*My findDay function works for years after 1752.I searched the internet and used the sources i found to write this function.So it's not fully original*/ 

int main()
{
	menu();
	return 0;
}
void menu()
{
	int choice;
	do{
		printf("\n1.Generate and write dates into a file\n2.Use the file you created and change format\n0.Exit\n\nYour choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				gnrtDate();
				break;
			case 2:
				newDate();
		}
	}while(choice != 0);
}
void enterDate(char startDate[],char endDate[])/*Gets start and end dates*/
{
	printf("Enter a start date(dd/mm/yyyy): ");
	scanf("%s",startDate);
	printf("Enter an end date(dd/mm/yyyy): ");
	scanf("%s",endDate);
}
void convertToDigit(char text[],int digText[])/*Converts chars to digits*/
{
	int i,j = 0;
	for(i = 0; text[i] != 0;i++){
		if(47 < text[i] && 58 > text[i]){
			digText[j] = text[i] - 48;
			j++;
		}
	}
}
void makeMeNum(int *day,int *month,int *year,int digText[])/*Reads the int array and assigns the number values to the day,month,year variables*/
{
	*day = digText[0] * 10;
	*day += digText[1];
	*month = digText[2] * 10;
	*month += digText[3];
	*year = digText[4] * 1000;
	*year += digText[5] * 100;
	*year += digText[6] * 10;
	*year += digText[7];
}
void gnrtDate()/*This function generates dates starting from the startDate to the endDate.*/
{
	FILE *fin;
	char startDate[DATE_LNGTH],endDate[DATE_LNGTH];
	int digStartDate[DATE_LNGTH],digEndDate[DATE_LNGTH];
	int sDay,sMonth,sYear,eDay,eMonth,eYear;
	fin = fopen("input_date.txt","w");
	enterDate(startDate,endDate);
	convertToDigit(startDate,digStartDate);
	makeMeNum(&sDay,&sMonth,&sYear,digStartDate);
	convertToDigit(endDate,digEndDate);
	makeMeNum(&eDay,&eMonth,&eYear,digEndDate);
	for(; sDay != eDay || sMonth!= eMonth || sYear != eYear; sDay++){
		if(is31(sMonth) && sDay > 31){
			sDay= 1;
			sMonth++;
		}
		else if(is30(sMonth) && sDay > 30){
			sDay= 1;
			sMonth++;
		}
		else if(sMonth == 2 && sDay > 28){
			if(sYear % 400 == 0 && sDay > 29){
				sDay = 1;
				sMonth++;
			}
			else if(sYear % 100 == 0 && sYear % 400 != 0){
				sDay = 1;
				sMonth++;
			}
			else if(sYear % 4 == 0 && sDay > 29){
				sDay = 1;
				sMonth++;
			}
			else if(sYear % 4 != 0){
				sDay = 1;
				sMonth++;
			}
		}
		if(sMonth> 12){
			sMonth= 1;
			sYear++;
		}
		if(sDay< 10)
			fprintf(fin,"0%d",sDay);
		else
			fprintf(fin, "%d",sDay);
		
		if(sMonth< 10)
			fprintf(fin,"/0%d",sMonth);
		else
			fprintf(fin, "/%d",sMonth);
		
		fprintf(fin,"/%d\n",sYear);
	}
	fprintf(fin, "%s",endDate);	
	fclose(fin);
}
void newDate()/*This function reads the file which is generated in previous function and changes the format of the dates to ddddd/mmmmm/dd/yyyy*/
{
	FILE *fr,*fout;
	int day,month,year;
	fr = fopen("input_date.txt","r");
	fout = fopen("new_date.txt","w");
	while(!feof(fr)){
		fscanf(fr,"%d",&day);
		fgetc(fr);
		fscanf(fr,"%d",&month);
		fgetc(fr);
		fscanf(fr,"%d",&year);
		fgetc(fr);
		switch(findDay(day,month,year) % 7){
			case 2:
				fprintf(fout,"Monday, ");
				break;
			case 3:
				fprintf(fout,"Tuesday, ");
				break;
			case 4:
				fprintf(fout,"Wednesday, ");
				break;
			case 5:
				fprintf(fout,"Thursday, ");
				break;
			case 6:
				fprintf(fout,"Friday, ");
				break;
			case 0:
				fprintf(fout,"Saturday, ");
				break;
			case 1:
				fprintf(fout,"Sunday, ");
		}
		switch(month){
			case 1:
				fprintf(fout,"January ");
				break;
			case 2:
				fprintf(fout,"February ");
				break;
			case 3:
				fprintf(fout,"March ");
				break;
			case 4:
				fprintf(fout,"April ");
				break;
			case 5:
				fprintf(fout,"May ");
				break;
			case 6:
				fprintf(fout,"June ");
				break;
			case 7:
				fprintf(fout,"July ");
				break;
			case 8: 
				fprintf(fout,"August ");
				break;
			case 9:
				fprintf(fout,"September ");
				break;
			case 10:
				fprintf(fout,"October ");
				break;
			case 11:
				fprintf(fout,"November ");
				break;
			case 12:
				fprintf(fout,"December ");
		}
		if(day < 10)
			fprintf(fout,"0%d, ",day);
		else
			fprintf(fout,"%d, ",day);
		
		fprintf(fout,"%d\n",year);
	}
	fclose(fr);
	fclose(fout);
}
int is31(int sMonth)/*This function checks the current month to decide the amount of days the month has is 31*/
{
	if(sMonth == 1 || sMonth == 3 || sMonth == 5 || sMonth == 7 || sMonth == 8 || sMonth == 10 || sMonth == 12)
		return 1;
	else 
		return 0;
}
int is30(int sMonth)/*This function checks the current month to decide the amount of days the month has is 30*/
{
	if(sMonth == 4 || sMonth == 6 || sMonth == 9 || sMonth == 11)
		return 1;
	else 
		return 0;
}
int findDay(int day,int month,int year)
{
	int dayOfWeek = (year - 1) * 365 + ((year - 1) / 4) + (month - 1) * 30 + (day - 11);
	int cor = ((year - 1) / 100) - 16;
	int co = ((year - 1) / 400) - 4;
	int x = 0,i;
	if(cor > 0)
		dayOfWeek -= cor;
	if(co > 0)
		dayOfWeek += co;
	for(i = 1; i <= month - 1; i++){
		x++;
		switch(x){
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				dayOfWeek++;
				break;
			case 2:
				if(year % 4 == 0){
					if(year > 1752){
						if(year % 100 == 0){
							dayOfWeek -= 2;
							if(year % 400 == 0)
								dayOfWeek++;
						}
						else
						dayOfWeek--;
					}
					else 
						dayOfWeek--;
				}
				else
					dayOfWeek -= 2;
				break; 
		}
	}
	return dayOfWeek;
}